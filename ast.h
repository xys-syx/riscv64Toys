#include <stdio.h>

#include "utils.h"

/**
 * The Abstract Syntax Tree carries the information about all the actual syntax construct represented in a given source text.
 * AST consists of the hierarchy of AstNode instances.
 * All the information carried by each node populated during tree construction in a strong bottom-up order.
 *
 * * * * * * * * * * * * * * * * * * * * * */

#ifndef AST_E_H
#define AST_E_H

/// <summary>
/// AST node type code for all the parseable language features
/// </summary>
BEGIN_ENUM(AstNodeKinds)
{
	DECL_ENUM_ELEMENT_VAL(AST_ERROR, 0)
	DECL_ENUM_ELEMENT(AST_ID)
	DECL_ENUM_ELEMENT(AST_LITERAL_STRING)
	DECL_ENUM_ELEMENT(AST_LITERAL_INT)
	DECL_ENUM_ELEMENT(AST_LITERAL_FLOAT)
	DECL_ENUM_ELEMENT(AST_LITERAL_CHAR)
	DECL_ENUM_ELEMENT(AST_STMT_EMPTY)
	DECL_ENUM_ELEMENT(AST_STMT_BLOCK)
	DECL_ENUM_ELEMENT(AST_STMT_IF)
	DECL_ENUM_ELEMENT(AST_STMT_EXPR)
	DECL_ENUM_ELEMENT(AST_STMT_SWITCH)
	DECL_ENUM_ELEMENT(AST_STMT_WHILE)
	DECL_ENUM_ELEMENT(AST_STMT_FOR)
	DECL_ENUM_ELEMENT(AST_STMT_DO)
	DECL_ENUM_ELEMENT(AST_STMT_RETURN)
	DECL_ENUM_ELEMENT(AST_STMT_BREAK)
	DECL_ENUM_ELEMENT(AST_STMT_CONTINUE)
	DECL_ENUM_ELEMENT(AST_STMT_GOTO)
	DECL_ENUM_ELEMENT(AST_STMT_LABELED)
	DECL_ENUM_ELEMENT(AST_STMT_ERROR)
	DECL_ENUM_ELEMENT(AST_LABEL)
	DECL_ENUM_ELEMENT(AST_DEF_FUNCTION_HEAD)
	DECL_ENUM_ELEMENT(AST_DEF_FUNCTION_IMPL)
	DECL_ENUM_ELEMENT(AST_DEF_STRUCT)
	DECL_ENUM_ELEMENT(AST_DEF_TYPEDEF)
	DECL_ENUM_ELEMENT(AST_DEF_UNION)
	DECL_ENUM_ELEMENT(AST_DEF_ENUM)
	DECL_ENUM_ELEMENT(AST_EXPR_PRE_INC)
	DECL_ENUM_ELEMENT(AST_EXPR_PRE_DEC)
	DECL_ENUM_ELEMENT(AST_EXPR_POST_INC)
	DECL_ENUM_ELEMENT(AST_EXPR_POST_DEC)
	DECL_ENUM_ELEMENT(AST_EXPR_PLUS)
	DECL_ENUM_ELEMENT(AST_EXPR_MINUS)
	DECL_ENUM_ELEMENT(AST_EXPR_MUL)
	DECL_ENUM_ELEMENT(AST_EXPR_DIV)
	DECL_ENUM_ELEMENT(AST_EXPR_REM)
	DECL_ENUM_ELEMENT(AST_EXPR_ASSIGN)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_PLUS)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_MINUS)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_MUL)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_DIV)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_REM)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_BITS_XOR)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_BITS_AND)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_BITS_OR)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_BITS_SHL)
	DECL_ENUM_ELEMENT(AST_EXPR_ASS_BITS_SHR)
	DECL_ENUM_ELEMENT(AST_EXPR_CMP_EQ)
	DECL_ENUM_ELEMENT(AST_EXPR_CMP_NEQ)
	DECL_ENUM_ELEMENT(AST_EXPR_CMP_LT)
	DECL_ENUM_ELEMENT(AST_EXPR_CMP_GT)
	DECL_ENUM_ELEMENT(AST_EXPR_CMP_LTEQ)
	DECL_ENUM_ELEMENT(AST_EXPR_CMP_GTEQ)
	DECL_ENUM_ELEMENT(AST_EXPR_BOOL_NOT)
	DECL_ENUM_ELEMENT(AST_EXPR_BOOL_AND)
	DECL_ENUM_ELEMENT(AST_EXPR_BOOL_OR)
	DECL_ENUM_ELEMENT(AST_EXPR_BITS_INV)
	DECL_ENUM_ELEMENT(AST_EXPR_BITS_XOR)
	DECL_ENUM_ELEMENT(AST_EXPR_BITS_AND)
	DECL_ENUM_ELEMENT(AST_EXPR_BITS_OR)
	DECL_ENUM_ELEMENT(AST_EXPR_BITS_SHL)
	DECL_ENUM_ELEMENT(AST_EXPR_BITS_SHR)
	DECL_ENUM_ELEMENT(AST_EXPR_CONDITIONAL)
	DECL_ENUM_ELEMENT(AST_EXPR_UNARY_REF)
	DECL_ENUM_ELEMENT(AST_EXPR_UNARY_UNREF)
	DECL_ENUM_ELEMENT(AST_EXPR_UNARY_PLUS)
	DECL_ENUM_ELEMENT(AST_EXPR_UNARY_MINUS)
	DECL_ENUM_ELEMENT(AST_EXPR_INDEX)
	DECL_ENUM_ELEMENT(AST_EXPR_CALL)
	DECL_ENUM_ELEMENT(AST_EXPR_INIT)
	DECL_ENUM_ELEMENT(AST_EXPR_INIT_MEMBER)
	DECL_ENUM_ELEMENT(AST_EXPR_INIT_MEMBER_TARGET)
	DECL_ENUM_ELEMENT(AST_EXPR_INIT_MEMBER_TARGET_INDEX)
	DECL_ENUM_ELEMENT(AST_EXPR_INIT_MEMBER_TARGET_FIELD)
	DECL_ENUM_ELEMENT(AST_EXPR_CAST)
	DECL_ENUM_ELEMENT(AST_EXPR_ACCESS_DIRECT)
	DECL_ENUM_ELEMENT(AST_EXPR_ACCESS_PTR)
	DECL_ENUM_ELEMENT(AST_EXPR_SIZEOF)
	DECL_ENUM_ELEMENT(AST_EXPR_ALIGNOF)
	DECL_ENUM_ELEMENT(AST_EXPR_LIST)
	DECL_ENUM_ELEMENT(AST_GENERIC)
	DECL_ENUM_ELEMENT(AST_GENERIC_ENTRY)
	DECL_ENUM_ELEMENT(AST_GENERIC_DEFAULT_ENTRY)
	DECL_ENUM_ELEMENT(AST_LIST)
	DECL_ENUM_ELEMENT(AST_SPEC_ALIGNAS_TYPE)
	DECL_ENUM_ELEMENT(AST_SPEC_ALIGNAS_CONST)
	DECL_ENUM_ELEMENT(AST_FSPEC_KW_INLINE)
	DECL_ENUM_ELEMENT(AST_FSPEC_KW_NORETURN)
	DECL_ENUM_ELEMENT(AST_TSPEC_KW_CONST)
	DECL_ENUM_ELEMENT(AST_TSPEC_KW_RESTRICT)
	DECL_ENUM_ELEMENT(AST_TSPEC_KW_VOLATILE)
	DECL_ENUM_ELEMENT(AST_SSPEC_KW_TYPEDEF)
	DECL_ENUM_ELEMENT(AST_SSPEC_KW_EXTERN)
	DECL_ENUM_ELEMENT(AST_SSPEC_KW_STATIC)
	DECL_ENUM_ELEMENT(AST_SSPEC_KW_THREAD_LOCAL)
	DECL_ENUM_ELEMENT(AST_SSPEC_KW_AUTO)
	DECL_ENUM_ELEMENT(AST_SSPEC_KW_REGISTER)
	DECL_ENUM_ELEMENT(AST_TYPE_VOID)
	DECL_ENUM_ELEMENT(AST_TYPE_CHAR)
	DECL_ENUM_ELEMENT(AST_TYPE_SHORT)
	DECL_ENUM_ELEMENT(AST_TYPE_INT)
	DECL_ENUM_ELEMENT(AST_TYPE_LONG)
	DECL_ENUM_ELEMENT(AST_TYPE_FLOAT)
	DECL_ENUM_ELEMENT(AST_TYPE_DOUBLE)
	DECL_ENUM_ELEMENT(AST_TYPE_SIGNED)
	DECL_ENUM_ELEMENT(AST_TYPE_UNSIGNED)
	DECL_ENUM_ELEMENT(AST_TYPE_BOOL)
	DECL_ENUM_ELEMENT(AST_TYPE_COMPLEX)
	DECL_ENUM_ELEMENT(AST_TYPE_IMAGINARY)
	DECL_ENUM_ELEMENT(AST_TYPE_NAMED)
	DECL_ENUM_ELEMENT(AST_TYPE_UNION)
	DECL_ENUM_ELEMENT(AST_TYPE_STRUCT)
	DECL_ENUM_ELEMENT(AST_TYPE_ENUM)
	DECL_ENUM_ELEMENT(AST_ENUM_ENTRY)
	DECL_ENUM_ELEMENT(AST_DECL_SPECS)
	DECL_ENUM_ELEMENT(AST_DECLARATION)
	DECL_ENUM_ELEMENT(AST_DECLARATION_PTR_SPEC)
	DECL_ENUM_ELEMENT(AST_DECLARATION_ENTRY)
	DECL_ENUM_ELEMENT(AST_DECLARATION_ARRAY_SPEC)
	DECL_ENUM_ELEMENT(AST_DECLARATION_PARAMS_SPEC)
	DECL_ENUM_ELEMENT(AST_DECLARATION_PARAM_ENTRY)
	DECL_ENUM_ELEMENT(AST_DECLARATION_PARAM_ELLIPSIS)
	DECL_ENUM_ELEMENT(AST_DECLARATION_VALUE_PLACE)
	DECL_ENUM_ELEMENT(AST_STATIC_ASSERT)
	DECL_ENUM_ELEMENT(AST_TODO)
}
END_ENUM(AstNodeKinds)

/// <summary>
/// Reduced AST node type code for node' purpose classification
/// </summary>
/// <param name=""></param>
BEGIN_ENUM(AstNodeKindFamily)
{
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_EXPR)
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_STATEMENT)
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_VAR_DECL)
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_TYPE_DECL)
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_FUNC_DECL)
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_FUNC_IMPL)
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_UTIL)
	DECL_ENUM_ELEMENT(AST_KIND_FAMILY_TODO)
}
END_ENUM(AstNodeKindFamily)

#endif

#ifndef AST_H
#define AST_H

/// <summary>
/// The location in the parsed source text
/// </summary>
typedef struct {
	int line, column, position;
} SourceLocation;


typedef int AstNodeKind; // There is a consideration on explicit int usage for enum representation, so here it is... though doesn't helps with type checking

/// <summary>
/// The node of the AST
/// </summary>
typedef struct AstNode {
	/// The kind of syntax construct represented by this node
	AstNodeKind kind;
	/// The depth of the stack required to traverse the whole subtree
	int stackDepthRequired;
	/// The subtree depth and the immediate children count of this node
	int depth, childrenCount;
	/// The range of source locations covered by the explicitly represented childrens of this node
	SourceLocation fromLoc, toLoc;
	/// The text fragment payload associated with the node, a terminal sequence typically when exists
	char* payload;
	/// The reference to the next AST node in a parent's children nodes list
	struct AstNode* next;
	/// The reference to the first child node belonging to this node 
	struct AstNode* firstChild;
	/// The reference to the last child node belonging to this node
	struct AstNode* lastChild;
} AstNode;

/// <summary>
/// Costruct a new AST node based on the kind a list of childrens ended with the NULL
/// </summary>
AstNode* makeAstNode(AstNodeKind kind, ...);

/// <summary>
/// Construct a new terminal AST node capturing the payload from the text
/// </summary>
AstNode* makeAstTerm(AstNodeKind kind, char* payload);

/// <summary>
/// Modify the existing AST node by inserting new child node at the begginning of the child nodes sequence
/// </summary>
AstNode* prependAstChild(AstNode* node, AstNode* child);

/// <summary>
/// Modify the existing AST node by inserting new child node at the end of the child nodes sequence
/// </summary>
AstNode* appendAstChild(AstNode* node, AstNode* child);

/// <summary>
/// Reduce the scope of node' kind for a shorter selection-logic (switch-statements with fewer branches)
/// </summary>
int classifyAstNode(AstNode* node);

/// <summary>
/// Trace the AST tree to the given file by loop-based depth-first traverse
/// </summary>
void traceAst(AstNode* root, FILE* out);

/// <summary>
/// Trace the AST tree to the given file recursion-based traverse
/// </summary>
void traceAstRecursively(AstNode* node, FILE* out);

/// <summary>
/// Release all the memory allocations associated with the AST
/// </summary>
void cleanupAst(AstNode* root);

/// <summary>
/// Print the formatted error message and increment the errors count
/// </summary>
void printError(AstNode* ast, const char* fmt, ...);

/// <summary>
/// Print the formatted trace message for a debugging purposes
/// </summary>
void printTrace(AstNode* ast, const char* fmt, ...);

/// <summary>
/// Register type name for further identifier VS typename disambiguation
/// </summary>
/// <param name="declarator"></param>
/// <returns></returns>
AstNode* registerTypeName(AstNode* declarator);

/// <summary>
/// Disambiguate the identifier interpretation
/// </summary>
bool isTypeName(char* name);

#endif
