#include <stdio.h>
#include <limits.h>

#include "utils.h"

#include "cfg.h"
#undef CFG_E_H
#define GENERATE_ENUM_STRINGS  // Start string generation
#include "cfg.h"             
#undef GENERATE_ENUM_STRINGS   // Stop string generation

#include "model.h"

typedef struct {
	CfgNode* node;
	CfgNode* targetNode;
	char* targetLabelName;
} CfgFixupInfo;

typedef struct {
	CfgInstance* cfg;
	
	CfgNode* currNode;

	LinkedList* fixups;
} CfgContext;

CfgExprPayload makeEmptyCfgPayload(void)
{
	CfgExprPayload payload;
	memset(&payload, 0, sizeof(CfgExprPayload));
	return payload;
}

static CfgNode* createCfgNode(CfgContext* ctx, AstNode* ast)
{
	CfgNode* node = allocStruct(CfgNode);
	node->id = ctx->cfg->nodes->count;
	node->ast = ast;
	node->conditionalBranch = NULL;
	node->defaultBranch = NULL;
	node->exprs = createLinkedList();
	node->scope = ctx->currNode == NULL ? NULL : ctx->currNode->scope;
	node->isReachable = false;
	node->isFinal = false;
	node->isReturning = false;
	node->stackDepth = -1;
	addLastLinkedListItem(ctx->cfg->nodes, node);
	return node;
}

CfgExprNode* createCfgExpr(AstNode* ast, CfgExprKind kind, CfgExprNode** args, int argsCount, CfgExprPayload payload)
{
	CfgExprNode* expr = allocStruct(CfgExprNode);
	expr->ast = ast;
	expr->kind = kind;
	expr->args = args;
	expr->argsCount = argsCount;
	expr->type = NULL;
	expr->payload = payload;
	expr->depth = -1;
	// expr->isReachable;
	return expr;
}

static CfgScope* createCfgScope(CfgScope* parent)
{
	CfgScope* scope = allocStruct(CfgScope);
	scope->parent = parent;
	scope->declarations = parent == NULL ? NULL : createDeclarationsScope(parent->declarations);
	scope->vars = createValuePlacesMap();
	scope->nodesByLabelName = parent == NULL ? createRbTreeByString() : parent->nodesByLabelName;
	scope->breakTarget = NULL;
	scope->continueTarget = NULL;
	return scope;
}

static void prepareStatement(CfgContext* ctx, AstNode* ast);
static CfgExprNode* prepareExpression(CfgContext* ctx, AstNode* ast);

CfgExprNode* prepareLiteralExpression(AstNode* ast, CfgExprKind exprKind, CfgExprPayload payload)
{
	return createCfgExpr(ast, exprKind, NULL, 0, payload);
}

CfgExprNode* makeUnaryExpression(AstNode* ast, CfgExprKind exprKind, CfgExprNode* arg)
{
	CfgExprNode** args = allocArray(CfgExprNode*, 1);
	args[0] = arg;
	return createCfgExpr(ast, exprKind, args, 1, makeEmptyCfgPayload());
}

CfgExprNode* makeBinaryExpression(AstNode* ast, CfgExprKind exprKind, CfgExprNode* a, CfgExprNode* b)
{
	CfgExprNode** args = allocArray(CfgExprNode*, 2);
	args[0] = a;
	args[1] = b;
	return createCfgExpr(ast, exprKind, args, 2, makeEmptyCfgPayload());
}

static CfgExprNode* prepareBuiltinUnaryExpression(CfgContext* ctx, AstNode* ast, CfgExprKind exprKind, int value, bool preStore)
{
	CfgExprNode* target = prepareExpression(ctx, ast->firstChild);
	
	CfgExprNode* arg = prepareLiteralExpression(ast, CFG_EXPR_LITERAL_INT, (CfgExprPayload) { .integer = value });

	CfgExprNode* op = makeBinaryExpression(ast, exprKind, target, arg);
	CfgExprNode* assignment = makeBinaryExpression(ast, CFG_EXPR_ASSIGN, target, op);

	if (preStore) // apply the operation then return 
	{
		return assignment;
	}
	else // preserve the value, then apply the operation, then return the value preserved
	{
		// TODO introduce the variable and store operation
		CfgExprNode* temp = prepareLiteralExpression(ast, CFG_EXPR_ENTITY_ID, (CfgExprPayload) { .identifier = "$temp" });

		CfgExprNode* preserveOp = makeBinaryExpression(ast, CFG_EXPR_ASSIGN, temp, target);
		op->args[0] = preserveOp;

		addLastLinkedListItem(ctx->currNode->exprs, assignment);
		return temp; // TODO intorduce load operation
	}
}

static CfgExprNode* prepareUnaryExpression(CfgContext* ctx, AstNode* ast, int exprKind)
{
	CfgExprNode* arg = prepareExpression(ctx, ast->firstChild);
	return makeUnaryExpression(ast, exprKind, arg);
}

static CfgExprNode* prepareBinaryExpression(CfgContext* ctx, AstNode* ast, int exprKind)
{
	CfgExprNode* a = prepareExpression(ctx, ast->firstChild);
	CfgExprNode* b = prepareExpression(ctx, ast->lastChild);
	return makeBinaryExpression(ast, exprKind, a, b);
}

static CfgExprNode* prepareBinaryAssignmentExpression(CfgContext* ctx, AstNode* ast, int exprKind)
{
	CfgExprNode* target = prepareExpression(ctx, ast->firstChild);
	CfgExprNode* arg = prepareExpression(ctx, ast->firstChild->next);
	CfgExprNode* op = makeBinaryExpression(ast, exprKind, target, arg);
	CfgExprNode* assignment = makeBinaryExpression(ast, CFG_EXPR_ASSIGN, target, op);
	return assignment;
}

static CfgExprNode* prepareIndexingTargetExpression(CfgContext* ctx, AstNode* ast)
{
	LinkedList* argsAstList = createLinkedList();

	AstNode* node = ast;
	while (node->kind == AST_EXPR_INDEX)
	{
		addFirstLinkedListItem(argsAstList, node->lastChild);
		node = node->firstChild;
	}

	CfgExprNode** args = allocArray(CfgExprNode*, argsAstList->count + 1);
	int index = 0;
	args[index++] = prepareExpression(ctx, node);
	for (LinkedListItem* item = argsAstList->first; item != NULL; item = item->next)
	{
		args[index++] = prepareExpression(ctx, (AstNode*)item->data);
	}
	return createCfgExpr(ast, CFG_EXPR_INDEX, args, index, makeEmptyCfgPayload());
}

static CfgExprNode* prepareExpression(CfgContext* ctx, AstNode* ast)
{
	CfgExprNode* expr;
	switch (ast->kind)
	{
	case AST_EXPR_PLUS: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_ADD); break;
	case AST_EXPR_MINUS: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_SUB); break;
	case AST_EXPR_MUL: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_MUL); break;
	case AST_EXPR_DIV: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_DIV); break;
	case AST_EXPR_REM: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_REM); break;
	case AST_EXPR_ASSIGN: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_ASSIGN); break;
	case AST_EXPR_CMP_EQ: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_CMP_EQ); break;
	case AST_EXPR_CMP_NEQ: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_CMP_NEQ); break;
	case AST_EXPR_CMP_LT: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_CMP_LT); break;
	case AST_EXPR_CMP_GT: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_CMP_GT); break;
	case AST_EXPR_CMP_LTEQ: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_CMP_LTEQ); break;
	case AST_EXPR_CMP_GTEQ: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_CMP_GTEQ); break;
	case AST_LITERAL_INT:
	{
		expr = prepareLiteralExpression(ast, CFG_EXPR_LITERAL_INT, (CfgExprPayload) { .integer = atoi(ast->payload) });
	} break;
	case AST_LITERAL_CHAR:
	{
		expr = prepareLiteralExpression(ast, CFG_EXPR_LITERAL_CHAR, (CfgExprPayload) { .character = ast->payload[1] });
	} break;
	case AST_LITERAL_FLOAT:
	{
		expr = prepareLiteralExpression(ast, CFG_EXPR_LITERAL_FLOAT, (CfgExprPayload) { .fractional = atof(ast->payload) });
	} break;
	case AST_LITERAL_STRING:
	{
		expr = prepareLiteralExpression(ast, CFG_EXPR_LITERAL_STRING, (CfgExprPayload) { .string = ast->payload });
	} break;
	case AST_ID:
	{
		expr = prepareLiteralExpression(ast, CFG_EXPR_ENTITY_ID, (CfgExprPayload) { .identifier = ast->payload });
	} break;
	case AST_EXPR_CALL:
	{
		int argsCount = ast->childrenCount > 1 ? ast->lastChild->childrenCount + 1: 1;
		CfgExprNode** args = allocArray(CfgExprNode*, argsCount);
		args[0] = prepareExpression(ctx, ast->firstChild);
		AstNode* opnd = ast->lastChild->firstChild;
		for (int i = 1; i < argsCount; i++)
		{
			args[i] = prepareExpression(ctx, opnd);
			opnd = opnd->next;
		}
		expr = createCfgExpr(ast, CFG_EXPR_CALL, args, argsCount, makeEmptyCfgPayload());
	} break;
	case AST_EXPR_ASS_PLUS: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_ADD); break;
	case AST_EXPR_ASS_MINUS: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_SUB); break;
	case AST_EXPR_ASS_MUL: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_MUL); break;
	case AST_EXPR_ASS_DIV: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_DIV); break;
	case AST_EXPR_ASS_REM: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_REM); break;
	case AST_EXPR_ASS_BITS_XOR: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_BITS_XOR); break;
	case AST_EXPR_ASS_BITS_AND: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_BITS_AND); break;
	case AST_EXPR_ASS_BITS_OR: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_BITS_OR); break;
	case AST_EXPR_ASS_BITS_SHL: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_BITS_SHL); break;
	case AST_EXPR_ASS_BITS_SHR: expr = prepareBinaryAssignmentExpression(ctx, ast, CFG_EXPR_BITS_SHR); break;
	case AST_EXPR_BITS_INV: expr = prepareUnaryExpression(ctx, ast, CFG_EXPR_BITS_INV); break;
	case AST_EXPR_BITS_XOR: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_BITS_XOR); break;
	case AST_EXPR_BITS_AND: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_BITS_AND); break;
	case AST_EXPR_BITS_OR: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_BITS_OR); break;
	case AST_EXPR_BITS_SHL: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_BITS_SHL); break;
	case AST_EXPR_BITS_SHR: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_BITS_SHR); break;
	case AST_EXPR_BOOL_NOT: expr = prepareUnaryExpression(ctx, ast, CFG_EXPR_BOOL_NOT); break;
	case AST_EXPR_BOOL_AND: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_BOOL_AND); break;
	case AST_EXPR_BOOL_OR: expr = prepareBinaryExpression(ctx, ast, CFG_EXPR_BOOL_OR); break;
	case AST_EXPR_UNARY_REF: expr = prepareUnaryExpression(ctx, ast, CFG_EXPR_UNARY_REF); break;
	case AST_EXPR_UNARY_UNREF: expr = prepareUnaryExpression(ctx, ast, CFG_EXPR_UNARY_UNREF); break;
	case AST_EXPR_UNARY_PLUS: expr = prepareUnaryExpression(ctx, ast, CFG_EXPR_UNARY_PLUS); break;
	case AST_EXPR_UNARY_MINUS: expr = prepareUnaryExpression(ctx, ast, CFG_EXPR_UNARY_MINUS); break;
	case AST_EXPR_PRE_INC: expr = prepareBuiltinUnaryExpression(ctx, ast, CFG_EXPR_ADD, 1, true); break;
	case AST_EXPR_PRE_DEC: expr = prepareBuiltinUnaryExpression(ctx, ast, CFG_EXPR_SUB, 1, true); break;
	case AST_EXPR_POST_INC: expr = prepareBuiltinUnaryExpression(ctx, ast, CFG_EXPR_ADD, 1, false); break;
	case AST_EXPR_POST_DEC: expr = prepareBuiltinUnaryExpression(ctx, ast, CFG_EXPR_SUB, 1, false); break;
	case AST_EXPR_CONDITIONAL:
	{
		CfgExprNode** args = allocArray(CfgExprNode*, 3);
		args[0] = prepareExpression(ctx, ast->firstChild);
		args[1] = prepareExpression(ctx, ast->firstChild->next);
		args[2] = prepareExpression(ctx, ast->firstChild->next->next);
		expr = createCfgExpr(ast, CFG_EXPR_COALESCE, args, 3, makeEmptyCfgPayload());
	} break;
	case AST_EXPR_INDEX: expr = prepareIndexingTargetExpression(ctx, ast); break;
	case AST_EXPR_LIST:
	{
		if (ast->childrenCount == 1)
		{
			expr = prepareExpression(ctx, ast->firstChild);
			break;
		}
		else
		{
			__attribute__((fallthrough));
		}
	}
	case AST_EXPR_INIT:
	case AST_EXPR_INIT_MEMBER:
	case AST_EXPR_INIT_MEMBER_TARGET:
	case AST_EXPR_INIT_MEMBER_TARGET_INDEX:
	case AST_EXPR_INIT_MEMBER_TARGET_FIELD:
	case AST_EXPR_CAST:
	case AST_EXPR_ACCESS_DIRECT:
	case AST_EXPR_ACCESS_PTR:
	case AST_EXPR_SIZEOF:
	case AST_EXPR_ALIGNOF:
	default:
		printError(ast, "Unsupported expression kind %s", getStringAstNodeKinds(ast->kind));
		expr = createCfgExpr(ast, CFG_EXPR_ERROR, NULL, 0, makeEmptyCfgPayload());
		break;
	}
	return expr;
}

static void prepareTopExpression(CfgContext* ctx, AstNode* ast)
{
	CfgExprNode* expr = prepareExpression(ctx, ast);
	addLastLinkedListItem(ctx->currNode->exprs, expr);
}

static void prepareBlockStatement(CfgContext* ctx, AstNode* ast)
{
	CfgNode* blockNode = createCfgNode(ctx, ast);
	ctx->currNode->defaultBranch = blockNode;
	ctx->currNode = blockNode;
	blockNode->scope = createCfgScope(ctx->currNode->scope);

	for (AstNode* node = ast->firstChild; node != NULL; node = node->next)
	{
		prepareStatement(ctx, node);
	}

	CfgNode* prevScope = createCfgNode(ctx, ast);
	ctx->currNode->defaultBranch = prevScope;
	ctx->currNode = prevScope;
	prevScope->scope = prevScope->scope->parent;
}

static void prepareForLoopStatement(CfgContext* ctx, AstNode* ast)
{
	CfgNode* initNode = createCfgNode(ctx, ast->firstChild);
	ctx->currNode->defaultBranch = initNode;
	ctx->currNode = initNode;
	initNode->scope = createCfgScope(ctx->currNode->scope);
	prepareStatement(ctx, ast->firstChild);

	CfgNode* exitLoopNode = createCfgNode(ctx, NULL);
	exitLoopNode->scope = initNode->scope->parent;

	CfgNode* condNode = createCfgNode(ctx, ast->firstChild->next);
	ctx->currNode->defaultBranch = condNode;
	ctx->currNode = condNode;
	prepareStatement(ctx, ast->firstChild->next);
	
	CfgNode* loopBodyNode = createCfgNode(ctx, ast->lastChild);
	ctx->currNode->defaultBranch = exitLoopNode;
	ctx->currNode->conditionalBranch = loopBodyNode;
	ctx->currNode = loopBodyNode;

	CfgNode* counterNode = createCfgNode(ctx, ast->firstChild->next->next);
	ctx->currNode->scope->breakTarget = exitLoopNode;
	ctx->currNode->scope->continueTarget = counterNode;
	prepareStatement(ctx, ast->lastChild);

	ctx->currNode->defaultBranch = counterNode;
	ctx->currNode = counterNode;
	if (ast->childrenCount > 3)
	{
		prepareTopExpression(ctx, ast->firstChild->next->next);
	}
	ctx->currNode->defaultBranch = condNode;

	ctx->currNode = exitLoopNode;
}

static void prepareWhileLoopStatement(CfgContext* ctx, AstNode* ast)
{
	CfgNode* condNode = createCfgNode(ctx, ast->firstChild);	
	ctx->currNode->defaultBranch = condNode;
	ctx->currNode = condNode;
	prepareTopExpression(ctx, ast->firstChild);

	CfgNode* exitLoopNode = createCfgNode(ctx, NULL);
	CfgNode* loopBodyNode = createCfgNode(ctx, ast->lastChild);
	ctx->currNode->defaultBranch = exitLoopNode;
	ctx->currNode->conditionalBranch = loopBodyNode;

	ctx->currNode = loopBodyNode;
	ctx->currNode->scope = createCfgScope(ctx->currNode->scope);
	ctx->currNode->scope->breakTarget = exitLoopNode;
	ctx->currNode->scope->continueTarget = condNode;
	prepareStatement(ctx, ast->lastChild);
	ctx->currNode->defaultBranch = condNode;

	ctx->currNode = exitLoopNode;
}

static void prepareDoWhileLoopStatement(CfgContext* ctx, AstNode* ast)
{
	CfgNode* bodyNode = createCfgNode(ctx, ast->firstChild);
	CfgNode* condNode = createCfgNode(ctx, ast->lastChild);
	CfgNode* exitLoopNode = createCfgNode(ctx, NULL);

	ctx->currNode->defaultBranch = bodyNode;
	ctx->currNode = bodyNode;
	ctx->currNode->scope = createCfgScope(ctx->currNode->scope);
	ctx->currNode->scope->breakTarget = exitLoopNode;
	ctx->currNode->scope->continueTarget = condNode;
	prepareStatement(ctx, ast->firstChild);

	ctx->currNode->defaultBranch = condNode;
	ctx->currNode = condNode;
	prepareTopExpression(ctx, ast->lastChild);
	ctx->currNode->conditionalBranch = bodyNode;

	ctx->currNode->defaultBranch = exitLoopNode;
	ctx->currNode = exitLoopNode;
}

static void prepareIfStatement(CfgContext* ctx, AstNode* ast)
{
	CfgNode* condNode = createCfgNode(ctx, ast->firstChild);
	ctx->currNode->defaultBranch = condNode;
	ctx->currNode = condNode;
	prepareTopExpression(ctx, ast->firstChild);

	CfgNode* thenNode = createCfgNode(ctx, ast->firstChild->next);
	condNode->conditionalBranch = thenNode;

	
	ctx->currNode = thenNode;
	prepareStatement(ctx, ast->firstChild->next);

	CfgNode* continueNode = createCfgNode(ctx, NULL);
	ctx->currNode->defaultBranch = continueNode;

	if (ast->childrenCount > 2) 
	{
		CfgNode* elseNode = createCfgNode(ctx, ast->lastChild);
		condNode->defaultBranch = elseNode;

		ctx->currNode = elseNode;
		prepareStatement(ctx, ast->lastChild);
		ctx->currNode->defaultBranch = continueNode;
	}
	else 
	{
		condNode->defaultBranch = continueNode;
	}

	ctx->currNode = continueNode;
}

static void implementVarInitializer(ValuePlaceInfo* var, CfgContext* ctx)
{
	AstNode* varSpec = var->ast;

	if (varSpec->childrenCount > 1)
	{
		CfgExprNode* target = prepareLiteralExpression(varSpec, CFG_EXPR_ENTITY_ID, (CfgExprPayload) { .identifier = var->name });
		CfgExprNode* initExpr = prepareExpression(ctx, varSpec->lastChild);
		addLastLinkedListItem(ctx->currNode->exprs, makeBinaryExpression(varSpec, CFG_EXPR_ASSIGN, target, initExpr));
	}
}

static void prepareDeclarationStatement(CfgContext* ctx, AstNode* ast)
{
	LinkedList* vars = collectDeclaration(NULL, ctx->currNode->scope->declarations, ctx->cfg->vars, ctx->currNode->scope->vars, ast);
	if (vars != NULL)
	{
		traverseLinkedList(vars, (action2)implementVarInitializer, ctx);
		releaseLinkedList(vars);
	}
}

static void prepareExplicitFlowFixup(CfgContext* ctx, AstNode* ast, CfgFixupInfo info)
{
	CfgFixupInfo* fixup = allocStruct(CfgFixupInfo);
	*fixup = info;
	addLastLinkedListItem(ctx->fixups, fixup);

	CfgNode* nextNode = createCfgNode(ctx, ast);
	ctx->currNode->defaultBranch = nextNode;
	ctx->currNode = nextNode;
}

static void prepareReturnStatement(CfgContext* ctx, AstNode* ast)
{
	CfgExprNode* retExpr;
	if (ast->childrenCount > 0)
	{
		retExpr = makeUnaryExpression(ast, CFG_EXPR_RET, prepareExpression(ctx, ast->firstChild));
		ctx->currNode->isReturning = true;
	}
	else
	{
		retExpr = createCfgExpr(ast, CFG_EXPR_RET, NULL, 0, makeEmptyCfgPayload());
	}
	addLastLinkedListItem(ctx->currNode->exprs, retExpr);
	ctx->currNode->isFinal = true;
	prepareExplicitFlowFixup(ctx, ast, (CfgFixupInfo) { .node = ctx->currNode, .targetNode = NULL, .targetLabelName = NULL });
}

static void prepareStatement(CfgContext* ctx, AstNode* ast)
{
	switch (ast->kind)
	{
	case AST_DECLARATION: prepareDeclarationStatement(ctx, ast); break;
	case AST_STMT_BLOCK: prepareBlockStatement(ctx, ast); break;
	case AST_STMT_WHILE: prepareWhileLoopStatement(ctx, ast); break;
	case AST_STMT_DO: prepareDoWhileLoopStatement(ctx, ast); break;
	case AST_STMT_FOR: prepareForLoopStatement(ctx, ast); break;
	case AST_STMT_IF: prepareIfStatement(ctx, ast); break;
	case AST_STMT_RETURN: prepareReturnStatement(ctx, ast); break;
	case AST_STMT_EXPR: prepareTopExpression(ctx, ast->firstChild); break;
	case AST_STMT_EMPTY: /* nothing to do */ break;
	case AST_STMT_LABELED: 
	{
		CfgNode* labeledNode = createCfgNode(ctx, ast);
		ctx->currNode->defaultBranch = labeledNode;
		ctx->currNode = labeledNode;
		if (ast->firstChild->kind == AST_ID)
		{
			if (!tryAddRbTreeItem(ctx->currNode->scope->nodesByLabelName, ast->firstChild->payload , labeledNode))
			{

				printError(ast, "duplicate label '%s'", ast->firstChild->payload); // TODO report old location too
				// TODO error label redefinition
			}
		}
		else 
		{
			// TODO switch-case not supported at the moment
			printError(ast, "Switch-case statement not supported at the moment");
		}
		prepareStatement(ctx, ast->lastChild);
	} break;
	case AST_STMT_GOTO: 
	{
		prepareExplicitFlowFixup(ctx, ast, (CfgFixupInfo) { .node = ctx->currNode, .targetNode = NULL, .targetLabelName = ast->firstChild->payload });
	} break;
	case AST_STMT_BREAK:
	{
		CfgScope* scope = ctx->currNode->scope;
		while (scope != NULL && scope->breakTarget == NULL)
			scope = scope->parent;

		if (scope == NULL)
		{
			printError(ast, "Unexpected break statement outside of the loop");
		}
		else
		{
			prepareExplicitFlowFixup(ctx, ast, (CfgFixupInfo) { .node = ctx->currNode, .targetNode = scope->breakTarget, .targetLabelName = NULL });
		}
	} break;
	case AST_STMT_CONTINUE:
	{
		CfgScope* scope = ctx->currNode->scope;
		while (scope != NULL && scope->continueTarget == NULL)
			scope = scope->parent;

		if (scope == NULL)
		{
			printError(ast, "Unexpected continue statement outside of the loop");
		}
		else
		{
			prepareExplicitFlowFixup(ctx, ast, (CfgFixupInfo) { .node = ctx->currNode, .targetNode = scope->continueTarget, .targetLabelName = NULL });
		}
	} break;
	case AST_STMT_SWITCH:
	case AST_STMT_ERROR:
	default:
		printError(ast, "Unsupported statement %s", getStringAstNodeKinds(ast->kind));
		break;
	}
}

static void applyBranchingFixup(CfgFixupInfo* fixup, CfgContext* ctx)
{
	UNUSED(ctx);

	if (fixup->targetNode != NULL)
	{
		fixup->node->defaultBranch = fixup->targetNode;
	}
	else if (fixup->targetLabelName != NULL)
	{
		CfgScope* scope = fixup->node->scope;
		CfgNode* targetNode = findRbTreeItem(scope->nodesByLabelName, fixup->targetLabelName);
		while (targetNode == NULL && scope != NULL)
		{
			scope = scope->parent;
			targetNode = findRbTreeItem(scope->nodesByLabelName, fixup->targetLabelName);
		}

		if (targetNode != NULL)
		{
			fixup->node->defaultBranch = targetNode;
		}
		else
		{
			// TODO target label not found error 
		}
	}
	else
	{
		fixup->node->defaultBranch = NULL;
	}
}

void performControlFlowReachabilityTraverse(CfgInstance* cfg)
{
	int depth = 0;
	CfgNode** stack = allocArray(CfgNode*, cfg->nodes->count * 2);
	stack[0] = cfg->start;

	while (depth >= 0)
	{
		CfgNode* node = stack[depth];
		if (node != NULL)
		{
			// printTrace(node->ast, "Marked %d", node->id);
			node->isReachable = true;

			stack[++depth] = NULL;

			if (node->defaultBranch != NULL && !node->defaultBranch->isReachable)
				stack[++depth] = node->defaultBranch;
			if (node->conditionalBranch != NULL && !node->conditionalBranch->isReachable)
				stack[++depth] = node->conditionalBranch;
		}
		else
		{
			node = stack[--depth];
			--depth;
		}
	}

	free(stack);
}

static void transparentBranchingFixupAction(CfgNode* node, CfgNode* oldTarget)
{
	if (node->defaultBranch == oldTarget)
		node->defaultBranch = oldTarget->defaultBranch;
	if (node->conditionalBranch == oldTarget)
		node->conditionalBranch = oldTarget->defaultBranch;
}

static bool uselessNodesCheck(CfgNode* node, CfgInstance* cfg)
{
	if (node->exprs->count == 0)
	{
		if (node->conditionalBranch != NULL)
			printError(NULL, "Control-flow graph construction error detected");

		traverseLinkedList(cfg->nodes, (action2)transparentBranchingFixupAction, node);
		return true;
	}
	else
	{
		return false;
	}
}

static bool unreachabilityFlagCheck(CfgNode* node, CfgInstance* cfg)
{
	UNUSED(cfg);
	return !node->isReachable;
}

typedef struct {
	int count;
} RenumberingState;

static void renumberingAction(CfgNode* node, RenumberingState* s)
{
	node->id = s->count++;
}

void removeUnnecessaryNodes(CfgInstance* cfg)
{
	traverseAndRemove(cfg->nodes, (boolFunc2)unreachabilityFlagCheck, cfg);
	traverseAndRemove(cfg->nodes, (boolFunc2)uselessNodesCheck, cfg);

	RenumberingState s = { 0 };
	traverseLinkedList(cfg->nodes, (action2)renumberingAction, &s);
}

static CfgInstance* prepareControlFlowGraphImpl(ProgramUnit* model, AstNode* exprOrStmt, bool forStmt)
{
	CfgInstance* cfg = allocStruct(CfgInstance);
	cfg->nodes = createLinkedList();
	cfg->start = NULL;
	cfg->vars = createValuePlacesMap();
	cfg->scope = createCfgScope(NULL);
	cfg->scope->declarations = createDeclarationsScope(model->types);
	
	CfgContext* ctx = allocStruct(CfgContext);
	ctx->cfg = cfg;
	ctx->currNode = NULL;
	ctx->currNode = cfg->start = createCfgNode(ctx, NULL);
	ctx->fixups = createLinkedList();

	if (forStmt)
	{
		prepareStatement(ctx, exprOrStmt);
	}
	else 
	{
		prepareTopExpression(ctx, exprOrStmt);
	}

	traverseLinkedList(ctx->fixups, (action2)applyBranchingFixup, ctx);

	free(ctx);

	return cfg;
}

CfgInstance* prepareControlFlowGraph(struct ProgramUnit* model, AstNode* exprOrStmt)
{
	switch (classifyAstNode(exprOrStmt))
	{
	case AST_KIND_FAMILY_EXPR: 
		return prepareControlFlowGraphImpl(model, exprOrStmt, false);
	case AST_KIND_FAMILY_STATEMENT: 
		return prepareControlFlowGraphImpl(model, exprOrStmt, true);
	case AST_KIND_FAMILY_VAR_DECL:
	case AST_KIND_FAMILY_TYPE_DECL:
	case AST_KIND_FAMILY_FUNC_DECL:
	case AST_KIND_FAMILY_FUNC_IMPL:
	case AST_KIND_FAMILY_UTIL:
	case AST_KIND_FAMILY_TODO:
	default:
		printError(exprOrStmt, "Cannot interpret node as control flow %s", getStringAstNodeKinds(exprOrStmt->kind));
		return NULL;
	}
}

static void freeCfgNode(void* node, void* state)
{
	UNUSED(state);
	free(node);
}

void releaseControlFlowGraph(CfgInstance* cfg)
{
	traverseLinkedList(cfg->nodes, freeCfgNode, NULL);
	releaseLinkedList(cfg->nodes);
	free(cfg);
}

typedef struct {
	FILE* out;
	// char* text;
} traceCfgState;

/*
	<DirectedGraph xmlns="http://schemas.microsoft.com/vs/2009/dgml"
				  Layout="Sugiyama" GraphDirection="TopToBottom">
	 <Nodes>
	   <Node  Id="a"  />
	   <Node  Id="b" Label="label" />
	   <Node  Id="c" />
	 </Nodes>
	 <Links>
	   <Link Source="a" Target="b" />
	   <Link Source="a" Target="c" />
	   <Link Source="b" Target="c" />
	 </Links>
   </DirectedGraph>
   */

static void traceCfgExprNode(CfgExprNode* expr, traceCfgState* state)
{
	if (expr->type != NULL)
	{
		fprintf(state->out, "[");
		writeXmlEscapedDataString(state->out, expr->type->name, INT_MAX);
		fprintf(state->out, "]");
	}
	fprintf(state->out, "%s(", &getStringCfgExprKind(expr->kind)[9]);

	switch (expr->kind)
	{
	case CFG_EXPR_ENTITY_ID: {
		if (expr->type == NULL)
		{
			fprintf(state->out, "&lt;%s&gt;", expr->payload.identifier);
		}
		else 
		{
			if (expr->type->kind == TYPE_FUNC)
			{
				fprintf(state->out, "func &lt;%s&gt;", expr->payload.function->name);
			}
			else if (expr->type->kind == TYPE_BUILTIN && expr->type->details.builtins.builtinKind == BUILTIN_TYPE_INVALID)
			{
				fprintf(state->out, "??? &lt;%s&gt;", expr->payload.identifier);
			}
			else 
			{
				fprintf(state->out, "var &lt;%s&gt;", expr->payload.valuePlace->name);
			}
		}
	} break;
	case CFG_EXPR_LITERAL_INT: fprintf(state->out, "&lt;%d&gt;", expr->payload.integer); break;
	case CFG_EXPR_LITERAL_CHAR: fprintf(state->out, "&lt;'%c'&gt;", expr->payload.character); break;
	case CFG_EXPR_LITERAL_FLOAT: fprintf(state->out, "&lt;%f&gt;", expr->payload.fractional); break;
	case CFG_EXPR_LITERAL_STRING: 
		//fprintf(state->out, "&lt;&quot;");
		fprintf(state->out, "&lt;");
		writeXmlEscapedDataString(state->out, expr->payload.string, INT_MAX);
		fprintf(state->out, "&gt;");
		//fprintf(state->out, "&quot;&gt;");
		break;
	default: /* do nothig */ break;
	}

	if (expr->argsCount > 0)
	{
		for (int i = 0; i < expr->argsCount; i++)
		{
			if (i > 0)
			{
				fprintf(state->out, ", ");
			}
		
			traceCfgExprNode(expr->args[i], state);
		}
	}
	else
	{
		// int len = node->ast->toLoc.position - node->ast->fromLoc.position;
		// char buff[len + 1];
		// memcpy(buff, &text[node->fromLoc.position], len);
		// buff[len] = 0;
		// writeXmlEscapedDataString(state->out, &state->text[node->ast->fromLoc.position], len);
	}

	fprintf(state->out, ")");
}

static void traceCfgExpr(CfgExprNode* node, traceCfgState* state)
{
	fprintf(state->out, "L%dC%d| ", node->ast->fromLoc.line, node->ast->fromLoc.column);
	traceCfgExprNode(node, state);
	fprintf(state->out, "&#10;");
}

static void traceCfgNode(CfgNode* node, traceCfgState* state)
{
	fprintf(state->out, "<Node Id=\"%d\" Label=\"#%d&#10;&#10;", node->id, node->id);
	traverseLinkedList(node->exprs, (action2)traceCfgExpr, state);


	if (node->conditionalBranch != NULL)
	{
		fprintf(state->out, "&#10;on condition to #%d", node->conditionalBranch->id);
	}
		
	if (node->defaultBranch != NULL)
	{
		fprintf(state->out, "&#10;default to #%d", node->defaultBranch->id);
	}

	if (node->isFinal)
	{
		if (node->isReturning)
		{
			fprintf(state->out, "&#10;returns value.");
		}
		else
		{
			fprintf(state->out, "&#10;returns.");
		}
	}

	fprintf(state->out, "\" />\n");
}

static void traceCfgNodeLinks(CfgNode* node, traceCfgState* state)
{
	if (node->conditionalBranch != NULL)
	{
		fprintf(state->out, "<Link Source=\"%d\" Target=\"%d\" />\n", node->id, node->conditionalBranch->id);
	}
	
	if (node->defaultBranch != NULL)
	{
		fprintf(state->out, "<Link Source=\"%d\" Target=\"%d\" />\n", node->id, node->defaultBranch->id);
	}
}

void traceControlFlowGraph(CfgInstance* cfg, FILE* out) //, char* text)
{
	traceCfgState state = {
		.out = out,
		// .text = text
	};
	fprintf(out, "<DirectedGraph xmlns=\"http://schemas.microsoft.com/vs/2009/dgml\" Layout=\"Sugiyama\" GraphDirection=\"TopToBottom\" >\n");
	fprintf(out, "<Nodes>\n");
	traverseLinkedList(cfg->nodes, (action2)traceCfgNode, (void*)&state);
	fprintf(out, "</Nodes>\n");
	fprintf(out, "<Links>\n");
	traverseLinkedList(cfg->nodes, (action2)traceCfgNodeLinks, (void*)&state);
	fprintf(out, "</Links>\n");
	fprintf(out, "</DirectedGraph>\n");
}

