%option yylineno
%option bison-locations
%e  1019
%p  2807
%n  371
%k  284
%a  1213
%o  1117

O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\n\f]

%{
#include <stdio.h>

#include "ast.h"

#include "c99.y.gen.h"

extern void yyerror(const char *);  /* prints grammar violation message */

extern int sym_type(const char *);  /* returns type from symbol table */

int submitToken(int token);

#define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

static void comment(void);

int yyPositionFrom = 0;
int yyPositionTo = 0;

%}

%%
"/*"                                    { comment(); /* parser doesn't see both whitespaces and comments */ } 
"//".*                                    { yyPositionTo += strlen(yytext); yyPositionFrom = yyPositionTo; /* consume //-comment */ }

"auto"					{ return submitToken(AUTO); }
"break"					{ return submitToken(BREAK); }
"case"					{ return submitToken(CASE); }
"char"					{ return submitToken(CHAR); }
"const"					{ return submitToken(CONST); }
"continue"				{ return submitToken(CONTINUE); }
"default"				{ return submitToken(DEFAULT); }
"do"					{ return submitToken(DO); }
"double"				{ return submitToken(DOUBLE); }
"else"					{ return submitToken(ELSE); }
"enum"					{ return submitToken(ENUM); }
"extern"				{ return submitToken(EXTERN); }
"float"					{ return submitToken(FLOAT); }
"for"					{ return submitToken(FOR); }
"goto"					{ return submitToken(GOTO); }
"if"					{ return submitToken(IF); }
"inline"				{ return submitToken(INLINE); }
"int"					{ return submitToken(INT); }
"long"					{ return submitToken(LONG); }
"register"				{ return submitToken(REGISTER); }
"restrict"				{ return submitToken(RESTRICT); }
"return"				{ return submitToken(RETURN); }
"short"					{ return submitToken(SHORT); }
"signed"				{ return submitToken(SIGNED); }
"sizeof"				{ return submitToken(SIZEOF); }
"static"				{ return submitToken(STATIC); }
"struct"				{ return submitToken(STRUCT); }
"switch"				{ return submitToken(SWITCH); }
"typedef"				{ return submitToken(TYPEDEF); }
"union"					{ return submitToken(UNION); }
"unsigned"				{ return submitToken(UNSIGNED); }
"void"					{ return submitToken(VOID); }
"volatile"				{ return submitToken(VOLATILE); }
"while"					{ return submitToken(WHILE); }
"_Alignas"                              { return submitToken(ALIGNAS); }
"_Alignof"                              { return submitToken(ALIGNOF); }
"_Atomic"                               { return submitToken(ATOMIC); }
"_Bool"                                 { return submitToken(BOOL); }
"_Complex"                              { return submitToken(COMPLEX); }
"_Generic"                              { return submitToken(GENERIC); }
"_Imaginary"                            { return submitToken(IMAGINARY); }
"_Noreturn"                             { return submitToken(NORETURN); }
"_Static_assert"                        { return submitToken(STATIC_ASSERT); }
"_Thread_local"                         { return submitToken(THREAD_LOCAL); }
"__func__"                              { return submitToken(FUNC_NAME); }

{L}{A}*					{ return submitToken(IDENTIFIER); }

{HP}{H}+{IS}?				{ return submitToken(I_CONSTANT); }
{NZ}{D}*{IS}?				{ return submitToken(I_CONSTANT); }
"0"{O}*{IS}?				{ return submitToken(I_CONSTANT); }
{CP}?"'"([^'\\\n]|{ES})+"'"		{ return submitToken(I_CONSTANT); }

{D}+{E}{FS}?				{ return submitToken(F_CONSTANT); }
{D}*"."{D}+{E}?{FS}?			{ return submitToken(F_CONSTANT); }
{D}+"."{E}?{FS}?			{ return submitToken(F_CONSTANT); }
{HP}{H}+{P}{FS}?			{ return submitToken(F_CONSTANT); }
{HP}{H}*"."{H}+{P}{FS}?			{ return submitToken(F_CONSTANT); }
{HP}{H}+"."{P}{FS}?			{ return submitToken(F_CONSTANT); }

({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{ return submitToken(STRING_LITERAL); }

"..."					{ return submitToken(ELLIPSIS); }
">>="					{ return submitToken(RIGHT_ASSIGN); }
"<<="					{ return submitToken(LEFT_ASSIGN); }
"+="					{ return submitToken(ADD_ASSIGN); }
"-="					{ return submitToken(SUB_ASSIGN); }
"*="					{ return submitToken(MUL_ASSIGN); }
"/="					{ return submitToken(DIV_ASSIGN); }
"%="					{ return submitToken(MOD_ASSIGN); }
"&="					{ return submitToken(AND_ASSIGN); }
"^="					{ return submitToken(XOR_ASSIGN); }
"|="					{ return submitToken(OR_ASSIGN); }
">>"					{ return submitToken(RIGHT_OP); }
"<<"					{ return submitToken(LEFT_OP); }
"++"					{ return submitToken(INC_OP); }
"--"					{ return submitToken(DEC_OP); }
"->"					{ return submitToken(PTR_OP); }
"&&"					{ return submitToken(AND_OP); }
"||"					{ return submitToken(OR_OP); }
"<="					{ return submitToken(LE_OP); }
">="					{ return submitToken(GE_OP); }
"=="					{ return submitToken(EQ_OP); }
"!="					{ return submitToken(NE_OP); }
";"					{ return submitToken(';'); }
("{"|"<%")				{ return submitToken('{'); }
("}"|"%>")				{ return submitToken('}'); }
","					{ return submitToken(','); }
":"					{ return submitToken(':'); }
"="					{ return submitToken('='); }
"("					{ return submitToken('('); }
")"					{ return submitToken(')'); }
("["|"<:")				{ return submitToken('['); }
("]"|":>")				{ return submitToken(']'); }
"."					{ return submitToken('.'); }
"&"					{ return submitToken('&'); }
"!"					{ return submitToken('!'); }
"~"					{ return submitToken('~'); }
"-"					{ return submitToken('-'); }
"+"					{ return submitToken('+'); }
"*"					{ return submitToken('*'); }
"/"					{ return submitToken('/'); }
"%"					{ return submitToken('%'); }
"<"					{ return submitToken('<'); }
">"					{ return submitToken('>'); }
"^"					{ return submitToken('^'); }
"|"					{ return submitToken('|'); }
"?"					{ return submitToken('?'); }

{WS}+					{ /* whitespace separates tokens */ submitToken(' '); }
.					{ /* discard bad characters */ submitToken('.'); }

%%

extern int yychar;

static char *tokenBuffer = NULL;

int submitToken(int token)
{
    yylval.text = yytext;
    
    // by the time we are capturing the yytext on the parser side it has unwanted characters for some reason sometimes
    // but at this point of time it is correct, so capture to token to the temporary buffer
    // consider getting rid of this thing, however the reason should be investigated
    char *buff;
    {
        if (tokenBuffer == NULL)
            free(tokenBuffer);
        
        int len = strlen(yytext);
        buff = allocArray(char, len + 1);
        strcpy(buff, yytext);
        buff[len] = 0;
        yylval.text = buff;
        tokenBuffer = buff;
    }
    
    // term location tracking

    yylloc.first_line = yylloc.last_line;
    yylloc.first_column = yylloc.last_column;
    
    // printf("@(%d,%d) %s\n", yylloc.first_line, yylloc.first_column, yytext);

    yyPositionFrom = yyPositionTo;
    for(int i = 0; yytext[i] != '\0'; i++) {
        yyPositionTo++;
        if(yytext[i] == '\n') {
            yylloc.last_line++;
            yylloc.last_column = 0;
        }
        else {
            yylloc.last_column++;
        }
    }
    yychar = token;
    //yyPositionTo++;

    return ((token == IDENTIFIER && isTypeName(buff))) ? TYPEDEF_NAME : token;
}

int yywrap(void)        /* called at end of input */
{
    return 1;           /* terminate now */
}

static void comment(void)
{
    int c;

    while ((c = input()) != 0)
    {
        yyPositionTo++;
        if (c == '*')
        {
            while ((c = input()) == '*')
                yyPositionTo++;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
    }
    yyerror("unterminated comment");
}
