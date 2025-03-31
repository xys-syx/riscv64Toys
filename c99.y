%locations
%define parse.error verbose
%{

#include <stdio.h>

#include "ast.h"

#define YYERROR_VERBOSE 1

extern AstNode* ast; // to capture the AST root
extern int yylineno; 

int yylex(void);
void yyerror(const char *s);


%}


%token	<text>	IDENTIFIER
%token	<text>	I_CONSTANT
%token	<text>	F_CONSTANT
%token	<text>	STRING_LITERAL
%token	<text>	FUNC_NAME
%token	<text>	SIZEOF
%token	<text>	PTR_OP
%token	<text>	INC_OP 
%token	<text>	DEC_OP 
%token	<text>	LEFT_OP 
%token	<text>	RIGHT_OP 
%token	<text>	LE_OP 
%token	<text>	GE_OP 
%token	<text>	EQ_OP 
%token	<text>	NE_OP
%token	<text>	AND_OP 
%token	<text>	OR_OP 
%token	<text>	MUL_ASSIGN 
%token	<text>	DIV_ASSIGN 
%token	<text>	MOD_ASSIGN 
%token	<text>	ADD_ASSIGN
%token	<text>	SUB_ASSIGN 
%token	<text>	LEFT_ASSIGN 
%token	<text>	RIGHT_ASSIGN 
%token	<text>	AND_ASSIGN
%token	<text>	XOR_ASSIGN 
%token	<text>	OR_ASSIGN
%token	<text>	TYPEDEF_NAME
%token	<text>	ENUMERATION_CONSTANT

%token	<text>	TYPEDEF 
%token	<text>	EXTERN 
%token	<text>	STATIC 
%token	<text>	AUTO 
%token	<text>	REGISTER 
%token	<text>	INLINE
%token	<text>	CONST 
%token	<text>	RESTRICT 
%token	<text>	VOLATILE
%token	<text>	BOOL 
%token	<text>	CHAR 
%token	<text>	SHORT 
%token	<text>	INT 
%token	<text>	LONG 
%token	<text>	SIGNED 
%token	<text>	UNSIGNED 
%token	<text>	FLOAT 
%token	<text>	DOUBLE 
%token	<text>	VOID
%token	<text>	COMPLEX 
%token	<text>	IMAGINARY 
%token	<text>	STRUCT 
%token	<text>	UNION 
%token	<text>	ENUM 
%token	<text>	ELLIPSIS

%token	<text>	CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token	<text>	ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL


%union
{
    AstNode* node;
    AstNodeKind kind;
	char* text;
}

%type <node> primary_expression
%type <node> constant
%type <node> enumeration_constant
%type <node> string 
%type <node> generic_selection
%type <node> generic_assoc_list
%type <node> generic_association
%type <node> postfix_expression
%type <node> argument_expression_list
%type <node> unary_expression
%type <kind> unary_operator
%type <node> cast_expression
%type <node> multiplicative_expression
%type <node> additive_expression
%type <node> shift_expression
%type <node> relational_expression
%type <node> equality_expression
%type <node> and_expression
%type <node> exclusive_or_expression
%type <node> inclusive_or_expression
%type <node> logical_and_expression
%type <node> logical_or_expression
%type <node> conditional_expression
%type <node> assignment_expression
%type <kind> assignment_operator
%type <node> expression
%type <node> constant_expression
%type <node> declaration
%type <node> declaration_specifiers
%type <node> init_declarator_list
%type <node> init_declarator
%type <node> storage_class_specifier
%type <node> type_specifier
%type <node> struct_or_union_specifier
%type <kind> struct_or_union
%type <node> struct_declaration_list
%type <node> struct_declaration
%type <node> specifier_qualifier_list
%type <node> struct_declarator_list
%type <node> struct_declarator
%type <node> enum_specifier
%type <node> enumerator_list
%type <node> enumerator
%type <node> type_qualifier
%type <node> function_specifier
%type <node> alignment_specifier
%type <node> declarator
%type <node> direct_declarator
%type <node> pointer
%type <node> type_qualifier_list
%type <node> parameter_type_list
%type <node> parameter_list
%type <node> parameter_declaration
%type <node> identifier_list											
%type <node> type_name
%type <node> abstract_declarator
%type <node> direct_abstract_declarator
%type <node> initializer
%type <node> initializer_list
%type <node> designation
%type <node> designator_list
%type <node> designator
%type <node> static_assert_declaration
%type <node> statement
%type <node> labeled_statement
%type <node> compound_statement
%type <node> block_item_list
%type <node> block_item
%type <node> expression_statement
%type <node> selection_statement
%type <node> iteration_statement
%type <node> jump_statement
%type <node> translation_unit
%type <node> external_declaration
%type <node> function_definition
%type <node> declaration_list

%start translation_unit

%nonassoc P_THEN
%nonassoc ELSE

%%


primary_expression
	: IDENTIFIER			{ $$ = makeAstTerm(AST_ID, $1); }
	| constant				{ $$ = $1; }
	| string				{ $$ = $1; }
	| '(' expression ')'	{ $$ = $2; }
	| generic_selection		{ $$ = $1; }
	;

constant
	: I_CONSTANT			{ $$ = makeAstTerm(AST_LITERAL_INT, $1); }/* includes character_constant */
	| F_CONSTANT			{ $$ = makeAstTerm(AST_LITERAL_FLOAT, $1); }
	| ENUMERATION_CONSTANT	{ $$ = makeAstTerm(AST_ID, $1); }		/* after it has been defined as such */
	;

enumeration_constant		/* before it has been defined as such */
	: IDENTIFIER			{ $$ = makeAstTerm(AST_ID, $1); }
	;

string
	: STRING_LITERAL		{ $$ = makeAstTerm(AST_LITERAL_STRING, $1); }
	| FUNC_NAME				{ $$ = makeAstTerm(AST_ID, $1); }
	;

generic_selection
	: GENERIC '(' assignment_expression ',' generic_assoc_list ')'	{ $$ = makeAstNode(AST_GENERIC, $3, $5, NULL); }
	;

generic_assoc_list
	: generic_association									{ $$ = makeAstNode(AST_LIST, $1, NULL); }
	| generic_assoc_list ',' generic_association			{ $$ = appendAstChild($1, $3); }
	;

generic_association
	: type_name ':' assignment_expression					{ $$ = makeAstNode(AST_GENERIC_ENTRY, $1, $3, NULL); }
	| DEFAULT ':' assignment_expression						{ $$ = makeAstNode(AST_GENERIC_DEFAULT_ENTRY, $3, NULL); }
	;

postfix_expression
	: primary_expression									{ $$ = $1; }
	| postfix_expression '[' expression ']'					{ $$ = makeAstNode(AST_EXPR_INDEX, $1, $3, NULL); }
	| postfix_expression '(' ')'							{ $$ = makeAstNode(AST_EXPR_CALL, $1, NULL); }
	| postfix_expression '(' argument_expression_list ')'	{ $$ = makeAstNode(AST_EXPR_CALL, $1, $3, NULL); }
	| postfix_expression '.' IDENTIFIER						{ $$ = makeAstNode(AST_EXPR_ACCESS_DIRECT, $1, makeAstTerm(AST_ID, $3), NULL); }
	| postfix_expression PTR_OP IDENTIFIER					{ $$ = makeAstNode(AST_EXPR_ACCESS_PTR, $1, makeAstTerm(AST_ID, $3), NULL); }
	| postfix_expression INC_OP								{ $$ = makeAstNode(AST_EXPR_POST_INC, $1, NULL); }
	| postfix_expression DEC_OP								{ $$ = makeAstNode(AST_EXPR_POST_DEC, $1, NULL); }
	| '(' type_name ')' '{' initializer_list '}'			{ $$ = makeAstNode(AST_EXPR_INIT, $2, $5, NULL); }
	| '(' type_name ')' '{' initializer_list ',' '}'		{ $$ = makeAstNode(AST_EXPR_INIT, $2, $5, NULL); }
	;

argument_expression_list
	: assignment_expression									{ $$ = makeAstNode(AST_LIST, $1, NULL); }
	| argument_expression_list ',' assignment_expression	{ $$ = appendAstChild($1, $3); }
	;

unary_expression
	: postfix_expression									{ $$ = $1; }
	| INC_OP unary_expression								{ $$ = makeAstNode(AST_EXPR_PRE_INC, $2, NULL); }
	| DEC_OP unary_expression								{ $$ = makeAstNode(AST_EXPR_PRE_DEC, $2, NULL); }
	| unary_operator cast_expression						{ $$ = makeAstNode($1, $2, NULL); }
	| SIZEOF unary_expression								{ $$ = makeAstNode(AST_EXPR_SIZEOF, $2, NULL); }
	| SIZEOF '(' type_name ')'								{ $$ = makeAstNode(AST_EXPR_SIZEOF, $3, NULL); }
	| ALIGNOF '(' type_name ')'								{ $$ = makeAstNode(AST_EXPR_ALIGNOF, $3, NULL); }
	;

unary_operator
	: '&'			{ $$ = AST_EXPR_UNARY_REF; }
	| '*'			{ $$ = AST_EXPR_UNARY_UNREF; }
	| '+'			{ $$ = AST_EXPR_UNARY_PLUS; }
	| '-'			{ $$ = AST_EXPR_UNARY_MINUS; }
	| '~'			{ $$ = AST_EXPR_BITS_INV; }
	| '!'			{ $$ = AST_EXPR_BOOL_NOT; }
	;

cast_expression
	: unary_expression										{ $$ = $1; }
	| '(' type_name ')' cast_expression						{ $$ = makeAstNode(AST_EXPR_CAST, $2, $4, NULL); }
	;

multiplicative_expression
	: cast_expression										{ $$ = $1; }
	| multiplicative_expression '*' cast_expression			{ $$ = makeAstNode(AST_EXPR_MUL, $1, $3, NULL); }
	| multiplicative_expression '/' cast_expression			{ $$ = makeAstNode(AST_EXPR_DIV, $1, $3, NULL); }
	| multiplicative_expression '%' cast_expression			{ $$ = makeAstNode(AST_EXPR_REM, $1, $3, NULL); }
	;

additive_expression
	: multiplicative_expression								{ $$ = $1; }
	| additive_expression '+' multiplicative_expression		{ $$ = makeAstNode(AST_EXPR_PLUS, $1, $3, NULL); }
	| additive_expression '-' multiplicative_expression		{ $$ = makeAstNode(AST_EXPR_MINUS, $1, $3, NULL); }
	;

shift_expression
	: additive_expression									{ $$ = $1; }
	| shift_expression LEFT_OP additive_expression			{ $$ = makeAstNode(AST_EXPR_BITS_SHL, $1, $3, NULL); }
	| shift_expression RIGHT_OP additive_expression			{ $$ = makeAstNode(AST_EXPR_BITS_SHR, $1, $3, NULL); }
	;

relational_expression
	: shift_expression										{ $$ = $1; }
	| relational_expression '<' shift_expression			{ $$ = makeAstNode(AST_EXPR_CMP_LT, $1, $3, NULL); }
	| relational_expression '>' shift_expression			{ $$ = makeAstNode(AST_EXPR_CMP_GT, $1, $3, NULL); }
	| relational_expression LE_OP shift_expression			{ $$ = makeAstNode(AST_EXPR_CMP_LTEQ, $1, $3, NULL); }
	| relational_expression GE_OP shift_expression			{ $$ = makeAstNode(AST_EXPR_CMP_GTEQ, $1, $3, NULL); }
	;

equality_expression
	: relational_expression									{ $$ = $1; }
	| equality_expression EQ_OP relational_expression		{ $$ = makeAstNode(AST_EXPR_CMP_EQ, $1, $3, NULL); }
	| equality_expression NE_OP relational_expression		{ $$ = makeAstNode(AST_EXPR_CMP_NEQ, $1, $3, NULL); }
	;

and_expression
	: equality_expression									{ $$ = $1; }
	| and_expression '&' equality_expression				{ $$ = makeAstNode(AST_EXPR_BITS_AND, $1, $3, NULL); }
	;

exclusive_or_expression
	: and_expression										{ $$ = $1; }
	| exclusive_or_expression '^' and_expression			{ $$ = makeAstNode(AST_EXPR_BITS_XOR, $1, $3, NULL); }
	;

inclusive_or_expression
	: exclusive_or_expression								{ $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression	{ $$ = makeAstNode(AST_EXPR_BITS_OR, $1, $3, NULL); }
	;

logical_and_expression
	: inclusive_or_expression								{ $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression	{ $$ = makeAstNode(AST_EXPR_BOOL_AND, $1, $3, NULL); }
	;

logical_or_expression
	: logical_and_expression								{ $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression	{ $$ = makeAstNode(AST_EXPR_BOOL_OR, $1, $3, NULL); }
	;

conditional_expression
	: logical_or_expression									{ $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = makeAstNode(AST_EXPR_CONDITIONAL, $1, $3, $5, NULL); }
	;

assignment_expression
	: conditional_expression								{ $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = makeAstNode($2, $1, $3, NULL); }
	;

assignment_operator
	: '='			{ $$ = AST_EXPR_ASSIGN; }
	| MUL_ASSIGN	{ $$ = AST_EXPR_ASS_MUL; }
	| DIV_ASSIGN	{ $$ = AST_EXPR_ASS_DIV; }
	| MOD_ASSIGN	{ $$ = AST_EXPR_ASS_REM; }
	| ADD_ASSIGN	{ $$ = AST_EXPR_ASS_PLUS; }
	| SUB_ASSIGN	{ $$ = AST_EXPR_ASS_MINUS; }
	| LEFT_ASSIGN	{ $$ = AST_EXPR_ASS_BITS_SHL; }
	| RIGHT_ASSIGN	{ $$ = AST_EXPR_ASS_BITS_SHR; }
	| AND_ASSIGN	{ $$ = AST_EXPR_ASS_BITS_AND; }
	| XOR_ASSIGN	{ $$ = AST_EXPR_ASS_BITS_XOR; }
	| OR_ASSIGN		{ $$ = AST_EXPR_ASS_BITS_OR; }
	;

expression
	: assignment_expression									{ $$ = makeAstNode(AST_EXPR_LIST, $1, NULL); }
	| expression ',' assignment_expression					{ $$ = appendAstChild($1, $3); }
	;

constant_expression
	: conditional_expression	/* with constraints */		{ $$ = $1; }
	;

declaration															
	: declaration_specifiers ';'									{ $$ = makeAstNode(AST_DECLARATION, $1, NULL); }
	| declaration_specifiers init_declarator_list ';'				{ $$ = registerTypeName(makeAstNode(AST_DECLARATION, $1, $2, NULL)); }
	| static_assert_declaration										{ $$ = $1; }
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers				{ $$ = prependAstChild($2, $1); }
	| storage_class_specifier										{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	| type_specifier declaration_specifiers							{ $$ = prependAstChild($2, $1); }
	| type_specifier												{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	| type_qualifier declaration_specifiers							{ $$ = prependAstChild($2, $1); }
	| type_qualifier												{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	| function_specifier declaration_specifiers						{ $$ = prependAstChild($2, $1); }
	| function_specifier											{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	| alignment_specifier declaration_specifiers					{ $$ = prependAstChild($2, $1); }
	| alignment_specifier											{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	;

init_declarator_list
	: init_declarator												{ $$ = makeAstNode(AST_LIST, $1, NULL); }
	| init_declarator_list ',' init_declarator						{ $$ = appendAstChild($1, $3); }
	;

init_declarator
	: declarator '=' initializer									{ $$ = makeAstNode(AST_DECLARATION_VALUE_PLACE, $1, $3, NULL); }
	| declarator													{ $$ = makeAstNode(AST_DECLARATION_VALUE_PLACE, $1, NULL); }
	;

storage_class_specifier
	: TYPEDEF	/* identifiers must be flagged as TYPEDEF_NAME */	{ $$ = makeAstTerm(AST_SSPEC_KW_TYPEDEF, $1); }
	| EXTERN														{ $$ = makeAstTerm(AST_SSPEC_KW_EXTERN, $1); }
	| STATIC														{ $$ = makeAstTerm(AST_SSPEC_KW_STATIC, $1); }
	| THREAD_LOCAL													{ $$ = makeAstTerm(AST_SSPEC_KW_THREAD_LOCAL, $1);	}
	| AUTO															{ $$ = makeAstTerm(AST_SSPEC_KW_AUTO, $1); }
	| REGISTER														{ $$ = makeAstTerm(AST_SSPEC_KW_REGISTER, $1); }
	;

type_specifier
	: VOID														{ $$ = makeAstTerm(AST_TYPE_VOID, $1); }
	| CHAR														{ $$ = makeAstTerm(AST_TYPE_CHAR, $1); }
	| SHORT														{ $$ = makeAstTerm(AST_TYPE_SHORT, $1); }
	| INT														{ $$ = makeAstTerm(AST_TYPE_INT, $1); }
	| LONG														{ $$ = makeAstTerm(AST_TYPE_LONG, $1); }
	| FLOAT														{ $$ = makeAstTerm(AST_TYPE_FLOAT, $1); }
	| DOUBLE													{ $$ = makeAstTerm(AST_TYPE_DOUBLE, $1); }
	| SIGNED													{ $$ = makeAstTerm(AST_TYPE_SIGNED, $1); }
	| UNSIGNED													{ $$ = makeAstTerm(AST_TYPE_UNSIGNED, $1); }
	| BOOL														{ $$ = makeAstTerm(AST_TYPE_BOOL, $1); }
	| COMPLEX													{ $$ = makeAstTerm(AST_TYPE_COMPLEX, $1); }
	| IMAGINARY	  	/* non-mandated extension */				{ $$ = makeAstTerm(AST_TYPE_IMAGINARY, $1); }
//	| atomic_type_specifier
	| struct_or_union_specifier									{ $$ = $1; }
	| enum_specifier											{ $$ = $1; }
	| TYPEDEF_NAME		/* after it has been defined as such */ { $$ = makeAstNode(AST_TYPE_NAMED, makeAstTerm(AST_ID, $1), NULL); }
	;

struct_or_union_specifier
	: struct_or_union '{' struct_declaration_list '}'			{ $$ = makeAstNode($1, $3, NULL); }
	| struct_or_union IDENTIFIER '{' struct_declaration_list '}'{ $$ = makeAstNode($1, makeAstTerm(AST_ID, $2), $4, NULL); }
	| struct_or_union IDENTIFIER								{ $$ = makeAstNode($1, makeAstTerm(AST_ID, $2), NULL); }
	;

struct_or_union
	: STRUCT													{ $$ = AST_TYPE_STRUCT; }
	| UNION														{ $$ = AST_TYPE_UNION; }
	;

struct_declaration_list
	: struct_declaration										{ $$ = makeAstNode(AST_LIST, $1, NULL); }
	| struct_declaration_list struct_declaration				{ $$ = appendAstChild($1, $2); }
	;

struct_declaration															// TODO
	: specifier_qualifier_list ';'	/* for anonymous struct/union */
	| specifier_qualifier_list struct_declarator_list ';'
	| static_assert_declaration										{ $$ = $1; }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list					{ $$ = prependAstChild($1, $2); }
	| type_specifier											{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	| type_qualifier specifier_qualifier_list					{ $$ = prependAstChild($1, $2); }
	| type_qualifier											{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: ':' constant_expression									{ $$ = makeAstNode(AST_DECLARATION_VALUE_PLACE, $2, NULL); }
	| declarator ':' constant_expression						{ $$ = makeAstNode(AST_DECLARATION_VALUE_PLACE, $1, $3, NULL); }
	| declarator												{ $$ = makeAstNode(AST_DECLARATION_VALUE_PLACE, $1, NULL); }
	;

enum_specifier
	: ENUM '{' enumerator_list '}'								{ $$ = makeAstNode(AST_TYPE_ENUM, $3, NULL); }
	| ENUM '{' enumerator_list ',' '}'							{ $$ = makeAstNode(AST_TYPE_ENUM, $3, NULL); }
	| ENUM IDENTIFIER '{' enumerator_list '}'					{ $$ = makeAstNode(AST_TYPE_ENUM, $2, $4, NULL); }
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'				{ $$ = makeAstNode(AST_TYPE_ENUM, $2, $4, NULL); }
	| ENUM IDENTIFIER											{ $$ = makeAstNode(AST_TYPE_ENUM, $2, NULL); }
	;

enumerator_list													
	: enumerator												{ $$ = makeAstNode(AST_LIST, $1, NULL); }
	| enumerator_list ',' enumerator							{ $$ = appendAstChild($1, $3); }
	;

enumerator	/* identifiers must be flagged as ENUMERATION_CONSTANT */
	: enumeration_constant '=' constant_expression				{ $$ = makeAstNode(AST_ENUM_ENTRY, $1, $3, NULL); }
	| enumeration_constant										{ $$ = makeAstNode(AST_ENUM_ENTRY, $1, NULL); }
	;

// atomic_type_specifier
//	: ATOMIC '(' type_name ')'
//	;

type_qualifier
	: CONST										{ $$ = makeAstTerm(AST_TSPEC_KW_CONST, $1); }								
	| RESTRICT									{ $$ = makeAstTerm(AST_TSPEC_KW_RESTRICT, $1); }
	| VOLATILE									{ $$ = makeAstTerm(AST_TSPEC_KW_VOLATILE, $1); }
//	| ATOMIC									
	;

function_specifier
	: INLINE									{ $$ = makeAstTerm(AST_FSPEC_KW_INLINE, $1); }
	| NORETURN									{ $$ = makeAstTerm(AST_FSPEC_KW_NORETURN, $1); }
	;

alignment_specifier
	: ALIGNAS '(' type_name ')'					{ $$ = makeAstNode(AST_SPEC_ALIGNAS_TYPE, $3, NULL); }
	| ALIGNAS '(' constant_expression ')'		{ $$ = makeAstNode(AST_SPEC_ALIGNAS_CONST, $3, NULL); }
	;

declarator
	: pointer direct_declarator					{ $$ = makeAstNode(AST_DECLARATION_ENTRY, $1, $2, NULL); }
	| direct_declarator							{ $$ = makeAstNode(AST_DECLARATION_ENTRY, $1, NULL); }
	;

direct_declarator
	: IDENTIFIER																	{ $$ = makeAstNode(AST_LIST, makeAstTerm(AST_ID, $1), NULL); }
	| '(' declarator ')'															{ $$ = makeAstNode(AST_LIST, $2, NULL); }
	| direct_declarator '[' ']'														{ $$ = appendAstChild($1, makeAstTerm(AST_DECLARATION_ARRAY_SPEC, "")); }
	| direct_declarator '[' '*' ']'						// TODO						{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "20"), NULL)); }	
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'	{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "21"), $4, $5, NULL)); }
	| direct_declarator '[' STATIC assignment_expression ']'						{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "22"), $4, NULL)); }
	| direct_declarator '[' type_qualifier_list '*' ']'								{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "23"), $3, NULL)); }
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'	{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "24"), $3, $5, NULL)); }
	| direct_declarator '[' type_qualifier_list assignment_expression ']'			{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "25"), $3, $4, NULL)); }
	| direct_declarator '[' type_qualifier_list ']'									{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "26"), $3, NULL)); }
	| direct_declarator '[' assignment_expression ']'								{ $$ = appendAstChild($1, makeAstNode(AST_DECLARATION_ARRAY_SPEC, $3, NULL)); }
	| direct_declarator '(' parameter_type_list ')'									{ $$ = appendAstChild($1, makeAstNode(AST_DECLARATION_PARAMS_SPEC, $3, NULL)); }
	| direct_declarator '(' ')'														{ $$ = appendAstChild($1, makeAstNode(AST_DECLARATION_PARAMS_SPEC, makeAstNode(AST_LIST, NULL), NULL)); }
	| direct_declarator '(' identifier_list ')'										{ $$ = appendAstChild($1, makeAstNode(AST_DECLARATION_PARAMS_SPEC, $3, NULL)); }
	;

pointer
	: '*' type_qualifier_list pointer												{ $$ = makeAstNode(AST_DECLARATION_PTR_SPEC, $2, $3, NULL); }
	| '*' type_qualifier_list														{ $$ = makeAstNode(AST_DECLARATION_PTR_SPEC, $2, NULL); }
	| '*' pointer																	{ $$ = makeAstNode(AST_DECLARATION_PTR_SPEC, $2, NULL); }
	| '*'																			{ $$ = makeAstTerm(AST_DECLARATION_PTR_SPEC, NULL); }
	;

type_qualifier_list
	: type_qualifier									{ $$ = makeAstNode(AST_DECL_SPECS, $1, NULL); }
	| type_qualifier_list type_qualifier				{ $$ = prependAstChild($1, $2); }
	;

parameter_type_list
	: parameter_list ',' ELLIPSIS						{ $$ = appendAstChild($1, makeAstTerm(AST_DECLARATION_PARAM_ELLIPSIS, $3)); }
	| parameter_list									{ $$ = $1; }
	;

parameter_list
	: parameter_declaration								{ $$ = makeAstNode(AST_LIST, $1, NULL); }
	| parameter_list ',' parameter_declaration			{ $$ = appendAstChild($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator					{ $$ = makeAstNode(AST_DECLARATION_PARAM_ENTRY, $1, $2, NULL); }
	| declaration_specifiers abstract_declarator		{ $$ = makeAstNode(AST_DECLARATION_PARAM_ENTRY, $1, $2, NULL); }
	| declaration_specifiers							{ $$ = makeAstNode(AST_DECLARATION_PARAM_ENTRY, $1, NULL); }
	;

identifier_list
	: IDENTIFIER										{ $$ = makeAstNode(AST_LIST, makeAstTerm(AST_ID, $1), NULL); }
	| identifier_list ',' IDENTIFIER					{ $$ = appendAstChild($1, makeAstTerm(AST_ID, $3)); }
	;

type_name
	: specifier_qualifier_list abstract_declarator		// TODO
	| specifier_qualifier_list							// TODO
	;

abstract_declarator
	: pointer direct_abstract_declarator				{ $$ = makeAstNode(AST_LIST, $1, $2, NULL); }
	| pointer											{ $$ = $1; }
	| direct_abstract_declarator						{ $$ = $1; }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'															{ $$ = makeAstNode(AST_LIST, $2, NULL); }
	| '[' ']'																				{ $$ = makeAstNode(AST_LIST, makeAstTerm(AST_DECLARATION_ARRAY_SPEC, NULL), NULL); }
	| '[' '*' ']'																			{ $$ = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "1"), NULL); }
	| '[' STATIC type_qualifier_list assignment_expression ']'								{ $$ = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "2"), $3, $4, NULL); }
	| '[' STATIC assignment_expression ']'													{ $$ = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "3"), $3, NULL); }
	| '[' type_qualifier_list STATIC assignment_expression ']'								{ $$ = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "4"), $2, $4, NULL); }
	| '[' type_qualifier_list assignment_expression ']'										{ $$ = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "5"), $2, $3, NULL); }
	| '[' type_qualifier_list ']'															{ $$ = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "6"), $2, NULL); }
	| '[' assignment_expression ']'															{ $$ = makeAstNode(AST_DECLARATION_ARRAY_SPEC, $2, NULL); }
	| direct_abstract_declarator '[' ']'													{ $$ = appendAstChild($1, makeAstTerm(AST_DECLARATION_ARRAY_SPEC, NULL)); }
	| direct_abstract_declarator '[' '*' ']'												{ $$ = appendAstChild($1, makeAstTerm(AST_DECLARATION_ARRAY_SPEC, NULL)); }
	| direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'	{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "8"), $4, $5, NULL)); }
	| direct_abstract_declarator '[' STATIC assignment_expression ']'						{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "9"), $4, NULL)); }
	| direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'			{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "10"), $3, $4, NULL)); }
	| direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'	{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "11"), $3, $5, NULL)); }
	| direct_abstract_declarator '[' type_qualifier_list ']'								{ $$ = appendAstChild($1, makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "12"), $3, NULL)); }
	| direct_abstract_declarator '[' assignment_expression ']'								{ $$ = appendAstChild($1, makeAstNode(AST_DECLARATION_ARRAY_SPEC, $3, NULL)); }
	| '(' ')'																				{ $$ = makeAstNode(AST_DECLARATION_PARAMS_SPEC, makeAstNode(AST_LIST, NULL), NULL); }
	| '(' parameter_type_list ')'															{ $$ = makeAstNode(AST_DECLARATION_PARAMS_SPEC, $2, NULL); }
	| direct_abstract_declarator '(' ')'													{ $$ = appendAstChild($1, makeAstNode(AST_DECLARATION_PARAMS_SPEC, makeAstNode(AST_LIST, NULL), NULL)); }
	| direct_abstract_declarator '(' parameter_type_list ')'								{ $$ = appendAstChild($1, makeAstNode(AST_DECLARATION_PARAMS_SPEC, $3, NULL)); }
	;

initializer
	: '{' initializer_list '}'									{ $$ = makeAstNode(AST_EXPR_INIT, $2, NULL); }
	| '{' initializer_list ',' '}'								{ $$ = makeAstNode(AST_EXPR_INIT, $2, NULL); }
	| assignment_expression										{ $$ = $1; }
	;

initializer_list
	: designation initializer						{ $$ = makeAstNode(AST_LIST, makeAstNode(AST_EXPR_INIT_MEMBER, $1, $2, NULL), NULL); }
	| initializer									{ $$ = makeAstNode(AST_LIST, makeAstNode(AST_EXPR_INIT_MEMBER, $1, NULL), NULL); }
	| initializer_list ',' designation initializer	{ $$ = appendAstChild($1, makeAstNode(AST_EXPR_INIT_MEMBER, $3, $4, NULL)); }
	| initializer_list ',' initializer				{ $$ = appendAstChild($1, makeAstNode(AST_EXPR_INIT_MEMBER, $3, NULL)); }
	;

designation
	: designator_list '='							{ $$ = $1; }
	;

designator_list
	: designator									{ $$ = makeAstNode(AST_EXPR_INIT_MEMBER_TARGET, $1, NULL); }
	| designator_list designator					{ $$ = appendAstChild($1, $2); }
	;

designator
	: '[' constant_expression ']'					{ $$ = makeAstNode(AST_EXPR_INIT_MEMBER_TARGET_INDEX, $2, NULL); }
	| '.' IDENTIFIER								{ $$ = makeAstTerm(AST_EXPR_INIT_MEMBER_TARGET_FIELD, $2); }
	;

static_assert_declaration
	: STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'		{ $$ = makeAstNode(AST_STATIC_ASSERT, $3, makeAstTerm(AST_LITERAL_STRING, $5), NULL); }
	;

statement
	: labeled_statement							{ $$ = $1; }
	| compound_statement						{ $$ = $1; }
	| expression_statement						{ $$ = $1; }
	| selection_statement						{ $$ = $1; }
	| iteration_statement						{ $$ = $1; }
	| jump_statement							{ $$ = $1; }
	| error ';'									{ $$ = makeAstTerm(AST_STMT_ERROR, NULL); }
	;

labeled_statement
	: IDENTIFIER ':' statement					{ $$ = makeAstNode(AST_STMT_LABELED, makeAstTerm(AST_ID, $1), $3, NULL); }
	| CASE constant_expression ':' statement	{ $$ = makeAstNode(AST_STMT_LABELED, $2, $4, NULL); }
	| DEFAULT ':' statement						{ $$ = makeAstNode(AST_STMT_LABELED, makeAstTerm(AST_ID, $1), $3, NULL); }
	;

compound_statement
	: '{' '}'									{ $$ = makeAstNode(AST_STMT_BLOCK, NULL); }
	| '{'  block_item_list '}'					{ $$ = $2; }
	;

block_item_list
	: block_item								{ $$ = makeAstNode(AST_STMT_BLOCK, $1, NULL); }
	| block_item_list block_item				{ $$ = appendAstChild($1, $2); }
	;

block_item
	: declaration								{ $$ = $1; }
	| statement									{ $$ = $1; }
	;

expression_statement
	: ';'										{ $$ = makeAstNode(AST_STMT_EMPTY, NULL); }
	| expression ';'							{ $$ = makeAstNode(AST_STMT_EXPR, $1, NULL); }
	;

selection_statement
	: IF '(' expression ')' statement                %prec P_THEN { $$ = makeAstNode(AST_STMT_IF, $3, $5, NULL); }
	| IF '(' expression ')' statement ELSE statement			  { $$ = makeAstNode(AST_STMT_IF, $3, $5, $7, NULL); }
	| SWITCH '(' expression ')' statement						  { $$ = makeAstNode(AST_STMT_SWITCH, $3, $5, NULL); }
	;

iteration_statement
	: WHILE '(' expression ')' statement										{ $$ = makeAstNode(AST_STMT_WHILE, $3, $5, NULL); }
	| DO statement WHILE '(' expression ')' ';'									{ $$ = makeAstNode(AST_STMT_DO, $2, $5, NULL); }
	| FOR '(' expression_statement expression_statement ')' statement			{ $$ = makeAstNode(AST_STMT_FOR, $3, $4, $6, NULL); }
	| FOR '(' expression_statement expression_statement expression ')' statement{ $$ = makeAstNode(AST_STMT_FOR, $3, $4, $5, $7, NULL); }
	| FOR '(' declaration expression_statement ')' statement					{ $$ = makeAstNode(AST_STMT_FOR, $3, $4, $6, NULL); }
	| FOR '(' declaration expression_statement expression ')' statement			{ $$ = makeAstNode(AST_STMT_FOR, $3, $4, $5, $7, NULL); }
	;

jump_statement
	: GOTO IDENTIFIER ';'						{ $$ = makeAstNode(AST_STMT_GOTO, makeAstTerm(AST_ID, $2), NULL); }
	| CONTINUE ';'								{ $$ = makeAstTerm(AST_STMT_CONTINUE, NULL); }
	| BREAK ';'									{ $$ = makeAstTerm(AST_STMT_BREAK, NULL); }
	| RETURN ';'								{ $$ = makeAstTerm(AST_STMT_RETURN, NULL); }
	| RETURN expression ';'						{ $$ = makeAstNode(AST_STMT_RETURN, $2, NULL); }
	;

translation_unit
	: external_declaration						{ $$ = ast = makeAstNode(AST_LIST, $1, NULL); }
	| translation_unit external_declaration		{ $$ = ast = appendAstChild($1, $2); }
	;

external_declaration
	: function_definition						{ $$ = $1; }
	| declaration								{ $$ = $1; }
	| error ';'									{ $$ = makeAstTerm(AST_STMT_ERROR, NULL); }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement	{ $$ = makeAstNode(AST_DEF_FUNCTION_IMPL, $1, $2, $3, $4, NULL); }
	| declaration_specifiers declarator compound_statement					{ $$ = makeAstNode(AST_DEF_FUNCTION_IMPL, $1, $2, $3, NULL); }
	;

declaration_list
	: declaration						{ $$ = makeAstNode(AST_LIST, $1, NULL); }
	| declaration_list declaration		{ $$ = appendAstChild($1, $2); }
	;

%%
