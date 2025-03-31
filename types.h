#include "utils.h"
#include "ast.h"
#include "model.h"

#ifndef TYPES_E_H
#define TYPES_E_H

/// <summary>
/// The classification of builtin types
/// </summary>
BEGIN_ENUM(BuiltinTypeKind)
{
	DECL_ENUM_ELEMENT(BUILTIN_TYPE_INVALID)
	DECL_ENUM_ELEMENT(BUILTIN_TYPE_CHAR)
	DECL_ENUM_ELEMENT(BUILTIN_TYPE_INT)
	DECL_ENUM_ELEMENT(BUILTIN_TYPE_FLOAT)
	DECL_ENUM_ELEMENT(BUILTIN_TYPE_BOOL)
	DECL_ENUM_ELEMENT(BUILTIN_TYPE_COMPLEX)
}
END_ENUM(BuiltinTypeKind)

/// <summary>
/// The basic classification of types
/// </summary>
BEGIN_ENUM(TypeKind)
{
	DECL_ENUM_ELEMENT(TYPE_ARRAY)
	DECL_ENUM_ELEMENT(TYPE_POINTER)
	DECL_ENUM_ELEMENT(TYPE_BUILTIN)
	DECL_ENUM_ELEMENT(TYPE_STRUCT)
	DECL_ENUM_ELEMENT(TYPE_UNION)
	DECL_ENUM_ELEMENT(TYPE_ENUM)
	DECL_ENUM_ELEMENT(TYPE_FUNC)
	// DECL_ENUM_ELEMENT(TYPE_FUNCPTR)
}
END_ENUM(TypeKind)

#endif

#ifndef TYPES_H
#define TYPES_H

/// <summary>
/// Extra information about the value place
/// </summary>
typedef struct {
	bool isImported;
	bool isImplemented;
	bool isExported;
} SymbolFlags;

/// <summary>
/// Value place description (variable or function parameters)
/// </summary>
typedef struct {
	int id;
	char* name;
	struct TypeInfo* type;
	SymbolFlags flags;
	AstNode* ast;
} ValuePlaceInfo;

/// <summary>
/// A collections of value place descriptions in a certain area
/// </summary>
typedef struct {
	LinkedList* places;
	RbTree* placeByName;
} ValuePlacesMap;

/// <summary>
/// The representation of information about a function signature
/// </summary>
typedef struct FunctionSignature {
	struct TypeInfo* returnType;
	ValuePlacesMap* parameters;
} FunctionSignature;

/// <summary>
/// Declarations scope carrying the type information on all the defintions in a particular lexical area
/// </summary>
typedef struct Declarations {
	struct Declarations* parent;
	RbTree* typesByName;
	RbTree* structsByName;
	RbTree* unionsByName;
	RbTree* enumsByName;
} Declarations;

/// <summary>
/// Create a new declarations scope having a given parent reference
/// </summary>
Declarations* createDeclarationsScope(Declarations* parent);

/// <summary>
/// A type description
/// </summary>
typedef struct TypeInfo {
	/// Numberical identifier of the type for a debugging purposes
	int id;
	/// The human-readable name of the type
	char* name;
	/// The size of the raw type instance in bytes
	int instanceSize;
	/// The kind of this type describing its nature and corresponding details being associated
	TypeKind kind;

	union {
		struct {
			/// The type of the array' element
			struct TypeInfo* elementType;
			/// The amount of array' dimensions
			int dimensions;
			/// The array holding a size for each of the array' dimensions
			int* dimSize;
		} arrays;
		struct {
			/// The type at instance of which this pointer points to ('int' for 'int*' and so on)
			struct TypeInfo* targetType;
		} pointers;
		struct {
			/// The kind of the builtin type
			BuiltinTypeKind builtinKind;
			/// The signedness of a builtin numberic type
			bool isSigned;
		} builtins;
		struct {
			/// The array of value-places belonging to the structure instance
			ValuePlaceInfo* fields;
			/// The amount of fields in the structure instance
			int fieldsCount;
		} structures;
		struct {
			/// The array of virtual value-places treating the contents of the union instance
			ValuePlaceInfo* fields;
			/// The amount of virtual value-places in the union instance
			int fieldsCount;
		} unions;
		// struct {
		// TODO 
		// } enums;
		struct {
			/// The header signature of a function type
			FunctionSignature* signature;
		} functions;
	} details;

	/// A reference to the syntax construct declaring this type for the first time, exists only for a custom types
	AstNode* definitionAst;

	/// A collections of types derived from this, used for deduplication purposes
	struct {
		struct TypeInfo* pointerType;
		RbTree* arrayTypeByName;
		RbTree* returningFunccTypeBySignature;
	} derived;
} TypeInfo;

/// <summary>
/// Obtain the builin Void type info
/// </summary>
TypeInfo* getBuiltinVoidType(void);

/// <summary>
/// Obtain the builin type info by its capabilities
/// </summary>
TypeInfo* findBuiltinType(BuiltinTypeKind kind, int size, bool isSigned);

/// <summary>
/// Obtain the builin type info by its specification' syntax recognition
/// </summary>
TypeInfo* recognizeWellKnownType(AstNode** ast);

/// <summary>
/// Obtain a pointer type info
/// </summary>
TypeInfo* makePointerType(TypeInfo* targetType);

/// <summary>
/// Obtain an array type info
/// </summary>
TypeInfo* makeArrayType(TypeInfo* targetType, int length);

/// <summary>
/// Obtain a function type info
/// </summary>
TypeInfo* makeFunctionType(FunctionSignature* signature, AstNode* ast);

/// <summary>
/// Obtain a function pointer type info
/// </summary>
// TypeInfo* makeFunctionPointerType(FunctionSignature* signature); // seems not needed as we'll have pointer type for a function type

/// <summary>
/// Introduce an explicit user-defined type (see typedef)
/// </summary>
bool registerCustomType(TypeInfo* type, char* name);

/// <summary>
/// Obtain a user-defined type info
/// </summary>
TypeInfo* findCustomTypeByName(char* name);

/// <summary>
/// Create a new instance of value-places collection
/// </summary>
ValuePlacesMap* createValuePlacesMap(void);

/// <summary>
/// Register a new value-place info into the given value-places collection
/// </summary>
ValuePlaceInfo* tryRegisterNewValuePlace(AstNode* ast, ValuePlacesMap* map, char* name, TypeInfo* type, SymbolFlags flags);

/// <summary>
/// Register a new value-place info into the given scope value-places collection also introducing to the given map's list anonymously (thus making it available not for resolving but for introspection)
/// </summary>
ValuePlaceInfo* tryRegisterNewScopedValuePlace(AstNode* ast, ValuePlacesMap* map, ValuePlacesMap* scope, char* name, TypeInfo* type, SymbolFlags flags);

/// <summary>
/// Create a new function signature description
/// </summary>
FunctionSignature* createFunctionSignature(TypeInfo* returnType, ValuePlacesMap* params);

/// <summary>
/// Print all the known types information to the standard output for a debugging purposes
/// </summary>
/// <param name=""></param>
void traceAllTypes(void);

/// <summary>
/// The function signature comparison
/// </summary>
/// <returns>true if the given signatures are equal by definition</returns>
bool signaturesAreEqual(FunctionSignature* a, FunctionSignature* b);

/// <summary>
/// Types equility check
/// </summary>
/// <returns>true if the given types are equal by definition</returns>
bool typesAreEqual(TypeInfo* a, TypeInfo* b);

#endif


