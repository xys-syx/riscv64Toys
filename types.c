#include <stdlib.h>

#include "collections.h"

#include "types.h"
#undef TYPES_E_H
#define GENERATE_ENUM_STRINGS  // Start string generation
#include "types.h"
#undef GENERATE_ENUM_STRINGS   // Stop string generation



// same as riscv64-linux-gnu-gcc-10

const int _immaterialSize = -1;
const int _charSize = 1;
const int _smallIntSize = 2;
const int _intSize = 4;
const int _longIntSize = 8;
const int _longLongIntSize = 8;
const int _pointerSize = 8;
const int _boolSize = 1;
const int _floatSize = 4;
const int _doubleSize = 8;
const int _longDoubleSize = 16;
const int _floatComplexSize = 8;
const int _doubleComplexSize = 16;
const int _longDoubleComplexSize = 32;



typedef struct WellKnownTypeNamesTrieNode {
	int* tokenIds;
	struct WellKnownTypeNamesTrieNode** subnodes;
	TypeInfo* typeInfo;
} WellKnownTypeNamesTrieNode;

const int distinctTypeKeywordsCount = 15;

static int wellKnownTypeNames[][6] = {
	{ 1, AST_TYPE_VOID, 0 },
	{ 2, AST_TYPE_CHAR, 0 },
	{ 3, AST_TYPE_SIGNED, AST_TYPE_CHAR, 0 },
	{ 4, AST_TYPE_UNSIGNED, AST_TYPE_CHAR, 0 },
	{ 5, AST_TYPE_SHORT, 0 },
	{ 5, AST_TYPE_SIGNED, AST_TYPE_SHORT, 0 },
	{ 5, AST_TYPE_SHORT, AST_TYPE_INT, 0 },
	{ 5, AST_TYPE_SIGNED, AST_TYPE_SHORT, AST_TYPE_INT, 0 },
	{ 6, AST_TYPE_UNSIGNED, AST_TYPE_SHORT, 0 },
	{ 6, AST_TYPE_UNSIGNED, AST_TYPE_SHORT, AST_TYPE_INT, 0 },
	{ 7, AST_TYPE_INT, 0 },
	{ 7, AST_TYPE_SIGNED, 0 },
	{ 7, AST_TYPE_SIGNED, AST_TYPE_INT, 0 },
	{ 8, AST_TYPE_UNSIGNED, 0 },
	{ 8, AST_TYPE_UNSIGNED, AST_TYPE_INT, 0 },
	{ 9, AST_TYPE_LONG, 0 },
	{ 9, AST_TYPE_SIGNED, AST_TYPE_LONG, 0 },
	{ 9, AST_TYPE_LONG, AST_TYPE_INT, 0 },
	{ 9, AST_TYPE_SIGNED, AST_TYPE_LONG, AST_TYPE_INT, 0 },
	{ 10, AST_TYPE_UNSIGNED, AST_TYPE_LONG, 0 },
	{ 10, AST_TYPE_UNSIGNED, AST_TYPE_LONG, AST_TYPE_INT, 0 },
	{ 11, AST_TYPE_LONG, AST_TYPE_LONG, 0 },
	{ 11, AST_TYPE_SIGNED, AST_TYPE_LONG, AST_TYPE_LONG, 0 },
	{ 11, AST_TYPE_LONG, AST_TYPE_LONG, AST_TYPE_INT, 0 },
	{ 11, AST_TYPE_SIGNED, AST_TYPE_LONG, AST_TYPE_LONG, AST_TYPE_INT, 0 },
	{ 12, AST_TYPE_UNSIGNED, AST_TYPE_LONG, AST_TYPE_LONG, 0 },
	{ 12, AST_TYPE_UNSIGNED, AST_TYPE_LONG, AST_TYPE_LONG, AST_TYPE_INT, 0 },
	{ 13, AST_TYPE_FLOAT, 0 },
	{ 14, AST_TYPE_DOUBLE, 0 },
	{ 15, AST_TYPE_LONG, AST_TYPE_DOUBLE, 0 },
	{ 16, AST_TYPE_BOOL, 0 },
	{ 17, AST_TYPE_FLOAT, AST_TYPE_COMPLEX, 0 },
	{ 18, AST_TYPE_DOUBLE, AST_TYPE_COMPLEX, 0 },
	{ 19, AST_TYPE_LONG, AST_TYPE_DOUBLE, AST_TYPE_COMPLEX, 0 },
};

static TypeInfo* wellKnownTypeInfoById[35];
static WellKnownTypeNamesTrieNode* wellKnownTypeInfoByNameTrieRoot;

static WellKnownTypeNamesTrieNode* createWellKnownTypeNamesTrieNode(void)
{
	WellKnownTypeNamesTrieNode* node = allocStruct(WellKnownTypeNamesTrieNode);
	// TODO lazy instantiate these collections
	node->tokenIds = allocArray(int, distinctTypeKeywordsCount);
	node->subnodes = allocArray(WellKnownTypeNamesTrieNode*, distinctTypeKeywordsCount);
	memset(node->tokenIds, 0, distinctTypeKeywordsCount * sizeof(int));
	memset(node->subnodes, 0, distinctTypeKeywordsCount * sizeof(WellKnownTypeNamesTrieNode*));
	node->typeInfo = NULL;
	return node;
}

static void registerWellKnownTypeName(int typeName[])
{
	int typeId = typeName[0];
	int typeNameTokenIndex = 1;
	int typeNameTokenId = typeName[typeNameTokenIndex];
	WellKnownTypeNamesTrieNode* root = wellKnownTypeInfoByNameTrieRoot;

	WellKnownTypeNamesTrieNode* node = root;
	while (typeNameTokenId != 0)
	{
		int i = 0;
		int key = node->tokenIds[i];
		while (key != 0 && key != typeNameTokenId)
		{
			key = node->tokenIds[++i];
		}

		WellKnownTypeNamesTrieNode* subnode;
		if (key == 0)
		{
			node->tokenIds[i] = typeNameTokenId;
			node->subnodes[i] = subnode = createWellKnownTypeNamesTrieNode();
		}
		else
		{
			subnode = node->subnodes[i];
		}

		node = subnode;
		typeNameTokenId = typeName[++typeNameTokenIndex];
	}

	node->typeInfo = wellKnownTypeInfoById[typeId];
}

static bool typesInitialized = false;
static LinkedList* allTypes;
static RbTree* customTypesByName;

static TypeInfo* registerBuiltinType(char* name, int size, BuiltinTypeKind kind, bool isSigned)
{
	TypeInfo* info = allocStruct(TypeInfo);
	clearStructure(&info->derived);
	info->id = allTypes->count;
	info->name = name;
	info->instanceSize = size;
	info->kind = TYPE_BUILTIN;
	info->definitionAst = NULL;
	info->details.builtins.builtinKind = kind;
	info->details.builtins.isSigned = isSigned;
	wellKnownTypeInfoById[info->id] = info;
	addLastLinkedListItem(allTypes, info);
	return info;
}

static TypeInfo* builtinVoidType;

static void initTypes(void)
{
	if (!typesInitialized)
	{
		allTypes = createLinkedList();
		customTypesByName = createRbTreeByString();

		// standard signed integer types: 
		//  - signed char, 
		//  - short int, 
		//  - int, 
		//  - long int, 
		//  - long long int
		// real floating types: 
		//  - float,
		//  - double, 
		//  - long double
		// void* and char* of the same representation


		registerBuiltinType("<INVALID_TYPE>", _immaterialSize, BUILTIN_TYPE_INVALID, false); // 0
		builtinVoidType = registerBuiltinType("void", _immaterialSize, BUILTIN_TYPE_INVALID, false); // 1
		registerBuiltinType("char", _charSize, BUILTIN_TYPE_CHAR, true); // 2
		registerBuiltinType("signed char", _charSize, BUILTIN_TYPE_CHAR, true); // 3
		registerBuiltinType("unsigned char", _charSize, BUILTIN_TYPE_CHAR, false); // 4
		registerBuiltinType("signed short int", _smallIntSize, BUILTIN_TYPE_INT, true); // 5
		registerBuiltinType("unsigned short int", _smallIntSize, BUILTIN_TYPE_INT, false); // 6
		registerBuiltinType("signed int", _intSize, BUILTIN_TYPE_INT, true); // 7
		registerBuiltinType("unsigned int", _intSize, BUILTIN_TYPE_INT, false); // 8
		registerBuiltinType("signed long int", _longIntSize, BUILTIN_TYPE_INT, true); // 9
		registerBuiltinType("unsigned long int", _longIntSize, BUILTIN_TYPE_INT, false); // 10
		registerBuiltinType("signed long long int", _longLongIntSize, BUILTIN_TYPE_INT, true); // 11
		registerBuiltinType("unsigned long long int", _longLongIntSize, BUILTIN_TYPE_INT, false); // 12
		registerBuiltinType("float", _floatSize, BUILTIN_TYPE_FLOAT, true); // 13
		registerBuiltinType("double", _doubleSize, BUILTIN_TYPE_FLOAT, true); // 14
		registerBuiltinType("long double", _longDoubleSize, BUILTIN_TYPE_FLOAT, true); // 15
		registerBuiltinType("_Bool", _boolSize, BUILTIN_TYPE_BOOL, false); // 16
		registerBuiltinType("float _Complex", _floatComplexSize, BUILTIN_TYPE_COMPLEX, false); // 17
		registerBuiltinType("double _Complex", _doubleComplexSize, BUILTIN_TYPE_COMPLEX, false); // 18
		registerBuiltinType("long double _Complex", _longDoubleComplexSize, BUILTIN_TYPE_COMPLEX, false); // 19

		wellKnownTypeInfoByNameTrieRoot = createWellKnownTypeNamesTrieNode();
		for (int i = 0; i < (int)(sizeof(wellKnownTypeNames) / sizeof(wellKnownTypeNames[0])); i++)
		{
			registerWellKnownTypeName(wellKnownTypeNames[i]);
		}

		typesInitialized = true;
	}
}

TypeInfo* getBuiltinVoidType() { initTypes(); return builtinVoidType; }

TypeInfo* findBuiltinType(BuiltinTypeKind kind, int size, bool isSigned)
{
	for (LinkedListItem* item = allTypes->first; item != NULL; item = item->next)
	{
		TypeInfo* type = (TypeInfo*)item->data;
		if (type->kind != TYPE_BUILTIN)
			return (TypeInfo*)allTypes->first->data;

		BuiltinTypeKind builtinKind = type->details.builtins.builtinKind;
		if (((builtinKind != BUILTIN_TYPE_INT && builtinKind != BUILTIN_TYPE_CHAR) || type->details.builtins.isSigned == isSigned)
			&& builtinKind == kind 
			&& ((builtinKind != BUILTIN_TYPE_INT && builtinKind != BUILTIN_TYPE_FLOAT && builtinKind != BUILTIN_TYPE_COMPLEX) || type->instanceSize == size))
			return type;
	}

	return (TypeInfo*)allTypes->first->data;
}

TypeInfo* recognizeWellKnownType(AstNode** ast)
{
	initTypes();

	// TODO consider proposing known nearly matched alternatives 

	AstNode* keyword = *ast;

	WellKnownTypeNamesTrieNode* node = wellKnownTypeInfoByNameTrieRoot;
	while (node != NULL)
	{
		int token = keyword->kind;

		int i = 0;
		int key = node->tokenIds[i];
		while (key != 0 && key != token)
		{
			key = node->tokenIds[++i];
		}

		if (key == 0)
		{
			// unable to resolve the type name by the sequence of keywords - unexpected keyword met
			return NULL;
		}
		else
		{
			node = node->subnodes[i];
			keyword = keyword->next;

			if (keyword == NULL) // the sequence of keywords finished
			{
				if (node->typeInfo != NULL) // the type identified
				{
					return node->typeInfo;
				}
				else
				{
					// unable to resolve the type name by the sequence of keywords - the sequence of keyowrds is shorter than expected?
					return NULL;
				}
			}
			else
			{
				// there are more keywords to look at, proceed to the next iteration
			}
		}
	}

	// unable to resolve the type name by the sequence of keywords - the sequence of keywords is longer than expected?
	return NULL;
}

TypeInfo* makePointerType(TypeInfo* targetType)
{
	initTypes();
	if (targetType->derived.pointerType == NULL)
	{
		int targetTypeNameLen = strlen(targetType->name);
		char* name = allocArray(char, targetTypeNameLen + 2);
		strcpy(name, targetType->name);
		name[targetTypeNameLen] = '*';
		name[targetTypeNameLen + 1] = 0;

		TypeInfo* info = allocStruct(TypeInfo);
		clearStructure(&info->derived);
		info->id = allTypes->count;
		info->name = name;
		info->instanceSize = _pointerSize;
		info->definitionAst = NULL;
		info->kind = TYPE_POINTER;
		info->details.pointers.targetType = targetType;
		addLastLinkedListItem(allTypes, info);
		targetType->derived.pointerType = info;
	}
	return targetType->derived.pointerType;
}

TypeInfo* makeArrayType(TypeInfo* targetType, int length)
{
	initTypes();
	if (targetType->derived.arrayTypeByName == NULL)
		targetType->derived.arrayTypeByName = createRbTreeByString();

	const char* nameFormat = "%s[%d]";
	size_t nameLen = snprintf(NULL, 0, nameFormat, targetType->name, length);
	char* name = allocArray(char, nameLen + 1);
	sprintf(name, nameFormat, targetType->name, length);
	name[nameLen] = 0;

	TypeInfo* elementType = targetType->kind == TYPE_ARRAY ? targetType->details.arrays.elementType : targetType;
	TypeInfo* arrayType = (TypeInfo*)findRbTreeItem(elementType->derived.arrayTypeByName, name);
	if (arrayType == NULL)
	{
		TypeInfo* info = allocStruct(TypeInfo);
		clearStructure(&info->derived);
		info->id = allTypes->count;
		info->name = name;
		info->instanceSize = length * targetType->instanceSize;
		info->definitionAst = NULL;
		info->kind = TYPE_ARRAY;

		if (targetType->kind == TYPE_ARRAY)
		{
			int dimsCount = targetType->details.arrays.dimensions + 1;
			int* dims = allocArray(int, dimsCount);
			memcpy(dims, targetType->details.arrays.dimSize, sizeof(int) * (dimsCount - 1));
			dims[dimsCount] = length;

			info->details.arrays.elementType = elementType;
			info->details.arrays.dimensions = dimsCount;
			info->details.arrays.dimSize = dims;
		}
		else
		{
			int* dims = allocArray(int, 1);
			dims[0] = length;

			info->details.arrays.elementType = elementType;
			info->details.arrays.dimensions = 1;
			info->details.arrays.dimSize = dims;
		}
		addLastLinkedListItem(allTypes, info);
		tryAddRbTreeItem(elementType->derived.arrayTypeByName, name, info);
		arrayType = info;
	}
	else
	{
		free(name);
	}
	return arrayType;
}

static int compareInts(void* a, void* b)
{
	int x = *(int*)a;
	int y = *(int*)b;
	
	if (x < y)
		return -1;
	else if (x > y)
		return 1;
	else
		return 0;
}

static int compareSignatures(FunctionSignature* a, FunctionSignature* b);

static int compareTypes(TypeInfo* a, TypeInfo* b)
{
	int result;
	if (a == b || a->id == b->id)
		result = 0;
	else if (a->kind < b->kind)
		result = -1;
	else if (a->kind > b->kind)
		result = 1;
	else
	{
		switch (a->kind)
		{
		case TYPE_BUILTIN: {
			if (a->details.builtins.builtinKind < b->details.builtins.builtinKind)
				result = -1;
			else if (a->details.builtins.builtinKind > b->details.builtins.builtinKind)
				result = 1;
			else if (a->details.builtins.isSigned && !b->details.builtins.isSigned)
				result = -1;
			else if (!a->details.builtins.isSigned && b->details.builtins.isSigned)
				result = 1;
		} break;
		case TYPE_ARRAY: {
			result = compareTypes(a->details.arrays.elementType, b->details.arrays.elementType);
			if (result == 0)
			{
				result = compareInts(&a->details.arrays.dimensions, &b->details.arrays.dimensions);
				if (result == 0)
				{
					for (int i = 0; i < a->details.arrays.dimensions; i++)
					{
						result = compareInts(&a->details.arrays.dimSize[i], &b->details.arrays.dimSize[i]);
						if (result != 0)
							break;
					}
				}
			}
		} break;
		case TYPE_POINTER: {
			result = compareTypes(a->details.pointers.targetType, b->details.pointers.targetType);
		} break;
		case TYPE_FUNC: {
			result = compareSignatures(a->details.functions.signature, b->details.functions.signature);
		} break;
		case TYPE_STRUCT:
		case TYPE_UNION:
		case TYPE_ENUM: printError(NULL, "Type comparison not implemented for %s", getStringTypeKind(a->kind)); return false;
		default: printError(NULL, "Unexpected type kind %d\n", a->kind); return false;
		}
		return compareInts(&a->instanceSize, &b->instanceSize);
	}

	// printTrace(NULL, "Comparing %s with %s to %d", a->name, b->name, result);
	return result;
}

static int compareSignatures(FunctionSignature* a, FunctionSignature* b)
{
	if (a != b)
	{
		int rc = compareTypes(a->returnType, b->returnType);
		if (rc != 0)
			return rc;

		rc = compareInts(&a->parameters->places->count, &b->parameters->places->count);
		if (rc != 0)
			return rc;

		LinkedListItem* p = a->parameters->places->first;
		LinkedListItem* q = b->parameters->places->first;
		while (p != NULL && q != NULL)
		{
			rc = compareTypes(((ValuePlaceInfo*)p->data)->type, ((ValuePlaceInfo*)q->data)->type);
			if (rc != 0)
				return rc;

			p = p->next;
			q = q->next;
		}
	}
	return 0;
}

TypeInfo* makeFunctionType(FunctionSignature* signature, AstNode* ast)
{
	if (signature->returnType->derived.returningFunccTypeBySignature == NULL)
		signature->returnType->derived.returningFunccTypeBySignature = createRbTree((intFunc2)compareSignatures, NULL, NULL);

	TypeInfo* funcType = (TypeInfo*)findRbTreeItem(signature->returnType->derived.returningFunccTypeBySignature, signature);
	if (funcType == NULL)
	{
		LinkedList* l = createLinkedList();
		addLastLinkedListItem(l, "(");
		addLastLinkedListItem(l, signature->returnType->name);
		addLastLinkedListItem(l, ")");
		addLastLinkedListItem(l, "<func>(");
		for (LinkedListItem* item = signature->parameters->places->first; item != NULL; item = item->next)
		{
			addLastLinkedListItem(l, ((ValuePlaceInfo*)(item->data))->type->name);
			if (item->next != NULL)
				addLastLinkedListItem(l, ",");
		}
		addLastLinkedListItem(l, ")");
		char* name = concatListOfStrings(l);
		releaseLinkedList(l);

		initTypes();
		TypeInfo* info = allocStruct(TypeInfo);
		clearStructure(&info->derived);
		info->id = allTypes->count;
		info->name = name;
		info->instanceSize = _immaterialSize;
		info->definitionAst = ast;
		info->kind = TYPE_FUNC;
		info->details.functions.signature = signature;
		addLastLinkedListItem(allTypes, info);
		tryAddRbTreeItem(signature->returnType->derived.returningFunccTypeBySignature, signature, info);
		funcType = info;
	}
	return funcType;;
}

//TypeInfo* makeFunctionPointerType(FunctionSignature* signature)
//{
//	initTypes();
//	TypeInfo* info = allocStruct(TypeInfo);
//  clearStructure(&info->derived);
//	info->id = allTypes->count;
//	info->name = "TODO";
//	info->instanceSize = 4;
//	info->definitionAst = NULL;
//	info->kind = TYPE_FUNCPTR;
//	addLastLinkedListItem(allTypes, info);
//	return info;
//}

Declarations* createDeclarationsScope(Declarations* parent)
{
	Declarations* decls = allocStruct(Declarations);
	decls->parent = parent;
	decls->typesByName = createRbTreeByString();
	decls->structsByName = createRbTreeByString();
	decls->unionsByName = createRbTreeByString();
	decls->enumsByName = createRbTreeByString();
	return decls;
}

bool registerCustomType(TypeInfo* type, char* name)
{
	return tryAddRbTreeItem(customTypesByName, name, type);
}

TypeInfo* findCustomTypeByName(char* name)
{
	initTypes();
	return (TypeInfo*)findRbTreeItem(customTypesByName, name);
}

ValuePlacesMap* createValuePlacesMap()
{
	ValuePlacesMap* map = allocStruct(ValuePlacesMap);
	map->places = createLinkedList();
	map->placeByName = createRbTreeByString();
	return map;
}

ValuePlaceInfo* tryRegisterNewValuePlace(AstNode* ast, ValuePlacesMap* map, char* name, TypeInfo* type, SymbolFlags flags)
{
	ValuePlaceInfo* info = allocStruct(ValuePlaceInfo);
	info->id = map->places->count;
	info->name = name;
	info->type = type;
	info->flags = flags;
	info->ast = ast;

	if (name != NULL)
	{
		if (!tryAddRbTreeItem(map->placeByName, name, info))
		{
			free(info);
			return NULL;
		}
	}

	addLastLinkedListItem(map->places, info);
	return info;
}

ValuePlaceInfo* tryRegisterNewScopedValuePlace(AstNode* ast, ValuePlacesMap* map, ValuePlacesMap* scope, char* name, TypeInfo* type, SymbolFlags flags)
{
	ValuePlaceInfo* info = tryRegisterNewValuePlace(ast, scope, name, type, flags);
	if (info != NULL)
	{
		info->id = map->places->count;
		addLastLinkedListItem(map->places, info);
		return info;
	}
	else 
	{
		return NULL;
	}
}

FunctionSignature* createFunctionSignature(TypeInfo* returnType, ValuePlacesMap* params)
{
	FunctionSignature* signature = allocStruct(FunctionSignature);
	signature->parameters = params;
	signature->returnType = returnType;
	return signature;
}

static void traceTypeInfoImpl(TypeInfo* type, int depth)
{
	for (int i = 0; i < depth; i++)
		printf("  ");

	char* format = type->definitionAst == NULL ? "#%d %s %s " : "#%d %s %s @L%dC%d";
	int defLine = type->definitionAst == NULL ? 0 : type->definitionAst->fromLoc.line + 1;
	int defColumn = type->definitionAst == NULL ? 0 : type->definitionAst->fromLoc.column + 1;
	printf(format, type->id, getStringTypeKind(type->kind), type->name == NULL ? "<?>" : type->name, defLine, defColumn);
	switch (type->kind)
	{
	case TYPE_ARRAY: {
		//for (int i = 0; i < type->details.arrays.dimensions; i++)
		//	printf("[%d]", type->details.arrays.dimSize[i]);
		printf(" of \n");
		traceTypeInfoImpl(type->details.arrays.elementType, depth + 1);
	}; break;
	case TYPE_POINTER: {
		printf(" to \n");
		traceTypeInfoImpl(type->details.pointers.targetType, depth + 1);
	} break;
	case TYPE_BUILTIN: {
		printf(" %s %s\n", type->details.builtins.isSigned ? "signed" : "unsigned", getStringBuiltinTypeKind(type->details.builtins.builtinKind));
	} break;
	case TYPE_STRUCT: {
		printf("<not implemented>\n"); // TODO
	} break;
	case TYPE_UNION: {
		printf("<not implemented>\n"); // TODO
	} break;
	case TYPE_ENUM: {
		printf("<not implemented>\n"); // TODO
	} break;
	case TYPE_FUNC: {
		printf("\n"); // TODO
	} break;
	default: printf("Unexpected type kind %d\n", type->kind); break;
	}
}

static void traceTypeInfo(TypeInfo* type, void* arg)
{
	UNUSED(arg);
	traceTypeInfoImpl(type, 0);
}

void traceAllTypes()
{
	traverseLinkedList(allTypes, (action2)traceTypeInfo, NULL);
}

bool signaturesAreEqual(FunctionSignature* a, FunctionSignature* b)
{
	if (!typesAreEqual(a->returnType, b->returnType) || a->parameters->places->count != b->parameters->places->count)
		return false;

	for (LinkedListItem* ta = a->parameters->places->first, *tb = b->parameters->places->first;
		ta != NULL && tb != NULL;
		ta = ta->next, tb = tb->next)
	{
		if (!typesAreEqual((TypeInfo*)ta->data, (TypeInfo*)tb->data))
			return false;
	}

	return true;
}

bool typesAreEqual(TypeInfo* a, TypeInfo* b)
{
	return compareTypes(a, b) == 0;
}

