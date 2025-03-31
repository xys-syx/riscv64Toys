#include "ast.h"
#include "model.h"


ProgramUnit* createModule(char* sourceFileName)
{
	ProgramUnit* model = allocStruct(ProgramUnit);
	model->sourceFileName = sourceFileName;
	model->types = createDeclarationsScope(NULL);
	model->globalVars = createValuePlacesMap();
	model->functionDeclarations = createLinkedList();
	model->functionDeclarationsByName = createRbTreeByString();
	model->functionDefinitions = createLinkedList();
	model->functionDefinitionsByName = createRbTreeByString();
	model->errorsCount = 0;
	return model;
}

// TODO classify and interpret?
//enum DeclarationKind {
//	MODEL_DECL_TYPEDEF,
//	MODEL_DECL_VARS,
//	MODEL_DECL
//};

static TypeInfo* collectionCustomTypeInfo(AstNode* ast)
{
	printError(ast, "Custom types are not supported");
	return NULL;
}

typedef struct {
	bool isConst, isRestrict, isVolatile;
} TypeSpec;

static bool collectTypeSpecifier(AstNode* ast, TypeSpec* typeSpec)
{
	switch (ast->kind)
	{
	case AST_TSPEC_KW_CONST: typeSpec->isConst = true; return true;
	case AST_TSPEC_KW_RESTRICT: typeSpec->isRestrict = true; return true;
	case AST_TSPEC_KW_VOLATILE: typeSpec->isVolatile = true; return true;
		//case AST_TSPEC_KW_ATOMIC:
	default: return false;
	}
}

typedef struct {
	bool isTypedef, isExtern, isStatic, isThreadLocal, isAuto, isRegister;
} StorageSpec;

static bool collectStorageSpecifier(AstNode* ast, StorageSpec* storage)
{
	switch (ast->kind)
	{
	case AST_SSPEC_KW_TYPEDEF: storage->isTypedef = true; return true;
	case AST_SSPEC_KW_EXTERN: storage->isExtern = true; return true;
	case AST_SSPEC_KW_STATIC: storage->isStatic = true; return true;
	case AST_SSPEC_KW_THREAD_LOCAL: storage->isThreadLocal = true; return true;
	case AST_SSPEC_KW_AUTO: storage->isAuto = true; return true;
	case AST_SSPEC_KW_REGISTER: storage->isRegister = true; return true;
	default: return false;
	}
}

typedef struct {
	bool isInline, isNoReturn;
} FunctionSpec;

static bool collectFunctionSpecifier(AstNode* ast, FunctionSpec* functionSpec)
{
	switch (ast->kind)
	{
	case AST_FSPEC_KW_INLINE: functionSpec->isInline = true; return true;
	case AST_FSPEC_KW_NORETURN: functionSpec->isNoReturn = true; return true;
	default: return false;
	}
}

typedef struct {
	StorageSpec storageSpec;
	TypeSpec typeSpec;
	FunctionSpec functionSpec;
	TypeInfo* referencedType;
} SpecifiersInfo;

static SpecifiersInfo collectSpecifiers(AstNode* ast) // declaration_specifiers as AST_DECL_SPECS
{
	SpecifiersInfo spec;
	memset(&spec, 0, sizeof(SpecifiersInfo));


	for (AstNode* node = ast; node != NULL; node = node->next)
	{
		switch (node->kind)
		{
		case AST_TYPE_VOID:
		case AST_TYPE_CHAR:
		case AST_TYPE_SHORT:
		case AST_TYPE_INT:
		case AST_TYPE_LONG:
		case AST_TYPE_FLOAT:
		case AST_TYPE_DOUBLE:
		case AST_TYPE_SIGNED:
		case AST_TYPE_UNSIGNED:
		case AST_TYPE_BOOL:
		case AST_TYPE_COMPLEX:
		case AST_TYPE_IMAGINARY: spec.referencedType = recognizeWellKnownType(&node); break;

		case AST_TYPE_STRUCT:
		case AST_TYPE_UNION:
		case AST_TYPE_ENUM: spec.referencedType = collectionCustomTypeInfo(node); break;

		case AST_TYPE_NAMED: spec.referencedType = findCustomTypeByName(node->firstChild->payload); break;
		default: {
			if (!(collectTypeSpecifier(node, &spec.typeSpec)
				|| collectStorageSpecifier(node, &spec.storageSpec)
				|| collectFunctionSpecifier(node, &spec.functionSpec)))
			{
				printError(node, "Unknown type specifier %s", getStringAstNodeKinds(node->kind));
			}

			if (spec.typeSpec.isConst)
				printError(node, "Const ignored");
			if (spec.typeSpec.isRestrict)
				printError(node, "Restrict ignored");
			if (spec.typeSpec.isVolatile)
				printError(node, "Volatile ignored");
			if (spec.functionSpec.isInline)
				printError(node, "Inline ignored");
			if (spec.functionSpec.isNoReturn)
				printError(node, "NoReturn ignored");
			if (spec.storageSpec.isAuto)
				printError(node, "Auto ignored");
			if (spec.storageSpec.isRegister)
				printError(node, "Register ignored");
			if (spec.storageSpec.isThreadLocal)
				printError(node, "Thread local ignored");
		} break;
		}

		if (spec.referencedType != NULL)
		{
			node = node->next;
			break;
		}
	}

	// TODO validate end of specifiers - all the type specifiers should be completely parsed

	return spec;
}

static int evaluateConstExpr(AstNode* ast)
{
	if (ast->kind == AST_LITERAL_INT)
	{
		return atoi(ast->payload);
	}
	else
	{
		// TODO resolve the expression tree

		printError(ast, "Nontrivial constexpr not supported here");
	}

	return 0;
}

typedef struct PtrSpec {
	struct PtrSpec* next;
	TypeSpec flags;
} PtrSpec;

typedef struct ArrSpec {
	struct ArrSpec* next;
	int length;
} ArrSpec;

typedef struct DeclarationInfo {
	PtrSpec* ptrSpec;
	char* name;
	struct DeclarationInfo* nested;
	ArrSpec* arrSpec;
	ValuePlacesMap* params;
} DeclarationInfo;

static void releaseDeclarationInfo(DeclarationInfo* decl)
{
	for (DeclarationInfo* next = decl; decl != NULL; decl = next)
	{
		next = decl->nested;
		free(decl);
	}
}

static DeclarationInfo* collectDeclarationEntry(AstNode* ast);


//int* (*pfp)();
//int (*getFunc(void))(int, int);
//int (*(*getFunc2(void))(int))(int, int);
//int **(*(*(*getFuncArr[4])(void))(int))(int, int);
// 
// int x = getFuncArr[3]()(3)(3, 3)[2][2];
static TypeInfo* resolveEntityType(SpecifiersInfo* specs, DeclarationInfo* declaration, AstNode* ast)
{
	TypeInfo* type = specs->referencedType;

	for (DeclarationInfo* decl = declaration; decl != NULL; decl = decl->nested)
	{
		for (PtrSpec* ps = decl->ptrSpec; ps != NULL; ps = ps->next)
		{
			// TDOO consider specs
			type = makePointerType(type);
		}

		for (ArrSpec* as = decl->arrSpec; as != NULL; as = as->next)
		{
			type = makeArrayType(type, as->length);
		}

		if (decl->params != NULL)
		{
			FunctionSignature* signature = createFunctionSignature(type, decl->params);
			type = makeFunctionType(signature, ast);
		}
	}

	return type;
}

static ValuePlacesMap* collectFunctionParameters(AstNode* ast) // parameter_type_list
{
	ValuePlacesMap* params = createValuePlacesMap();

	if (ast->childrenCount > 0)
	{
		for (AstNode* paramNode = ast->firstChild; paramNode != NULL; paramNode = paramNode->next)
		{
			if (paramNode->kind == AST_DECLARATION_PARAM_ENTRY)
			{
				SpecifiersInfo specs = collectSpecifiers(paramNode->firstChild->firstChild);
				DeclarationInfo* paramDecl = paramNode->childrenCount > 1 ? collectDeclarationEntry(paramNode->lastChild) : NULL;
				TypeInfo* paramType = resolveEntityType(&specs, paramDecl, paramNode);

				// printTrace(paramNode, "  param [%d] %s type is %s", params->places->count, paramDecl == NULL ? "<abstract>" : paramDecl->name, paramType->name);

				// TODO consider specs
				if (!tryRegisterNewValuePlace(paramNode, params, paramDecl == NULL ? NULL : paramDecl->name, paramType, (SymbolFlags) { false, false, false }))
				{
					printError(paramNode, "Duplicated parameter name %s", paramDecl->name);
				}
				releaseDeclarationInfo(paramDecl);
			}
		}

		if (ast->lastChild->kind == AST_DECLARATION_PARAM_ELLIPSIS)
		{
			printError(ast->lastChild, "Variable-argument functions not supported");
		}
	}

	return params;
}

// declarator or abstract_declarator
static DeclarationInfo* collectDeclarationEntry(AstNode* ast)
{
	DeclarationInfo* declaration = allocStruct(DeclarationInfo);
	clearStructure(declaration);

	if (ast->kind != AST_DECLARATION_ENTRY)
	{
		printError(ast, "Invalid declaration entry %s", getStringAstNodeKinds(ast->kind));
		return NULL;
	}

	for (AstNode* ptrSpecNode = ast->firstChild;
		ptrSpecNode != NULL && ptrSpecNode->kind == AST_DECLARATION_PTR_SPEC;
		ptrSpecNode = ptrSpecNode->lastChild)
	{
		TypeSpec ptrSpec;
		if (ptrSpecNode->childrenCount > 0 && ptrSpecNode->firstChild->kind == AST_DECL_SPECS)
		{
			for (AstNode* node = ptrSpecNode->firstChild->firstChild; node != NULL; node = node->next)
			{
				collectTypeSpecifier(node, &ptrSpec);
			}
		}
		PtrSpec* p = allocStruct(PtrSpec);
		p->next = declaration->ptrSpec;
		p->flags = ptrSpec;
		declaration->ptrSpec = p;
	}

	for (AstNode* declNode = ast->lastChild->firstChild; declNode != NULL; declNode = declNode->next)
	{
		switch (declNode->kind)
		{
		case AST_ID: {
			declaration->name = declNode->payload;
			// printTrace(declNode, "Collecting decl name %s", declaration->name);
		} break;
		case AST_DECLARATION_ARRAY_SPEC: {
			if (declNode->childrenCount == 0)
			{
				printError(ast, "Variable-length arrays are not supported");
			}
			else
			{
				ArrSpec* a = allocStruct(ArrSpec);
				a->length = evaluateConstExpr(declNode->firstChild);
				// printTrace("array length %d\n", a->length);
				declaration->arrSpec = a;
			}
		} break;
		case AST_DECLARATION_PARAMS_SPEC: {
			// printTrace(declNode, "Collecting params of %s - %s", declaration->name, getStringAstNodeKinds(declNode->kind));
			declaration->params = collectFunctionParameters(declNode->firstChild);
		} break;
		case AST_DECLARATION_ENTRY: {
			// printTrace(declNode, "Collecting nested decl {");
			DeclarationInfo* nested = collectDeclarationEntry(declNode);
			declaration->nested = nested;
			declaration->name = nested->name;
			// printTrace(declNode, "} found name %s", nested->name);
		} break;
		default:
			printError(ast, "Unsupported declaration item kind %s", getStringAstNodeKinds(declNode->kind));
			break;
		}
	}

	return declaration;
}

static void registerTypeDeclaration(Declarations* decls, TypeInfo* type)
{
	switch (type->kind)
	{
	case TYPE_STRUCT: {
		if (!tryAddRbTreeItem(decls->structsByName, type->name, type))
			printError(type->definitionAst, "Struct %s redefinition", type->name);
	} break;
	case TYPE_UNION: {
		if (!tryAddRbTreeItem(decls->unionsByName, type->name, type))
			printError(type->definitionAst, "Union %s redefinition", type->name);
	} break;
	case TYPE_ENUM: {
		if (!tryAddRbTreeItem(decls->enumsByName, type->name, type))
			printError(type->definitionAst, "Enum %s redefinition", type->name);
	} break;
	default: /* do nothing */ break;
	}
}

LinkedList* collectDeclaration(ProgramUnit* model, Declarations* decls, ValuePlacesMap* vars, ValuePlacesMap* scope, AstNode* ast)
{
	LinkedList* result = NULL;

	if (ast->kind != AST_DECLARATION)
	{
		printError(ast, "Invalid declaration %s", getStringAstNodeKinds(ast->kind));
		return NULL;
	}

	SpecifiersInfo specs = collectSpecifiers(ast->firstChild->firstChild);

	if (specs.referencedType == NULL)
	{
		printError(ast, "Unresolved type specifier (invalid or unsupported)");
	}
	else 
	{
		if (specs.referencedType->name != NULL)
		{
			registerTypeDeclaration(decls, specs.referencedType);
		}
	}

	if (specs.functionSpec.isInline || specs.functionSpec.isNoReturn)
	{
		printError(ast, "inline and noreturn are not expected for declaration");
		return NULL;
	}

	if (ast->childrenCount > 1)
	{
		SymbolFlags flags = {
			.isExported = !specs.storageSpec.isStatic && !specs.storageSpec.isExtern,
			.isImplemented = !specs.storageSpec.isExtern,
			.isImported = specs.storageSpec.isExtern
		};

		// for each AST_DECLARATION_VALUE_PLACE in the AST_LIST under the AST_DECLARATION 
		for (AstNode* varNode = ast->lastChild->firstChild; varNode != NULL; varNode = varNode->next)
		{
			DeclarationInfo* decl = collectDeclarationEntry(varNode->firstChild);
			TypeInfo* type = resolveEntityType(&specs, decl, varNode);

			if (specs.storageSpec.isTypedef)
			{
				registerCustomType(type, decl->name);
			}
			else
			{
				// TODO backreference on error
				switch (type->kind)
				{
				case TYPE_ARRAY:
				case TYPE_POINTER:
					//case TYPE_FUNCPTR:
				case TYPE_BUILTIN:
				case TYPE_STRUCT:
				case TYPE_UNION:
				case TYPE_ENUM: {
					ValuePlaceInfo* varInfo;
					if (scope == NULL)
					{
						varInfo = tryRegisterNewValuePlace(varNode, vars, decl->name, type, flags);
					}
					else 
					{
						varInfo = tryRegisterNewScopedValuePlace(varNode, vars, scope, decl->name, type, flags);
					}

					if (varInfo == NULL)
					{
						printError(varNode, "Variable %s redefinition", decl->name);
					}
					else
					{
						if (result == NULL)
							result = createLinkedList();

						addLastLinkedListItem(result, varInfo);
					}
				} break;
				case TYPE_FUNC: {
					if (model != NULL)
					{
						Function* func = allocStruct(Function);
						func->id = model->functionDeclarations->count;
						func->name = decl->name;
						func->isPublic = !specs.storageSpec.isStatic;
						func->isExternal = specs.storageSpec.isExtern;
						func->signature = type->details.functions.signature;
						func->type = type;
						func->body = NULL;
						func->maxStackDepth = -1;
						func->declAst = varNode;
						func->implAst = NULL;

						addLastLinkedListItem(model->functionDeclarations, func);
						if (!tryAddRbTreeItem(model->functionDeclarationsByName, func->name, func))
							printError(varNode, "Function %s redeclaration", decl->name);
					}
					else 
					{
						printError(varNode, "Function declarations are not supported here");
					}
				} break;
				default:
					printError(ast, "Unknown type kind %d", type->kind);
					break;
				}
			}
			releaseDeclarationInfo(decl);
		}
	}

	return result;
}

typedef struct {
	ProgramUnit* model;
	Function* func;
	CfgScope* scope;
} TypeCheckingContext;

typedef enum EntityKind {
	EREF_NONE,
	EREF_FUNC,
	EREF_LOCAL,
	EREF_GLOBAL,
	EREF_PARAM
} EntityKind;

typedef struct {
	EntityKind kind;
	union {
		ValuePlaceInfo* variable;
		Function* function;
	};
} EntityReference;

static EntityReference resolveEntityReference(CfgExprNode* expr, TypeCheckingContext* ctx)
{
	char* name = expr->payload.identifier;
	CfgScope* scope = ctx->scope;

	ValuePlaceInfo* var = (ValuePlaceInfo*)findRbTreeItem(scope->vars->placeByName, name);
	while (scope->parent != NULL && var == NULL)
	{
		scope = scope->parent;
		var = (ValuePlaceInfo*)findRbTreeItem(scope->vars->placeByName, name);
	}
	if (var != NULL)
	{
		return (EntityReference) { .kind = EREF_LOCAL, .variable = var };
	}
	else
	{
		var = (ValuePlaceInfo*)findRbTreeItem(ctx->func->signature->parameters->placeByName, name);
		if (var != NULL)
		{
			return (EntityReference) { .kind = EREF_PARAM, .variable = var };
		}
		else
		{
			var = (ValuePlaceInfo*)findRbTreeItem(ctx->model->globalVars->placeByName, name);
			if (var != NULL)
			{
				return (EntityReference) { .kind = EREF_GLOBAL, .variable = var };
			}
			else
			{
				Function* fdef = (Function*)findRbTreeItem(ctx->model->functionDefinitionsByName, name);
				if (fdef != NULL)
				{
					return (EntityReference) { .kind = EREF_FUNC, .function = fdef };
				}
				else
				{
					Function* fdecl = (Function*)findRbTreeItem(ctx->model->functionDeclarationsByName, name);
					if (fdecl != NULL)
					{
						return (EntityReference) { .kind = EREF_FUNC, .function = fdecl };
					}
					else
					{
						printError(expr->ast, "Identifier %s is undefined", name);
						return (EntityReference) { .kind = EREF_NONE, .variable = var };
					}
				}
			}
		}
	}
}

static CfgExprNode* validateAndAdjustOperand(CfgExprNode* expr, TypeInfo* expectedType)
{
	if (typesAreEqual(expr->type, expectedType))
	{
		return expr;
	}
	else
	{
		// TODO test if adjustable

		CfgExprNode* result = makeUnaryExpression(expr->ast, CFG_EXPR_CAST, expr);
		result->type = expectedType;
		return result;
	}
}

static void validateAndAdjustBinaryOp(CfgExprNode* expr, bool returnsBool)
{
	TypeInfo* a = expr->args[0]->type;
	TypeInfo* b = expr->args[1]->type;
	TypeInfo* type;
	bool adjustA = false, adjustB = false;
	if (typesAreEqual(a, b))
	{
		type = a;
	}
	else
	{		
		bool aIsFloat = a->kind == TYPE_BUILTIN && a->details.builtins.builtinKind == BUILTIN_TYPE_FLOAT;
		bool bIsFloat = b->kind == TYPE_BUILTIN && b->details.builtins.builtinKind == BUILTIN_TYPE_FLOAT;
		if (aIsFloat && bIsFloat)
		{
			if (a->instanceSize < b->instanceSize)
			{
				adjustA = true;
				type = b;
			}
			else 
			{
				adjustB = true;
				type = a;
			}
		}
		else
		{
			bool aIsNum = a->kind == TYPE_BUILTIN && (a->details.builtins.builtinKind == BUILTIN_TYPE_INT || a->details.builtins.builtinKind == BUILTIN_TYPE_CHAR);
			bool bIsNum = b->kind == TYPE_BUILTIN && (b->details.builtins.builtinKind == BUILTIN_TYPE_INT || b->details.builtins.builtinKind == BUILTIN_TYPE_CHAR);
			if (aIsNum && bIsNum)
			{
				if (a->instanceSize - (a->details.builtins.isSigned ? 1 : 0) < b->instanceSize - (b->details.builtins.isSigned ? 1 : 0))
				{
					adjustA = true;
					type = b;
				}
				else
				{
					adjustB = true;
					type = a;
				}
			}
			else if (aIsNum && bIsFloat)
			{
				adjustA = true;
				type = b;
			}
			else if (aIsFloat && bIsNum)
			{
				adjustB = true;
				type = a;
			}
			else
			{
				printError(expr->ast, "Unable to adjust one of %s and %s to another", a->name, b->name);
				type = findBuiltinType(BUILTIN_TYPE_INVALID, 0, false);
			}
		}

		if (adjustA)
		{
			expr->args[0] = validateAndAdjustOperand(expr->args[0], type);
		}
		if (adjustB)
		{
			expr->args[1] = validateAndAdjustOperand(expr->args[1], type);
		}
	}

	if (returnsBool)
	{
		expr->type = findBuiltinType(BUILTIN_TYPE_BOOL, 0, false);
	}
	else
	{
		expr->type = type;
	}
}

static void validateAndAdjustStorageOp(CfgExprNode* expr, TypeCheckingContext* ctx)
{
	// resolve first arg to a real place
	// substitude the operation and resolve the actual type

	if (expr->args[0]->kind == CFG_EXPR_ENTITY_ID)
	{
		EntityReference ref = resolveEntityReference(expr->args[1], ctx);
		switch (ref.kind)
		{
		case EREF_LOCAL:
		case EREF_PARAM:
		case EREF_GLOBAL:
			expr->args[1] = validateAndAdjustOperand(expr->args[1], ref.variable->type);
			expr->type = ref.variable->type;
			break;
		default:
			printError(expr->ast, "Nonvariable cannot be assigned to.");
			break;
		}

	}
	else if (expr->args[0]->kind == CFG_EXPR_INDEX)
	{
		printError(expr->ast, "TODO ");

	}
	else
	{
		// TODO struct and union members
		printError(expr->ast, "Unsupported assignment target %s", getStringCfgExprKind(expr->args[0]->kind));
	}
}

typedef struct {
	int index;
	CfgExprNode* callExpr;
	bool isOk;
} CallExprParameterTypeCheckState;

static void callExprParameterTypeCheckAction(ValuePlaceInfo* paramInfo, CallExprParameterTypeCheckState* state)
{
	state->callExpr->args[state->index] = validateAndAdjustOperand(state->callExpr->args[state->index], paramInfo->type);
	state->index++;
}

static void controlFlowExprTypeCheckAction(CfgExprNode* expr, TypeCheckingContext* ctx)
{
	for (int i = 0; i < expr->argsCount; i++)
		controlFlowExprTypeCheckAction(expr->args[i], ctx);

	for (int i = 0; i < expr->argsCount; i++)
	{
		if (expr->args[i]->type->kind == TYPE_BUILTIN && expr->args[i]->type->details.builtins.builtinKind == BUILTIN_TYPE_INVALID)
		{
			expr->type = findBuiltinType(BUILTIN_TYPE_INVALID, 0, false);
			return;
		}
	}


	switch (expr->kind)
	{
	case CFG_EXPR_LITERAL_INT: expr->type = findBuiltinType(BUILTIN_TYPE_INT, 4, true); break;
	case CFG_EXPR_LITERAL_STRING: expr->type = makePointerType(findBuiltinType(BUILTIN_TYPE_CHAR, 1, true)); break;
	case CFG_EXPR_LITERAL_CHAR: expr->type = findBuiltinType(BUILTIN_TYPE_CHAR, 1, true); break;
	case CFG_EXPR_LITERAL_FLOAT: expr->type = findBuiltinType(BUILTIN_TYPE_FLOAT, 4, true); break;
	case CFG_EXPR_ADD:
	case CFG_EXPR_SUB:
	case CFG_EXPR_MUL:
	case CFG_EXPR_DIV:
	case CFG_EXPR_REM: validateAndAdjustBinaryOp(expr, false); break;
	case CFG_EXPR_ASSIGN: {
		CfgExprNode* target = expr->args[0];
		TypeInfo* targetType = target->type;

		if (target->kind == CFG_EXPR_ENTITY_ID)
		{
			if (targetType->kind != TYPE_FUNC)
			{
				expr->payload.valuePlace = target->payload.valuePlace;
				expr->type = target->type;
				expr->args[1] = validateAndAdjustOperand(expr->args[1], expr->type);
			}
			else 
			{
				printError(expr->ast, "Cannot assign to a function %s", target->payload.function->name);
			}
		}
		else if (target->kind == CFG_EXPR_INDEX)
		{
			expr->type = target->type;
			expr->args[1] = validateAndAdjustOperand(expr->args[1], expr->type);
		}
		else if (target->kind == CFG_EXPR_UNARY_UNREF)
		{
			expr->type = target->type;
			expr->args[1] = validateAndAdjustOperand(expr->args[1], expr->type);
		}
		else if (target->kind == CFG_EXPR_ACCESS_PTR)
		{
			printError(expr->ast, "Unsupported assignment target"); // TODO structs and unions
		}
		else if (target->kind == CFG_EXPR_ACCESS_DIRECT)
		{
			printError(expr->ast, "Unsupported assignment target"); // TODO structs and unions
		}
		else 
		{
			printError(expr->ast, "Invalid assignment target");
		}
	} break;
	case CFG_EXPR_CMP_EQ:
	case CFG_EXPR_CMP_NEQ:
	case CFG_EXPR_CMP_LT:
	case CFG_EXPR_CMP_GT:
	case CFG_EXPR_CMP_LTEQ:
	case CFG_EXPR_CMP_GTEQ: validateAndAdjustBinaryOp(expr, true); break;
	case CFG_EXPR_BOOL_NOT: expr->type = findBuiltinType(BUILTIN_TYPE_BOOL, 0, false); break;
	case CFG_EXPR_BOOL_AND:
	case CFG_EXPR_BOOL_OR: validateAndAdjustBinaryOp(expr, true); break;
	case CFG_EXPR_BITS_INV: expr->type = expr->args[0]->type; break;
	case CFG_EXPR_BITS_XOR:
	case CFG_EXPR_BITS_AND:
	case CFG_EXPR_BITS_OR: validateAndAdjustBinaryOp(expr, true); break;
	case CFG_EXPR_BITS_SHL:
	case CFG_EXPR_BITS_SHR: validateAndAdjustBinaryOp(expr, false); break;
	case CFG_EXPR_UNARY_REF: {
		// TODO validate that the argument represents an actual value place (lvalue)
		expr->type = makePointerType(expr->args[0]->type);
	} break;
	case CFG_EXPR_UNARY_UNREF: {
		TypeInfo* argType = expr->args[0]->type;
		if (argType->kind == TYPE_POINTER)
		{
			expr->type = argType->details.pointers.targetType;
		}
		else if (argType->kind == TYPE_ARRAY)
		{
			int depth = argType->details.arrays.dimensions - 1;
			TypeInfo* type = argType->details.arrays.elementType;
			for (int i = 0; i < depth; i++)
				type = makePointerType(type);

			expr->type = type;
		}
		else
		{
			printError(expr->ast, "Given type cannot be dereferenced");
		}
	} break;
	case CFG_EXPR_UNARY_PLUS:
	case CFG_EXPR_UNARY_MINUS: expr->type = expr->args[0]->type; break;
	case CFG_EXPR_ENTITY_ID: {
		EntityReference ref = resolveEntityReference(expr, ctx);
		switch (ref.kind)
		{
		case EREF_LOCAL:
		case EREF_PARAM:
		case EREF_GLOBAL:
			expr->type = ref.variable->type;
			expr->payload.valuePlace = ref.variable;
			break;
		case EREF_FUNC:
			expr->type = makeFunctionType(ref.function->signature, NULL);
			expr->payload.function = ref.function;
			break;
		default:
			expr->type = findBuiltinType(BUILTIN_TYPE_INVALID, 0, false);
			printError(expr->ast, "Unknown identifier %s", expr->payload.identifier);
			break;
		}
	} break;
	case CFG_EXPR_INDEX: {
		TypeInfo* type = expr->args[0]->type;
		for (int i = 1; i < expr->argsCount; i++)
		{
			if (type->kind == TYPE_POINTER && type->details.pointers.targetType->kind != TYPE_FUNC)
			{
				CfgExprNode* refExpr = makeUnaryExpression(expr->ast, CFG_EXPR_UNARY_REF, expr->args[0]);
				refExpr->type = type->details.pointers.targetType;
				CfgExprNode* simSizeExpr = prepareLiteralExpression(
					expr->ast, CFG_EXPR_LITERAL_INT, (CfgExprPayload) { .integer = type->details.pointers.targetType->instanceSize }
				);
				CfgExprNode* offExpr = makeBinaryExpression(expr->ast, CFG_EXPR_MUL, simSizeExpr, expr->args[i]);
				expr = makeBinaryExpression(expr->ast, CFG_EXPR_ADD, refExpr, offExpr);

				type = type->details.pointers.targetType;
			}
			else if (type->kind == TYPE_ARRAY && type->details.pointers.targetType->kind != TYPE_FUNC)
			{
				printError(expr->ast, "TODO rewrite array indexing %s", getStringCfgExprKind(expr->kind)); break;
				type = type->details.arrays.elementType;
			}
			else
			{
				printError(expr->ast, "Given type %s cannot be dereferenced", type->name);
			}
		}
		expr->type = type;
	} break;
	case CFG_EXPR_CALL: {
		TypeInfo* targetType = expr->args[0]->type;
		if (targetType->kind == TYPE_FUNC && expr->args[0]->kind == CFG_EXPR_ENTITY_ID)
		{
			FunctionSignature* signature = targetType->details.functions.signature;
			expr->payload.function = expr->args[0]->payload.function;
			expr->type = signature->returnType;

			CallExprParameterTypeCheckState state = {
				.index = 1,
				.callExpr = expr,
				.isOk = true
			};
			traverseLinkedList(signature->parameters->places, (action2)callExprParameterTypeCheckAction, &state);

			if (!state.isOk) 
			{
				int totalLen = 0;
				int* argsLengths = allocArray(int, expr->argsCount);
				for (int i = 0; i > expr->argsCount; i++)
				{
					totalLen += argsLengths[i] = strlen(expr->args[i]->type->name) + (i > 0 ? 2 : 0);
				}
				char* argsSignature = allocArray(char, totalLen + 1);
				char* p = argsSignature;
				for (int i = 0; i > expr->argsCount; i++)
				{
					if (i > 0)
					{
						strcpy(p, ", ");
					}
					p += 2;
					strcpy(p, expr->args[i]->type->name);
					p += argsLengths[i];
				}
				argsSignature[totalLen] = 0;
				printError(expr->ast, "Call parameters (%s) are inconsistent with function %s signature %s", argsSignature, expr->payload.function->name, expr->args[0]->type->name);
				free(argsSignature);
				free(argsLengths);
			}
		}
		else 
		{
			printError(expr->ast, "Indirect call not supported");
		}
	} break;
	case CFG_EXPR_RET: {
		expr->type = ctx->func->signature->returnType;

		if (expr->argsCount > 0)
		{
			expr->args[0] = validateAndAdjustOperand(expr->args[0], expr->type);
		}
	} break;
	case CFG_EXPR_COALESCE: /* TODO */ 
	case CFG_EXPR_PRESERVE: /* TODO */ 
	//case CFG_EXPR_LOAD_LOCAL:
	//case CFG_EXPR_LOAD_PARAM:
	//case CFG_EXPR_LOAD_GLOBAL:
	//case CFG_EXPR_STORE_LOCAL:
	//case CFG_EXPR_STORE_PARAM:
	//case CFG_EXPR_STORE_GLOBAL: // validateAndAdjustStorageOp(expr, ctx); break;
	case CFG_EXPR_CAST:
	case CFG_EXPR_SIZEOF:
	case CFG_EXPR_ALIGNOF:
	case CFG_EXPR_ERROR:
	case CFG_EXPR_ACCESS_DIRECT:
	case CFG_EXPR_ACCESS_PTR:
	default: {
		expr->type = findBuiltinType(BUILTIN_TYPE_INVALID, 0, false);
		printError(expr->ast, "Unexpected control-flow expression %s", getStringCfgExprKind(expr->kind));
	} break;
	}

	if (expr->type == NULL)
	{
		printError(expr->ast, "Unresolved type for expression of kind %s", getStringCfgExprKind(expr->kind));
		expr->type = findBuiltinType(BUILTIN_TYPE_INVALID, 0, false);
	}
}

static void controlFlowExprStackStackDepthEvaluationAction(CfgExprNode* expr, CfgNode* node)
{
	int depth = 0;
	for (int i = 0; i < expr->argsCount; i++)
	{
		CfgExprNode* subexpr = expr->args[i];
		controlFlowExprStackStackDepthEvaluationAction(subexpr, node);
		depth = max(depth, subexpr->depth);
	}
	expr->depth = depth + 1;
}

static void controlFlowNodeTypeCheckAction(CfgNode* node, TypeCheckingContext* ctx)
{
	ctx->scope = node->scope;
	traverseLinkedList(node->exprs, (action2)controlFlowExprTypeCheckAction, ctx);
	ctx->scope = NULL;

	if (node->isReturning && !typesAreEqual(ctx->func->signature->returnType, getBuiltinVoidType()))
	{
		LinkedListItem* lastExprItem = node->exprs->last;
		CfgExprNode* lastExpr = (CfgExprNode*)lastExprItem->data;
		lastExprItem->data = validateAndAdjustOperand(lastExpr, ctx->func->signature->returnType);
	}

	if (node->exprs->count > 0)
	{
		traverseLinkedList(node->exprs, (action2)controlFlowExprStackStackDepthEvaluationAction, node);
		node->stackDepth = ((CfgExprNode*)node->exprs->last->data)->depth;
	}
	else
	{
		node->stackDepth = 0;
	}

	ctx->func->maxStackDepth = max(ctx->func->maxStackDepth, node->stackDepth);
}

static void performTypeCheckings(ProgramUnit* model, Function* func)
{
	TypeCheckingContext ctx = {
		.model = model,
		.func = func
	};
	func->maxStackDepth = 0;
	// printTrace(func->implAst, "Checking the types of %s: %s", func->name, func->type->name);
	traverseLinkedList(func->body->nodes, (action2)controlFlowNodeTypeCheckAction, &ctx);
}

static void prepareFunctionDefinition(ProgramUnit* model, AstNode* ast)
{
	SpecifiersInfo specs = collectSpecifiers(ast->firstChild->firstChild);
	DeclarationInfo* decl = collectDeclarationEntry(ast->firstChild->next);
	TypeInfo* funcType = resolveEntityType(&specs, decl, ast);

	if (ast->childrenCount == 4)
	{
		printError(ast->firstChild->next->next, "declaration_list not supported here");
	}

	CfgInstance* cfg = prepareControlFlowGraph(model, ast->lastChild);

	Function* func = allocStruct(Function);
	func->id = model->functionDefinitions->count;
	func->name = decl->name;
	func->isPublic = !specs.storageSpec.isStatic;
	func->isExternal = specs.storageSpec.isExtern;
	func->signature = funcType->details.functions.signature;
	func->type = funcType;
	func->body = cfg;
	func->maxStackDepth = -1;
	func->declAst = NULL;
	func->implAst = ast;

	//printTrace(func->implAst, "Registering function %s: %s", func->name, func->type->name);


	addLastLinkedListItem(model->functionDefinitions, func);
	if (!tryAddRbTreeItem(model->functionDefinitionsByName, func->name, func))
		printError(ast, "Function %s redefinition", func->name);
}

static void newVarAction(ValuePlaceInfo* var, ProgramUnit* model)
{
	UNUSED(model);

	if (var->ast->childrenCount > 1)
	{
		AstNode* initializer = var->ast->lastChild; // should be a constant expression?
		UNUSED(initializer);

		printError(var->ast, "Global variable initializer not supported");
	}
}

void collectSource(ProgramUnit* model, AstNode* ast)
{
	for (AstNode* node = ast->firstChild; node != NULL; node = node->next)
	{
		switch (node->kind)
		{
		case AST_DEF_FUNCTION_IMPL: {
			prepareFunctionDefinition(model, node);
		} break;
		case AST_DECLARATION: {
			LinkedList* vars = collectDeclaration(model, model->types, model->globalVars, NULL, node);

			if (vars != NULL)
			{
				traverseLinkedList(vars, (action2)newVarAction, model);
				releaseLinkedList(vars);
			}
		} break;
		default:
			printError(node, "Unsupported top-level declaration %s", getStringAstNodeKinds(node->kind));
			break;
		}
	}
}

static void performFunctionAnalysisAction(Function* func, ProgramUnit* model)
{
	if (func->body != NULL)
	{
		performControlFlowReachabilityTraverse(func->body);

		performTypeCheckings(model, func);

		removeUnnecessaryNodes(func->body);
	}
}

void performAnalysis(ProgramUnit* model)
{
	traverseLinkedList(model->functionDefinitions, (action2)performFunctionAnalysisAction, model);
}

