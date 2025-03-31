#include "ast.h"
#include "types.h"
#include "collections.h"

/**
 * The primary IR in this compiler consists of two pieces:
 *  - per-function control-flow graph (CFG);
 *  - per-statement expression trees.
 * 
 * CFG describes the branching logic derived from the source text by analysing the statements represented in the AST.
 * Each CFG node represents a control-flow basic block, which corresponds to a number of consequent comutation steps represeted with expression trees. 
 * 
 * Expression-trees describe the actual computational activities in a program derived from the source text by analysing the expressions represeted in the AST.
 * Depending on the analysis stage, the expression node carries various information:
 *	- on pre-analysis stage it describes a direct extraction from AST but restricted with a reduced amount of node kinds
 *  - on a post-analysis stage it carries type info and references entity descriptions (value-places and functions) instead of the pure identifiers 
 * 
 * * * * * * * * * * * * * * * * * * * * * */

#ifndef CFG_E_H
#define CFG_E_H

/// <summary>
/// Expression tree node type code for all the modelled logic constructs
/// </summary>
BEGIN_ENUM(CfgExprKind)
{
	DECL_ENUM_ELEMENT(CFG_EXPR_LITERAL_INT)
	DECL_ENUM_ELEMENT(CFG_EXPR_LITERAL_STRING)
	DECL_ENUM_ELEMENT(CFG_EXPR_LITERAL_CHAR)
	DECL_ENUM_ELEMENT(CFG_EXPR_LITERAL_FLOAT)
	DECL_ENUM_ELEMENT(CFG_EXPR_ADD)
	DECL_ENUM_ELEMENT(CFG_EXPR_SUB)
	DECL_ENUM_ELEMENT(CFG_EXPR_MUL)
	DECL_ENUM_ELEMENT(CFG_EXPR_DIV)
	DECL_ENUM_ELEMENT(CFG_EXPR_REM)
	DECL_ENUM_ELEMENT(CFG_EXPR_ASSIGN)
	DECL_ENUM_ELEMENT(CFG_EXPR_COALESCE)
	DECL_ENUM_ELEMENT(CFG_EXPR_PRESERVE)
	DECL_ENUM_ELEMENT(CFG_EXPR_CMP_EQ)
	DECL_ENUM_ELEMENT(CFG_EXPR_CMP_NEQ)
	DECL_ENUM_ELEMENT(CFG_EXPR_CMP_LT)
	DECL_ENUM_ELEMENT(CFG_EXPR_CMP_GT)
	DECL_ENUM_ELEMENT(CFG_EXPR_CMP_LTEQ)
	DECL_ENUM_ELEMENT(CFG_EXPR_CMP_GTEQ)
	DECL_ENUM_ELEMENT(CFG_EXPR_BOOL_NOT)
	DECL_ENUM_ELEMENT(CFG_EXPR_BOOL_AND)
	DECL_ENUM_ELEMENT(CFG_EXPR_BOOL_OR)
	DECL_ENUM_ELEMENT(CFG_EXPR_BITS_INV)
	DECL_ENUM_ELEMENT(CFG_EXPR_BITS_XOR)
	DECL_ENUM_ELEMENT(CFG_EXPR_BITS_AND)
	DECL_ENUM_ELEMENT(CFG_EXPR_BITS_OR)
	DECL_ENUM_ELEMENT(CFG_EXPR_BITS_SHL)
	DECL_ENUM_ELEMENT(CFG_EXPR_BITS_SHR)
	DECL_ENUM_ELEMENT(CFG_EXPR_UNARY_REF)
	DECL_ENUM_ELEMENT(CFG_EXPR_UNARY_UNREF)
	DECL_ENUM_ELEMENT(CFG_EXPR_UNARY_PLUS)
	DECL_ENUM_ELEMENT(CFG_EXPR_UNARY_MINUS)
	DECL_ENUM_ELEMENT(CFG_EXPR_INDEX)
	DECL_ENUM_ELEMENT(CFG_EXPR_CALL)
	DECL_ENUM_ELEMENT(CFG_EXPR_CAST)
	DECL_ENUM_ELEMENT(CFG_EXPR_ACCESS_DIRECT)	// for rewrite
	DECL_ENUM_ELEMENT(CFG_EXPR_ACCESS_PTR)		// for rewrite
	DECL_ENUM_ELEMENT(CFG_EXPR_SIZEOF)			// for rewrite
	DECL_ENUM_ELEMENT(CFG_EXPR_ALIGNOF)			// for rewrite
	DECL_ENUM_ELEMENT(CFG_EXPR_ERROR)
	DECL_ENUM_ELEMENT(CFG_EXPR_ENTITY_ID)
	// TODO introduce load-store operations on the analysis stage, when we are doing the validation already, and simplify the code generator
	//DECL_ENUM_ELEMENT(CFG_EXPR_LOAD_LOCAL)
	//DECL_ENUM_ELEMENT(CFG_EXPR_LOAD_PARAM)
	//DECL_ENUM_ELEMENT(CFG_EXPR_LOAD_GLOBAL)
	//DECL_ENUM_ELEMENT(CFG_EXPR_STORE_LOCAL)
	//DECL_ENUM_ELEMENT(CFG_EXPR_STORE_PARAM)
	//DECL_ENUM_ELEMENT(CFG_EXPR_STORE_GLOBAL)
	DECL_ENUM_ELEMENT(CFG_EXPR_RET)
}
END_ENUM(CfgExprKind)


#endif

#ifndef CFG_H
#define CFG_H

/// <summary>
/// The lexical scope for each control-flow basic block
/// </summary>
typedef struct CfgScope {
	/// The reference to the parent scope for a progressive identifiers resolving
	struct CfgScope* parent;
	/// Local declarations
	Declarations* declarations;
	/// Local variables
	ValuePlacesMap* vars;
	/// Local goto-labels to CFG nodes mapping for explicit goto-statements resolving
	RbTree* nodesByLabelName;
	/// The current loop' explicit control flow break jump target
	struct CfgNode* breakTarget;
	/// The current loop' explicit control flow continuation jump target
	struct CfgNode* continueTarget;
} CfgScope;

/// <summary>
/// The context-specific information associated with the expression node
/// </summary>
typedef union {
	char* string;
	int integer;
	double fractional;
	char character;
	char* identifier;
	ValuePlaceInfo* valuePlace;
	struct Function* function;
} CfgExprPayload;

/// <summary>
/// The expression-tree node
/// </summary>
typedef struct CfgExprNode {
	/// The reference to the AST node defining this expression
	AstNode* ast;
	/// The kind of expression or computational operation represented by this node
	CfgExprKind kind;
	/// The array of immediate operands of this expression 
	struct CfgExprNode** args;
	/// The amount of immediate operands of this expression 
	int argsCount;
	/// The depth of the expression subtree
	int depth;
	/// The type information associated with this expression after the analysis stage
	TypeInfo* type;
	/// The context-specific information which may be different on a various stages
	CfgExprPayload payload;
	// bool isReachable; // TODO support the conditional ternary operator
} CfgExprNode;

/// <summary>
/// The explicit default payload constructor
/// </summary>
CfgExprPayload makeEmptyCfgPayload(void);

/// <summary>
/// Create an expression-tree node
/// </summary>
CfgExprNode* createCfgExpr(AstNode* ast, CfgExprKind kind, CfgExprNode** args, int argsCount, CfgExprPayload payload);

/// <summary>
/// Create a literal-value-based expression-tree node with the given payload
/// </summary>
CfgExprNode* prepareLiteralExpression(AstNode* ast, CfgExprKind exprKind, CfgExprPayload payload);

/// <summary>
/// Create an expression-tree node for the unary operation
/// </summary>
CfgExprNode* makeUnaryExpression(AstNode* ast, CfgExprKind exprKind, CfgExprNode* arg);

/// <summary>
/// Create an expression-tree node for the binary operation
/// </summary>
CfgExprNode* makeBinaryExpression(AstNode* ast, CfgExprKind exprKind, CfgExprNode* a, CfgExprNode* b);

/// <summary>
/// The node of the cotrol-flow graph (basic block)
/// </summary>
typedef struct CfgNode {
	/// Numberical id for labeling purposes
	int id;
	/// The reference to the AST node describing the syntax construct responsible for the control-flow pattern
	AstNode* ast;
	/// The list of the expression-trees associated with this CFG node, describes the nonbreakable sequence of computation operations
	LinkedList* exprs;
	/// The flag describing the reachability of the CFG node during CFG cleanup
	bool isReachable;
	/// The flag denoting the exit-points in CFG
	bool isFinal;
	/// The flag denoting the presence of exit value contruction
	bool isReturning;
	/// The evaluation stack depth required to interpret all the expression-trees belonging to this node
	int stackDepth;
	/// The reference to the CFG node being a target of conditional control-flow transfer
	struct CfgNode* defaultBranch;
	/// The reference to the CFG node being a target of unconditional of default control-flow transfer
	struct CfgNode* conditionalBranch;
	/// The associated lexical scope
	CfgScope* scope;
} CfgNode;

/// <summary>
/// The function CFG
/// </summary>
typedef struct CfgInstance {
	/// Control-flow start node
	CfgNode* start;
	/// The list of CFG nodes as they are constructed during AST traversing
	LinkedList* nodes;
	/// The complete list of all the variables defined in a function
	ValuePlacesMap* vars;
	/// The function lexical scope
	CfgScope* scope;
} CfgInstance;

struct ProgramUnit; // forward-declaration for a program model

/// <summary>
/// Remove all the nodes not marked as reachable and not carrying any useful expression-trees, presenving the control-flow information
/// </summary>
void removeUnnecessaryNodes(CfgInstance* cfg);

/// <summary>
/// Traverse the CFG from the start node and mark all the actually reachable nodes
/// </summary>
void performControlFlowReachabilityTraverse(CfgInstance* cfg);

/// <summary>
/// Build the control-flow graph for a given syntax construct in the given program context
/// </summary>
CfgInstance* prepareControlFlowGraph(struct ProgramUnit* model, AstNode* exprOrStmt);

/// <summary>
/// Release all the memory allocations associated with the CFG
/// </summary>
void releaseControlFlowGraph(CfgInstance* cfg);

/// <summary>
/// Trace the CFG to the given file
/// </summary>
void traceControlFlowGraph(CfgInstance* cfg, FILE* out);

#endif
