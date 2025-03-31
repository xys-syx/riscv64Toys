#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <math.h>

#include "collections.h"

#include "ast.h"
#undef AST_E_H
#define GENERATE_ENUM_STRINGS  // Start string generation
#include "ast.h"             
#undef GENERATE_ENUM_STRINGS   // Stop string generation

#include "c99.y.gen.h"
#include "c99.l.gen.h"

#include "model.h"

extern int yyPositionFrom;
extern int yyPositionTo;

//extern char* text;
//
//static void printNodeLocation(AstNode* node)
//{
//    int len = node->toLoc.position - node->fromLoc.position;
//    char buff[len + 1];
//    memcpy(buff, &text[node->fromLoc.position], len);
//    buff[len] = 0;
//
//    printf(
//        "L%dC%d@%d - L%dC%d@%d %s : %s\n",
//        node->fromLoc.line,
//        node->fromLoc.column,
//        node->fromLoc.position,
//        node->toLoc.line,
//        node->toLoc.column,
//        node->toLoc.position,
//        getStringAstNodeKinds(node->kind),
//        buff // node->payload == NULL ? "" : node->payload
//    );
//}

AstNode* makeAstNode(AstNodeKind kind, ...)
{
    AstNode* node = allocStruct(AstNode);
    node->kind = kind;
    node->payload = NULL;
    node->firstChild = NULL;
    node->lastChild = NULL;
    node->next = NULL;

    int count = 0, stackForChildren = 0, childrenDepth = 0;
    AstNode** childPtr = &node->firstChild;
    va_list ptrSpec;
    va_start(ptrSpec, kind);

    AstNode* child = va_arg(ptrSpec, AstNode*);
    if (child != NULL)
    {
        node->firstChild = child;
        do
        {
            stackForChildren = max(stackForChildren, child->stackDepthRequired);
            childrenDepth = max(childrenDepth, child->depth);
            *childPtr = child;
            childPtr = &child->next;
            node->lastChild = child;
            count++;
            child = va_arg(ptrSpec, AstNode*);
        } while (child != NULL);
    }
    node->stackDepthRequired = stackForChildren + count;
    node->depth = childrenDepth + 1;
    node->childrenCount = count;

    if (count > 0)
    {
        node->fromLoc = node->firstChild->fromLoc;
        node->toLoc = node->lastChild->toLoc;
    }
    else
    {
        node->fromLoc = (SourceLocation){ 0, 0, 0 };
        node->toLoc= (SourceLocation){ 0, 0, 0 };
    }
    
    va_end(ptrSpec);

    return node;
}

AstNode* makeAstTerm(AstNodeKind kind, char* payload)
{
    char* buff;
    if (payload != NULL)
    {
        int len = strlen(payload);
        buff = allocArray(char, len + 1);
        strcpy(buff, payload);
    }
    else
    {
        buff = NULL;
    }

    AstNode* node = allocStruct(AstNode);
    node->kind = kind;
    node->stackDepthRequired = 1;
    node->depth = 1;
    node->childrenCount = 0;
    node->payload = buff;
    node->firstChild = NULL;
    node->lastChild = NULL;
    node->next = NULL;
    node->fromLoc = (SourceLocation){
        .line = yylloc.first_line,
        .column = yylloc.first_column,
        .position = yyPositionFrom
    };
    node->toLoc = (SourceLocation){
        .line = yylloc.last_line,
        .column = yylloc.last_column,
        .position = yyPositionTo
    };
    
    // printError(node, "Term captured: %s -- %s", payload, buff);

    return node;
}

AstNode* appendAstChild(AstNode* node, AstNode* child)
{
    if (node->lastChild != NULL)
    {
        node->lastChild->next = child;
    }
    else 
    {
        node->firstChild = child;
    }

    node->lastChild = child;
    
    node->stackDepthRequired = max(node->stackDepthRequired - node->childrenCount, child->stackDepthRequired) + node->childrenCount;
    node->depth = max(node->depth - 1, child->depth) + 1;
    node->childrenCount++;
    node->fromLoc = node->firstChild->fromLoc;
    node->toLoc = node->lastChild->toLoc;

    return node;
}

AstNode* prependAstChild(AstNode* node, AstNode* child)
{
    child->next = node->firstChild;
    node->firstChild = child;

    if (node->lastChild == NULL)
    {
        node->lastChild = child;
    }

    node->stackDepthRequired = max(node->stackDepthRequired - node->childrenCount, child->stackDepthRequired) + node->childrenCount;
    node->depth = max(node->depth - 1, child->depth) + 1;
    node->childrenCount++;
    node->fromLoc = node->firstChild->fromLoc;
    node->toLoc = node->lastChild->toLoc;

    return node;
}

void traceAstRecursively(AstNode* node, FILE* out)
{
    fprintf(out, "<%s Line=\"%d\" Column=\"%d\" Position=\"%d\">\n", getStringAstNodeKinds(node->kind), node->fromLoc.line + 1, node->fromLoc.column + 1, node->fromLoc.position);
    if (node->payload != NULL)
    {
        fprintf(out, "%s", node->payload);

    }

    for (AstNode* child = node->firstChild; child != NULL; child = child->next)
    {
        traceAstRecursively(child, out);
    }
    fprintf(out, "</%s>\n", getStringAstNodeKinds(node->kind));
}

int classifyAstNode(AstNode* node)
{
    switch (node->kind)
    {
    case AST_STMT_EMPTY:
    case AST_STMT_BLOCK:
    case AST_STMT_IF:
    case AST_STMT_EXPR:
    case AST_STMT_SWITCH:
    case AST_STMT_WHILE:
    case AST_STMT_FOR:
    case AST_STMT_DO:
    case AST_STMT_RETURN:
    case AST_STMT_BREAK:
    case AST_STMT_CONTINUE:
    case AST_STMT_GOTO:
    case AST_STMT_LABELED:
    case AST_STMT_ERROR:
        return AST_KIND_FAMILY_STATEMENT;
    case AST_LABEL:
    case AST_DEF_FUNCTION_HEAD:
        return AST_KIND_FAMILY_FUNC_DECL;
    case AST_DEF_FUNCTION_IMPL:
        return AST_KIND_FAMILY_FUNC_IMPL;
    case AST_DEF_STRUCT:
    case AST_DEF_TYPEDEF:
    case AST_DEF_UNION:
    case AST_DEF_ENUM:
        return AST_KIND_FAMILY_TYPE_DECL;
    case AST_LITERAL_STRING:
    case AST_LITERAL_INT:
    case AST_LITERAL_FLOAT:
    case AST_LITERAL_CHAR:
    case AST_EXPR_PRE_INC:
    case AST_EXPR_PRE_DEC:
    case AST_EXPR_POST_INC:
    case AST_EXPR_POST_DEC:
    case AST_EXPR_PLUS:
    case AST_EXPR_MINUS:
    case AST_EXPR_MUL:
    case AST_EXPR_DIV:
    case AST_EXPR_REM:
    case AST_EXPR_ASSIGN:
    case AST_EXPR_ASS_PLUS:
    case AST_EXPR_ASS_MINUS:
    case AST_EXPR_ASS_MUL:
    case AST_EXPR_ASS_DIV:
    case AST_EXPR_ASS_REM:
    case AST_EXPR_ASS_BITS_XOR:
    case AST_EXPR_ASS_BITS_AND:
    case AST_EXPR_ASS_BITS_OR:
    case AST_EXPR_ASS_BITS_SHL:
    case AST_EXPR_ASS_BITS_SHR:
    case AST_EXPR_CMP_EQ:
    case AST_EXPR_CMP_NEQ:
    case AST_EXPR_CMP_LT:
    case AST_EXPR_CMP_GT:
    case AST_EXPR_CMP_LTEQ:
    case AST_EXPR_CMP_GTEQ:
    case AST_EXPR_BOOL_NOT:
    case AST_EXPR_BOOL_AND:
    case AST_EXPR_BOOL_OR:
    case AST_EXPR_BITS_INV:
    case AST_EXPR_BITS_XOR:
    case AST_EXPR_BITS_AND:
    case AST_EXPR_BITS_OR:
    case AST_EXPR_BITS_SHL:
    case AST_EXPR_BITS_SHR:
    case AST_EXPR_CONDITIONAL:
    case AST_EXPR_UNARY_REF:
    case AST_EXPR_UNARY_UNREF:
    case AST_EXPR_UNARY_PLUS:
    case AST_EXPR_UNARY_MINUS:
    case AST_EXPR_INDEX:
    case AST_EXPR_CALL:
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
    case AST_EXPR_LIST:
        return AST_KIND_FAMILY_EXPR;
    case AST_ID:
    case AST_GENERIC:
    case AST_GENERIC_ENTRY:
    case AST_GENERIC_DEFAULT_ENTRY:
    case AST_LIST:
    case AST_SPEC_ALIGNAS_TYPE:
    case AST_SPEC_ALIGNAS_CONST:
    case AST_FSPEC_KW_INLINE:
    case AST_FSPEC_KW_NORETURN:
    case AST_TSPEC_KW_CONST:
    case AST_TSPEC_KW_VOLATILE:
    case AST_SSPEC_KW_TYPEDEF:
    case AST_SSPEC_KW_EXTERN:
    case AST_SSPEC_KW_STATIC:
    case AST_SSPEC_KW_THREAD_LOCAL:
    case AST_SSPEC_KW_AUTO:
    case AST_SSPEC_KW_REGISTER:
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
    case AST_TYPE_IMAGINARY:
    case AST_TYPE_NAMED:
    case AST_TYPE_UNION:
    case AST_TYPE_STRUCT:
    case AST_TYPE_ENUM:
    case AST_ENUM_ENTRY:
    case AST_DECL_SPECS:
        return AST_KIND_FAMILY_UTIL;
    case AST_DECLARATION:
    case AST_DECLARATION_PTR_SPEC:
    case AST_DECLARATION_ENTRY:
    case AST_DECLARATION_ARRAY_SPEC:
    case AST_DECLARATION_PARAMS_SPEC:
    case AST_DECLARATION_PARAM_ENTRY:
        return AST_KIND_FAMILY_VAR_DECL;
    case AST_STATIC_ASSERT:
    case AST_TODO:
    default:
        return AST_KIND_FAMILY_TODO;
    }
}

void traceAst(AstNode* root, FILE* out)
{
    int depth = 0;
    AstNode* stack[root->stackDepthRequired * 2];
    stack[0] = root;

    while (depth >= 0)
    {
        AstNode* node = stack[depth];

        if (node != NULL)
        {
            fprintf(out, "<%s Line=\"%d\" Column=\"%d\" Position=\"%d\">\n", getStringAstNodeKinds(node->kind), node->fromLoc.line + 1, node->fromLoc.column + 1, node->fromLoc.position);
            stack[++depth] = NULL;
            
            int lastIndex = depth + node->childrenCount;
            for (AstNode* child = node->firstChild; child != NULL; child = child->next)
            {
                stack[lastIndex--] = child;
            }
            depth += node->childrenCount;

            if (node->payload != NULL)
            {
                fprintf(out, "%s", node->payload);
            }
        }
        else
        {
            node = stack[--depth];
            --depth;
            fprintf(out, "</%s>\n", getStringAstNodeKinds(node->kind));
        }
    }

}

void cleanupAst(AstNode* root)
{
    int depth = 1;
    AstNode* stack[root->stackDepthRequired * 2];
    stack[0] = root;

    while (depth > 0) 
    {
        AstNode* node = stack[depth];

        if (node != NULL)
        {
            stack[++depth] = NULL;

            for (AstNode* child = node->firstChild; child != NULL; child = child->next)
            {
                stack[++depth] = child;
            }
        }
        else
        {
            node = stack[--depth];

            if (node->payload != NULL)
            {
                free(node->payload);
            }

            free(node);
            --depth;
        }
    }
}

extern ProgramUnit* model;

void yyerror(const char* s);
void yyerror(const char* s)
{
    fflush(stdout);
    fprintf(stderr, "%s(%d,%d): %s\n", model->sourceFileName, yylloc.first_line + 1, yylloc.first_column + 1, s);

    model->errorsCount++;
}

static void printImpl(AstNode* ast, const char* kind, const char* fmt, va_list args)
{
    fflush(stdout);

    if (ast != NULL)
    {
        fprintf(stderr, "%s(%d,%d): %s:", model->sourceFileName, ast->fromLoc.line + 1, ast->fromLoc.column + 1, kind);
    }
    else
    {
        fprintf(stderr, "%s(?): %s:", model->sourceFileName, kind);
    }

    //va_list args;
    //va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    //va_end(args);

    printf("\n");
}

void printError(AstNode* ast, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printImpl(ast, "error", fmt, args);
    va_end(args);

    model->errorsCount++;

    if (errno != 0)
    {
        fprintf(stderr, "error(%d): %s\n ", errno, strerror(errno));
    }
}

void printTrace(AstNode* ast, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printImpl(ast, "trace", fmt, args);
    va_end(args);
}

static RbTree* typeNames = NULL;

AstNode* registerTypeName(AstNode* declaration)
{
    if (typeNames == NULL)
        typeNames = createRbTreeByString();

    bool isTypeDef = false;
    for (AstNode* node = declaration->firstChild->firstChild; node != NULL; node = node->next)
    {
        if (node->kind == AST_SSPEC_KW_TYPEDEF)
        {
            isTypeDef = true;
            break;
        }
    }

    if (isTypeDef)
    {
        // for each AST_DECLARATION_VALUE_PLACE
        for (AstNode* node = declaration->lastChild->firstChild; node != NULL; node = node->next)
        {
            AstNode* id = node->firstChild->lastChild->firstChild;
            while (id->kind != AST_ID)
                id = id->lastChild->firstChild;
            
            if (id->kind == AST_ID)
            tryAddRbTreeItem(typeNames, id->payload, id->payload);
        }
    }

    return declaration;
}

bool isTypeName(char* name)
{
    return typeNames == NULL ? false : findRbTreeItem(typeNames, name);
}


