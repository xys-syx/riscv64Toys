/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "c99.y"


#include <stdio.h>

#include "ast.h"

#define YYERROR_VERBOSE 1

extern AstNode* ast;
extern int yylineno;

int yylex(void);
void yyerror(const char *s);



#line 88 "c99.y.gen.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "c99.y.gen.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_I_CONSTANT = 4,                 /* I_CONSTANT  */
  YYSYMBOL_F_CONSTANT = 5,                 /* F_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_FUNC_NAME = 7,                  /* FUNC_NAME  */
  YYSYMBOL_SIZEOF = 8,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 9,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 10,                    /* INC_OP  */
  YYSYMBOL_DEC_OP = 11,                    /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 12,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 13,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 14,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 15,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 16,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 17,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 18,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 19,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 20,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 21,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 22,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 23,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 24,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 25,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 26,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 27,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 28,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 29,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPEDEF_NAME = 30,              /* TYPEDEF_NAME  */
  YYSYMBOL_ENUMERATION_CONSTANT = 31,      /* ENUMERATION_CONSTANT  */
  YYSYMBOL_TYPEDEF = 32,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 33,                    /* EXTERN  */
  YYSYMBOL_STATIC = 34,                    /* STATIC  */
  YYSYMBOL_AUTO = 35,                      /* AUTO  */
  YYSYMBOL_REGISTER = 36,                  /* REGISTER  */
  YYSYMBOL_INLINE = 37,                    /* INLINE  */
  YYSYMBOL_CONST = 38,                     /* CONST  */
  YYSYMBOL_RESTRICT = 39,                  /* RESTRICT  */
  YYSYMBOL_VOLATILE = 40,                  /* VOLATILE  */
  YYSYMBOL_BOOL = 41,                      /* BOOL  */
  YYSYMBOL_CHAR = 42,                      /* CHAR  */
  YYSYMBOL_SHORT = 43,                     /* SHORT  */
  YYSYMBOL_INT = 44,                       /* INT  */
  YYSYMBOL_LONG = 45,                      /* LONG  */
  YYSYMBOL_SIGNED = 46,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 47,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 48,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 49,                    /* DOUBLE  */
  YYSYMBOL_VOID = 50,                      /* VOID  */
  YYSYMBOL_COMPLEX = 51,                   /* COMPLEX  */
  YYSYMBOL_IMAGINARY = 52,                 /* IMAGINARY  */
  YYSYMBOL_STRUCT = 53,                    /* STRUCT  */
  YYSYMBOL_UNION = 54,                     /* UNION  */
  YYSYMBOL_ENUM = 55,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 56,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 57,                      /* CASE  */
  YYSYMBOL_DEFAULT = 58,                   /* DEFAULT  */
  YYSYMBOL_IF = 59,                        /* IF  */
  YYSYMBOL_ELSE = 60,                      /* ELSE  */
  YYSYMBOL_SWITCH = 61,                    /* SWITCH  */
  YYSYMBOL_WHILE = 62,                     /* WHILE  */
  YYSYMBOL_DO = 63,                        /* DO  */
  YYSYMBOL_FOR = 64,                       /* FOR  */
  YYSYMBOL_GOTO = 65,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 66,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 67,                     /* BREAK  */
  YYSYMBOL_RETURN = 68,                    /* RETURN  */
  YYSYMBOL_ALIGNAS = 69,                   /* ALIGNAS  */
  YYSYMBOL_ALIGNOF = 70,                   /* ALIGNOF  */
  YYSYMBOL_ATOMIC = 71,                    /* ATOMIC  */
  YYSYMBOL_GENERIC = 72,                   /* GENERIC  */
  YYSYMBOL_NORETURN = 73,                  /* NORETURN  */
  YYSYMBOL_STATIC_ASSERT = 74,             /* STATIC_ASSERT  */
  YYSYMBOL_THREAD_LOCAL = 75,              /* THREAD_LOCAL  */
  YYSYMBOL_P_THEN = 76,                    /* P_THEN  */
  YYSYMBOL_77_ = 77,                       /* '('  */
  YYSYMBOL_78_ = 78,                       /* ')'  */
  YYSYMBOL_79_ = 79,                       /* ','  */
  YYSYMBOL_80_ = 80,                       /* ':'  */
  YYSYMBOL_81_ = 81,                       /* '['  */
  YYSYMBOL_82_ = 82,                       /* ']'  */
  YYSYMBOL_83_ = 83,                       /* '.'  */
  YYSYMBOL_84_ = 84,                       /* '{'  */
  YYSYMBOL_85_ = 85,                       /* '}'  */
  YYSYMBOL_86_ = 86,                       /* '&'  */
  YYSYMBOL_87_ = 87,                       /* '*'  */
  YYSYMBOL_88_ = 88,                       /* '+'  */
  YYSYMBOL_89_ = 89,                       /* '-'  */
  YYSYMBOL_90_ = 90,                       /* '~'  */
  YYSYMBOL_91_ = 91,                       /* '!'  */
  YYSYMBOL_92_ = 92,                       /* '/'  */
  YYSYMBOL_93_ = 93,                       /* '%'  */
  YYSYMBOL_94_ = 94,                       /* '<'  */
  YYSYMBOL_95_ = 95,                       /* '>'  */
  YYSYMBOL_96_ = 96,                       /* '^'  */
  YYSYMBOL_97_ = 97,                       /* '|'  */
  YYSYMBOL_98_ = 98,                       /* '?'  */
  YYSYMBOL_99_ = 99,                       /* '='  */
  YYSYMBOL_100_ = 100,                     /* ';'  */
  YYSYMBOL_YYACCEPT = 101,                 /* $accept  */
  YYSYMBOL_primary_expression = 102,       /* primary_expression  */
  YYSYMBOL_constant = 103,                 /* constant  */
  YYSYMBOL_enumeration_constant = 104,     /* enumeration_constant  */
  YYSYMBOL_string = 105,                   /* string  */
  YYSYMBOL_generic_selection = 106,        /* generic_selection  */
  YYSYMBOL_generic_assoc_list = 107,       /* generic_assoc_list  */
  YYSYMBOL_generic_association = 108,      /* generic_association  */
  YYSYMBOL_postfix_expression = 109,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 110, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 111,         /* unary_expression  */
  YYSYMBOL_unary_operator = 112,           /* unary_operator  */
  YYSYMBOL_cast_expression = 113,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 114, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 115,      /* additive_expression  */
  YYSYMBOL_shift_expression = 116,         /* shift_expression  */
  YYSYMBOL_relational_expression = 117,    /* relational_expression  */
  YYSYMBOL_equality_expression = 118,      /* equality_expression  */
  YYSYMBOL_and_expression = 119,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 120,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 121,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 122,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 123,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 124,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 125,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 126,      /* assignment_operator  */
  YYSYMBOL_expression = 127,               /* expression  */
  YYSYMBOL_constant_expression = 128,      /* constant_expression  */
  YYSYMBOL_declaration = 129,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 130,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 131,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 132,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 133,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 134,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 135, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 136,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 137,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 138,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 139, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 140,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 141,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 142,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 143,          /* enumerator_list  */
  YYSYMBOL_enumerator = 144,               /* enumerator  */
  YYSYMBOL_type_qualifier = 145,           /* type_qualifier  */
  YYSYMBOL_function_specifier = 146,       /* function_specifier  */
  YYSYMBOL_alignment_specifier = 147,      /* alignment_specifier  */
  YYSYMBOL_declarator = 148,               /* declarator  */
  YYSYMBOL_direct_declarator = 149,        /* direct_declarator  */
  YYSYMBOL_pointer = 150,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 151,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 152,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 153,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 154,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 155,          /* identifier_list  */
  YYSYMBOL_type_name = 156,                /* type_name  */
  YYSYMBOL_abstract_declarator = 157,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 158, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 159,              /* initializer  */
  YYSYMBOL_initializer_list = 160,         /* initializer_list  */
  YYSYMBOL_designation = 161,              /* designation  */
  YYSYMBOL_designator_list = 162,          /* designator_list  */
  YYSYMBOL_designator = 163,               /* designator  */
  YYSYMBOL_static_assert_declaration = 164, /* static_assert_declaration  */
  YYSYMBOL_statement = 165,                /* statement  */
  YYSYMBOL_labeled_statement = 166,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 167,       /* compound_statement  */
  YYSYMBOL_block_item_list = 168,          /* block_item_list  */
  YYSYMBOL_block_item = 169,               /* block_item  */
  YYSYMBOL_expression_statement = 170,     /* expression_statement  */
  YYSYMBOL_selection_statement = 171,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 172,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 173,           /* jump_statement  */
  YYSYMBOL_translation_unit = 174,         /* translation_unit  */
  YYSYMBOL_external_declaration = 175,     /* external_declaration  */
  YYSYMBOL_function_definition = 176,      /* function_definition  */
  YYSYMBOL_declaration_list = 177          /* declaration_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2575

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  274
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  478

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,     2,     2,     2,    93,    86,     2,
      77,    78,    87,    88,    79,    89,    83,    92,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    80,   100,
      94,    99,    95,    98,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    81,     2,    82,    96,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    97,    85,    90,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   175,   175,   176,   177,   178,   179,   183,   184,   185,
     189,   193,   194,   198,   202,   203,   207,   208,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   225,   226,
     230,   231,   232,   233,   234,   235,   236,   240,   241,   242,
     243,   244,   245,   249,   250,   254,   255,   256,   257,   261,
     262,   263,   267,   268,   269,   273,   274,   275,   276,   277,
     281,   282,   283,   287,   288,   292,   293,   297,   298,   302,
     303,   307,   308,   312,   313,   317,   318,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   336,   337,
     341,   345,   346,   347,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   364,   365,   369,   370,   374,   375,
     376,   377,   378,   379,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   396,   397,   398,   402,
     403,   404,   408,   409,   413,   414,   418,   419,   420,   424,
     425,   426,   427,   431,   432,   436,   437,   438,   442,   443,
     444,   445,   446,   450,   451,   455,   456,   464,   465,   466,
     471,   472,   476,   477,   481,   482,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     503,   504,   505,   506,   510,   511,   515,   516,   520,   521,
     525,   526,   527,   531,   532,   536,   537,   541,   542,   543,
     547,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   571,   572,   573,   577,   578,   579,   580,   584,   588,
     589,   593,   594,   598,   602,   603,   604,   605,   606,   607,
     608,   612,   613,   614,   618,   619,   623,   624,   628,   629,
     633,   634,   638,   639,   640,   644,   645,   646,   647,   648,
     649,   653,   654,   655,   656,   657,   661,   662,   666,   667,
     668,   672,   673,   677,   678
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "I_CONSTANT", "F_CONSTANT", "STRING_LITERAL", "FUNC_NAME", "SIZEOF",
  "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF_NAME",
  "ENUMERATION_CONSTANT", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "INLINE", "CONST", "RESTRICT", "VOLATILE", "BOOL", "CHAR",
  "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "VOID",
  "COMPLEX", "IMAGINARY", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE",
  "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "ALIGNAS", "ALIGNOF", "ATOMIC", "GENERIC",
  "NORETURN", "STATIC_ASSERT", "THREAD_LOCAL", "P_THEN", "'('", "')'",
  "','", "':'", "'['", "']'", "'.'", "'{'", "'}'", "'&'", "'*'", "'+'",
  "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'",
  "'='", "';'", "$accept", "primary_expression", "constant",
  "enumeration_constant", "string", "generic_selection",
  "generic_assoc_list", "generic_association", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "function_specifier", "alignment_specifier",
  "declarator", "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator",
  "static_assert_declaration", "statement", "labeled_statement",
  "compound_statement", "block_item_list", "block_item",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "declaration_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,    40,    41,    44,
      58,    91,    93,    46,   123,   125,    38,    42,    43,    45,
     126,    33,    47,    37,    60,    62,    94,   124,    63,    61,
      59
};
#endif

#define YYPACT_NINF (-370)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2009,   -90,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,  -370,    30,   -42,  -370,     3,
    -370,  -370,    51,  2419,  2419,  -370,    34,  -370,  2419,  2419,
    2419,  -370,  1901,  -370,  -370,  -370,   -16,   119,   912,  1733,
    -370,    59,    -9,  -370,   -66,  -370,  2055,   -39,    52,  -370,
    -370,    12,  2457,  -370,  -370,  -370,  -370,  -370,   119,  -370,
      41,    83,  -370,  -370,  -370,  -370,  -370,  -370,  1755,  1777,
    1777,  -370,    65,    78,   912,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  -370,   166,  -370,  1733,  -370,   116,
     -62,   206,    71,   205,    94,   105,    92,   193,    45,  -370,
     138,  2520,    86,  2520,   152,   156,   159,  -370,  -370,    -9,
      59,  -370,   517,  1489,  -370,    51,  -370,  2275,  1954,  1001,
     -39,  2457,  2173,  -370,    25,  -370,    85,  1733,    56,  -370,
     912,  -370,   912,  -370,  -370,  2520,  1733,   387,  -370,  -370,
     145,   200,   241,  -370,  -370,  1511,  1733,   276,  -370,  1733,
    1733,  1733,  1733,  1733,  1733,  1733,  1733,  1733,  1733,  1733,
    1733,  1733,  1733,  1733,  1733,  1733,  1733,  1733,  -370,  -370,
    2123,  1023,   -25,  -370,   117,  -370,  -370,   275,  -370,  -370,
    -370,  -370,   184,   186,   204,  1733,   207,   212,   214,   215,
     426,   216,   291,   195,   196,   783,  -370,  -370,   -59,  -370,
    -370,  -370,  -370,   639,  -370,  -370,  -370,  -370,  -370,  1378,
    -370,  -370,  -370,  -370,  -370,  -370,    58,   220,   221,  -370,
     147,  1467,  -370,   223,   227,  1112,  2221,  -370,  -370,  1733,
    -370,   -47,  -370,   222,    63,  -370,  -370,  -370,  -370,   225,
     232,   233,   235,  -370,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,  -370,  -370,  1733,  -370,  1733,  1600,  -370,  -370,
     155,  -370,   118,  -370,  -370,  -370,  -370,   116,   116,   -62,
     -62,   206,   206,   206,   206,    71,    71,   205,    94,   105,
      92,   193,   162,  -370,   239,   243,  1467,  -370,   237,   240,
    1134,   117,  2328,  1223,   246,  -370,   426,   248,   426,  1733,
    1733,  1733,   267,   730,   231,  -370,  -370,  -370,    81,  -370,
    -370,  -370,  1733,   329,  -370,    93,  1489,   -32,  -370,  1845,
    -370,   129,  -370,  -370,  2375,  -370,   330,   252,  1467,  -370,
    -370,  1733,  -370,   254,   255,  -370,  -370,    72,  -370,  1733,
    -370,   257,   257,  -370,  2494,  -370,  -370,  1378,  -370,  -370,
    1733,  -370,  1733,  -370,  -370,   256,  1467,  -370,  -370,  1733,
    -370,   261,  -370,   266,  1467,  -370,   263,   264,  1245,   247,
    -370,   426,  -370,   167,   172,   175,   271,   821,   821,  -370,
    -370,   274,  -370,  1267,  -370,  -370,  -370,  -370,  -370,  -370,
    -370,  -370,   277,   278,  -370,  -370,  -370,  -370,   269,   178,
    -370,   273,   100,  -370,  -370,  -370,   280,   281,  -370,  -370,
     282,  1467,  -370,  -370,  1733,  -370,   283,  -370,  -370,   426,
     426,   426,  1733,  1622,  1644,  -370,  -370,  -370,  1489,  -370,
    -370,  1733,  -370,  2494,  1733,  1356,  -370,  -370,  -370,  -370,
     284,   286,  -370,   297,  -370,  -370,   180,   426,   182,   426,
     185,  -370,  -370,  -370,  -370,  -370,  -370,  -370,   426,   272,
    -370,   426,  -370,   426,  -370,  -370,  -370,  -370
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,   128,   108,   109,   110,   112,   113,   160,   157,
     158,   159,   123,   115,   116,   117,   118,   121,   122,   119,
     120,   114,   124,   125,   132,   133,     0,     0,   161,     0,
     111,   269,     0,    95,    97,   126,     0,   127,    99,   101,
     103,    93,     0,   266,   268,   270,   152,     0,     0,     0,
     166,     0,   183,    91,     0,   104,   107,   165,     0,    94,
      96,   131,     0,    98,   100,   102,     1,   267,     0,    10,
     156,     0,   153,     2,     7,     8,    11,    12,     0,     0,
       0,     9,     0,     0,     0,    37,    38,    39,    40,    41,
      42,    18,     3,     4,     6,    30,    43,     0,    45,    49,
      52,    55,    60,    63,    65,    67,    69,    71,    73,    90,
       0,   140,   196,   142,     0,     0,     0,   184,   182,   181,
       0,    92,     0,     0,   273,     0,   272,     0,     0,     0,
     164,     0,     0,   134,     0,   138,     0,     0,     0,   148,
       0,    34,     0,    31,    32,     0,     0,    43,    75,    88,
       0,     0,     0,    24,    25,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   163,   139,
       0,     0,   198,   195,   199,   141,   162,     0,   167,   185,
     180,   105,   107,     0,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   244,   250,     0,   248,
     249,   234,   235,     0,   246,   236,   237,   238,   239,     0,
     223,   106,   274,   271,   193,   178,   192,     0,   187,   188,
       0,     0,   168,    38,     0,     0,     0,   129,   135,     0,
     136,     0,   143,   147,     0,   150,   155,   149,   154,     0,
       0,     0,     0,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    77,     0,     5,     0,     0,    23,    20,
       0,    28,     0,    22,    46,    47,    48,    50,    51,    53,
      54,    58,    59,    56,    57,    61,    62,    64,    66,    68,
      70,    72,     0,   217,     0,     0,     0,   201,    38,     0,
       0,   197,     0,     0,     0,   240,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   262,   263,   264,     0,   251,
     245,   247,     0,     0,   225,     0,     0,     0,   229,     0,
     190,   198,   191,   177,     0,   179,     0,     0,     0,   169,
     176,     0,   175,    38,     0,   130,   145,     0,   137,     0,
     151,    35,     0,    36,     0,    76,    89,     0,    44,    21,
       0,    19,     0,   218,   200,     0,     0,   202,   208,     0,
     207,     0,   219,     0,     0,   209,    38,     0,     0,     0,
     241,     0,   243,     0,     0,     0,     0,     0,     0,   261,
     265,     0,   232,     0,   221,   224,   228,   230,   186,   189,
     194,   171,     0,     0,   172,   174,   144,   146,     0,     0,
      14,     0,     0,    29,    74,   204,     0,     0,   206,   220,
       0,     0,   210,   216,     0,   215,     0,   233,   242,     0,
       0,     0,     0,     0,     0,   231,   222,   227,     0,   170,
     173,     0,    13,     0,     0,     0,    26,   203,   205,   212,
       0,     0,   213,   252,   254,   255,     0,     0,     0,     0,
       0,   226,    17,    15,    16,    27,   211,   214,     0,     0,
     259,     0,   257,     0,   253,   256,   260,   258
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -370,  -370,  -370,  -370,  -370,  -370,  -370,   -74,  -370,  -370,
     306,  -370,   -50,   107,   108,    46,   104,   199,   201,   202,
     203,   211,  -370,   -37,     1,  -370,   -82,   -34,    -6,     6,
    -370,   260,  -370,   -41,  -370,  -370,   250,  -116,    -5,  -370,
      35,  -370,   309,  -113,   -48,  -370,  -370,   -27,   -55,   -30,
    -112,  -109,  -370,    49,  -370,    29,   -89,  -174,  -122,    31,
    -369,  -370,    62,   -44,  -191,  -370,    17,  -370,   177,  -234,
    -370,  -370,  -370,  -370,   349,  -370,  -370
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    91,    92,    70,    93,    94,   409,   410,    95,   270,
     147,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   148,   149,   264,   208,   110,    31,   125,
      54,    55,    33,    34,    35,    36,   132,   133,   112,   241,
     242,    37,    71,    72,    38,    39,    40,   116,    57,    58,
     119,   294,   228,   229,   230,   411,   295,   184,   324,   325,
     326,   327,   328,    41,   210,   211,   212,   213,   214,   215,
     216,   217,   218,    42,    43,    44,   127
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     113,   221,   150,   130,   117,    56,    32,   111,   301,   312,
      45,   109,   109,   120,   113,   115,   238,   235,   135,   227,
     266,   111,   118,   183,   438,   248,   162,   163,    50,     9,
      10,    11,   347,    46,   121,    48,   113,    61,   128,    59,
      60,   319,   129,   111,    63,    64,    65,   158,    32,   322,
     124,   323,   180,   348,    50,    50,   181,   134,   150,    69,
     150,    50,    50,   113,   176,   113,    69,   396,    68,   300,
     111,   189,   111,   126,   272,    50,   438,   114,    52,   388,
      49,   117,   182,   113,   113,   166,   167,   135,   135,   190,
     111,   111,   113,   192,   113,   292,   131,   113,   192,   111,
     109,   111,    51,   246,   111,   239,   179,   243,   185,   274,
     275,   276,    52,   151,    47,   380,   209,   382,    62,   338,
     238,   222,    69,   318,   220,   240,   134,   134,    51,    51,
     234,   248,    50,   117,   226,   329,    51,   332,    52,   181,
     137,   247,   145,   177,   223,    52,    52,   252,   350,    51,
     182,    53,   239,   433,   434,   146,   271,   301,   109,    52,
     266,   307,   138,   180,   244,   168,   169,   181,   139,   249,
     245,   250,   393,    52,   251,   152,   153,   154,   394,   445,
     172,   390,   299,   117,   366,   446,   226,   189,   113,   174,
     428,   378,   135,   373,   302,   111,   331,   266,   303,   330,
     361,   173,   109,   159,   395,   346,   329,   209,   160,   161,
     181,   175,   281,   282,   283,   284,   178,   358,   164,   165,
     220,   170,   171,   265,   266,   335,   336,   383,   384,   385,
     186,   134,   337,   359,   360,   187,   344,   188,   453,   454,
     455,   266,   362,   155,   268,   429,   266,   156,   117,   157,
     430,   266,   189,   431,   266,   117,   442,   443,   469,   266,
     471,   266,   421,   473,   266,   355,   470,   356,   472,   277,
     278,   437,   279,   280,   285,   286,   130,   474,   267,   273,
     476,   304,   477,   123,   306,   109,   305,   308,   391,   309,
     189,   310,   311,   313,   314,   315,   316,   365,   333,   331,
     334,   371,   349,   351,   377,   339,   113,   387,   226,   340,
     352,   353,   109,   111,   354,   407,   461,   363,   189,   367,
     243,   364,   368,   437,   379,   414,   117,   220,   381,   386,
     189,   389,   392,   400,   401,   226,   404,   405,   415,   402,
     226,   357,   403,   418,   419,   422,   423,   427,   432,   441,
     456,   458,   460,   444,    96,    96,   435,   468,   220,   439,
     440,   413,   447,   448,   449,   452,   466,   416,   467,   463,
     417,   287,   475,   189,   288,   420,   289,   136,   290,   426,
     191,   236,   406,   399,   141,   143,   144,   291,   412,   397,
     321,    67,     0,     0,   220,   113,     0,     0,     0,     0,
       0,     0,   111,    96,     0,     0,     0,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,     0,     0,     0,
       0,     0,   450,     0,     0,   451,     0,   193,     0,   194,
      74,    75,    76,    77,    78,     0,    79,    80,     0,   220,
       0,     0,   462,    96,     0,   464,   220,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,   195,   196,   197,   263,   198,   199,   200,
     201,   202,   203,   204,   205,     0,    82,     0,    83,     0,
       0,    96,     0,    84,     0,     0,     0,     0,     0,     0,
     122,     0,    85,    86,    87,    88,    89,    90,   193,     0,
     194,    74,    75,    76,    77,    78,   207,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     2,    81,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    96,   195,   196,   197,     0,   198,   199,
     200,   201,   202,   203,   204,   205,    27,    82,     0,    83,
      28,    29,    30,     0,    84,     0,     0,     0,     0,     0,
       0,   122,   206,    85,    86,    87,    88,    89,    90,     0,
       0,     0,     0,     0,     0,     0,     0,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     193,     0,   194,    74,    75,    76,    77,    78,     0,    79,
      80,     0,     0,     0,     0,    96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     2,
      81,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     0,   195,   196,   197,     0,
     198,   199,   200,   201,   202,   203,   204,   205,    27,    82,
       0,    83,    28,    29,    30,     0,    84,     0,     0,     0,
       0,     0,     0,   122,   320,    85,    86,    87,    88,    89,
      90,     0,     0,    73,    74,    75,    76,    77,    78,   207,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,    81,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    73,    74,    75,    76,
      77,    78,     0,    79,    80,     0,     0,     0,     0,    27,
      82,     0,    83,    28,    29,    30,     0,    84,     0,     0,
       0,     0,     0,     0,    81,     0,    85,    86,    87,    88,
      89,    90,     0,     0,    73,    74,    75,    76,    77,    78,
     207,    79,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    81,    82,     0,    83,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,   317,     0,     0,     0,     0,     0,     0,
       0,    82,     0,    83,     0,     0,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,    90,     0,     0,    73,    74,    75,    76,    77,
      78,   207,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,    81,     0,     0,     0,     0,     0,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,    83,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,    90,    73,    74,    75,    76,    77,    78,
       0,    79,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    73,    74,    75,    76,
      77,    78,    81,    79,    80,   231,     0,     0,     0,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,     0,   296,     0,     0,
       0,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,    82,     0,    83,     0,     0,     0,     0,    84,     0,
       0,     0,     0,   232,     0,     0,     0,    85,   233,    87,
      88,    89,    90,    82,     0,    83,     0,     0,     0,     0,
      84,     0,     0,     0,     0,   297,     0,     0,     0,    85,
     298,    87,    88,    89,    90,    73,    74,    75,    76,    77,
      78,     0,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    74,    75,
      76,    77,    78,    81,    79,    80,   341,     0,     0,     0,
       9,    10,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,     0,     0,   369,     0,
       0,     0,     9,    10,    11,     0,     0,     0,     0,     0,
       0,     0,    82,     0,    83,     0,     0,     0,     0,    84,
       0,     0,     0,     0,   342,     0,     0,     0,    85,   343,
      87,    88,    89,    90,    82,     0,    83,     0,     0,     0,
       0,    84,     0,     0,     0,     0,   370,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    73,    74,    75,    76,
      77,    78,     0,    79,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    81,    79,    80,   374,     0,     0,
       0,     9,    10,    11,     0,     0,     0,     0,     0,     0,
      73,    74,    75,    76,    77,    78,    81,    79,    80,   424,
       0,     0,     0,     9,    10,    11,     0,     0,     0,     0,
       0,     0,     0,    82,     0,    83,     0,     0,    81,     0,
      84,     0,     0,     0,     0,   375,     0,     0,     0,    85,
     376,    87,    88,    89,    90,    82,     0,    83,     0,     0,
       0,     0,    84,     0,     0,     0,     0,   425,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    82,     0,    83,
       0,     0,     0,     0,    84,     0,     0,     0,   322,     0,
     323,   219,   436,    85,    86,    87,    88,    89,    90,    73,
      74,    75,    76,    77,    78,     0,    79,    80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    81,    79,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,    83,     0,
       0,     0,     0,    84,     0,     0,     0,   322,     0,   323,
     219,   465,    85,    86,    87,    88,    89,    90,    82,     0,
      83,     0,     0,     0,     0,    84,     0,     0,     0,   322,
       0,   323,   219,     0,    85,    86,    87,    88,    89,    90,
      73,    74,    75,    76,    77,    78,     0,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,    81,    79,
      80,     0,     0,     0,     0,     9,    10,    11,     0,     0,
       0,     0,     0,     0,    73,    74,    75,    76,    77,    78,
      81,    79,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,    83,
       0,     0,    81,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,    90,    82,
       0,    83,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,   219,     0,    85,    86,    87,    88,    89,
      90,    82,     0,    83,     0,     0,     0,     0,    84,   269,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,    90,    73,    74,    75,    76,    77,    78,     0,
      79,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,    74,    75,    76,    77,
      78,    81,    79,    80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,    74,    75,
      76,    77,    78,    81,    79,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,     0,     0,    81,     0,    84,     0,     0,
       0,     0,     0,     0,   357,     0,    85,    86,    87,    88,
      89,    90,    82,     0,    83,     0,     0,     0,     0,    84,
     457,     0,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,    90,    82,     0,    83,     0,     0,     0,
       0,    84,   459,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    73,    74,    75,    76,
      77,    78,     0,    79,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    81,    79,    80,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,    74,    75,    76,    77,    78,    81,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,     0,    83,     0,     0,    81,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    82,     0,    83,     0,     0,
       0,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    82,    50,    83,
       0,     0,     0,     0,   142,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,    90,     0,
       0,     0,     0,     0,     0,     2,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    66,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,    28,     0,
      30,     0,   329,   293,     0,     0,   181,     0,     0,     0,
       0,     2,    52,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,   224,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,     0,     0,     0,    28,    29,    30,     0,     0,     0,
       0,     0,     0,     0,     2,     0,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,     0,     0,     0,    28,     0,    30,
       0,     0,   225,     0,     0,     0,     0,     0,     0,     2,
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
       0,     0,    28,    29,    30,     2,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,   123,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,     0,    28,     0,    30,     0,
     180,   293,     0,     2,   181,     0,     0,     0,     0,     0,
      52,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     2,     0,     0,     0,     0,     0,     0,   237,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,   345,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,     2,   122,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    28,     0,    30,     0,     2,   372,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,   398,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,    28,     2,
      30,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,    27,     0,
       0,     0,    28,     0,    30,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     0,     0,     0,     0,     0,
       0,    29,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       2,     0,   408,     0,     0,     0,     0,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26
};

static const yytype_int16 yycheck[] =
{
      48,   123,    84,    58,    52,    32,     0,    48,   182,   200,
     100,    48,    49,    79,    62,    49,   132,   129,    62,   128,
      79,    62,    52,   112,   393,   138,    88,    89,     3,    38,
      39,    40,    79,     3,   100,    77,    84,     3,    77,    33,
      34,   100,    81,    84,    38,    39,    40,    97,    42,    81,
      56,    83,    77,   100,     3,     3,    81,    62,   140,     3,
     142,     3,     3,   111,    19,   113,     3,    99,    84,   181,
     111,   119,   113,    56,   156,     3,   445,    48,    87,   313,
      77,   129,   112,   131,   132,    14,    15,   131,   132,   119,
     131,   132,   140,   120,   142,   177,    84,   145,   125,   140,
     137,   142,    77,   137,   145,    80,   111,   134,   113,   159,
     160,   161,    87,    84,    84,   306,   122,   308,    84,   231,
     236,   127,     3,   205,   123,   100,   131,   132,    77,    77,
     129,   244,     3,   181,   128,    77,    77,   226,    87,    81,
      99,    85,    77,    98,   127,    87,    87,   146,    85,    77,
     180,   100,    80,   387,   388,    77,   155,   331,   195,    87,
      79,   195,    79,    77,    79,    94,    95,    81,    85,   140,
      85,   142,    79,    87,   145,     9,    10,    11,    85,    79,
      86,   100,   181,   231,   296,    85,   180,   235,   236,    97,
     381,   303,   236,   302,    77,   236,   226,    79,    81,   226,
      82,    96,   239,    87,   326,   239,    77,   213,    92,    93,
      81,    18,   166,   167,   168,   169,    78,   267,    12,    13,
     219,    16,    17,    78,    79,    78,    79,   309,   310,   311,
      78,   236,   231,    78,    79,    79,   235,    78,   429,   430,
     431,    79,    80,    77,     3,    78,    79,    81,   296,    83,
      78,    79,   300,    78,    79,   303,    78,    79,    78,    79,
      78,    79,   374,    78,    79,   264,   457,   266,   459,   162,
     163,   393,   164,   165,   170,   171,   331,   468,    78,     3,
     471,     6,   473,    99,    80,   322,   100,    80,   322,    77,
     338,    77,    77,    77,     3,   100,   100,   296,    78,   329,
      79,   300,    80,    78,   303,    82,   354,   313,   302,    82,
      78,    78,   349,   354,    79,   349,   438,    78,   366,    82,
     347,    78,    82,   445,    78,   362,   374,   326,    80,    62,
     378,   100,     3,     3,    82,   329,    82,    82,    82,   338,
     334,    84,   341,    82,    78,    82,    82,   100,    77,    80,
     432,   433,   434,    80,    48,    49,    82,    60,   357,    82,
      82,   360,    82,    82,    82,    82,    82,   366,    82,   443,
     369,   172,   100,   421,   173,   374,   174,    68,   175,   378,
     120,   131,   347,   334,    78,    79,    80,   176,   357,   327,
     213,    42,    -1,    -1,   393,   443,    -1,    -1,    -1,    -1,
      -1,    -1,   443,    97,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,   421,    -1,    -1,   424,    -1,     1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,   438,
      -1,    -1,   441,   137,    -1,   444,   445,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,    57,    58,    59,    99,    61,    62,    63,
      64,    65,    66,    67,    68,    -1,    70,    -1,    72,    -1,
      -1,   195,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    86,    87,    88,    89,    90,    91,     1,    -1,
       3,     4,     5,     6,     7,     8,   100,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   239,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,   267,    57,    58,    59,    -1,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    72,
      73,    74,    75,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   322,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    -1,    -1,    -1,    -1,   349,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   362,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    57,    58,    59,    -1,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    72,    73,    74,    75,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    -1,     3,     4,     5,     6,     7,     8,   100,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    69,
      70,    -1,    72,    73,    74,    75,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    86,    87,    88,    89,
      90,    91,    -1,    -1,     3,     4,     5,     6,     7,     8,
     100,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    70,    -1,    72,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    -1,    -1,     3,     4,     5,     6,     7,
       8,   100,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    72,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,    31,    10,    11,    34,    -1,    -1,    -1,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,    -1,
      -1,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    70,    -1,    72,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      87,    88,    89,    90,    91,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    31,    10,    11,    34,    -1,    -1,    -1,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    34,    -1,
      -1,    -1,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    72,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    70,    -1,    72,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,    31,    10,    11,    34,    -1,    -1,
      -1,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,    31,    10,    11,    34,
      -1,    -1,    -1,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    72,    -1,    -1,    31,    -1,
      77,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      87,    88,    89,    90,    91,    70,    -1,    72,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    70,    -1,    72,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    31,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    70,    -1,
      72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,
      -1,    83,    84,    -1,    86,    87,    88,    89,    90,    91,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,    31,    10,
      11,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
      31,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,
      -1,    -1,    31,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    70,
      -1,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    86,    87,    88,    89,    90,
      91,    70,    -1,    72,    -1,    -1,    -1,    -1,    77,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    31,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    31,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    -1,    -1,    31,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    86,    87,    88,    89,
      90,    91,    70,    -1,    72,    -1,    -1,    -1,    -1,    77,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    70,    -1,    72,    -1,    -1,    -1,
      -1,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,    31,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,    31,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    72,    -1,    -1,    31,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    90,    91,    70,    -1,    72,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    70,     3,    72,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,     0,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    73,    -1,
      75,    -1,    77,    78,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    30,    87,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    73,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    73,    -1,    75,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    73,    74,    75,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    73,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    99,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    -1,    -1,    -1,    73,    -1,    75,    -1,
      77,    78,    -1,    30,    81,    -1,    -1,    -1,    -1,    -1,
      87,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    85,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    85,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    73,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    84,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,
      -1,    73,    -1,    75,    -1,    30,    78,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    73,    30,
      75,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    69,    -1,
      -1,    -1,    73,    -1,    75,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      30,    -1,    58,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    30,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    69,    73,    74,
      75,   129,   130,   133,   134,   135,   136,   142,   145,   146,
     147,   164,   174,   175,   176,   100,     3,    84,    77,    77,
       3,    77,    87,   100,   131,   132,   148,   149,   150,   130,
     130,     3,    84,   130,   130,   130,     0,   175,    84,     3,
     104,   143,   144,     3,     4,     5,     6,     7,     8,    10,
      11,    31,    70,    72,    77,    86,    87,    88,    89,    90,
      91,   102,   103,   105,   106,   109,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     128,   134,   139,   145,   156,   128,   148,   145,   150,   151,
      79,   100,    84,    99,   129,   130,   167,   177,    77,    81,
     149,    84,   137,   138,   139,   164,   143,    99,    79,    85,
      77,   111,    77,   111,   111,    77,    77,   111,   124,   125,
     127,   156,     9,    10,    11,    77,    81,    83,   113,    87,
      92,    93,    88,    89,    12,    13,    14,    15,    94,    95,
      16,    17,    86,    96,    97,    18,    19,    98,    78,   139,
      77,    81,   150,   157,   158,   139,    78,    79,    78,   145,
     150,   132,   148,     1,     3,    57,    58,    59,    61,    62,
      63,    64,    65,    66,    67,    68,    85,   100,   127,   129,
     165,   166,   167,   168,   169,   170,   171,   172,   173,    84,
     125,   159,   129,   167,     3,    78,   130,   152,   153,   154,
     155,    34,    82,    87,   125,   151,   137,    85,   138,    80,
     100,   140,   141,   148,    79,    85,   128,    85,   144,   156,
     156,   156,   125,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    99,   126,    78,    79,    78,     3,    78,
     110,   125,   127,     3,   113,   113,   113,   114,   114,   115,
     115,   116,   116,   116,   116,   117,   117,   118,   119,   120,
     121,   122,   127,    78,   152,   157,    34,    82,    87,   125,
     151,   158,    77,    81,     6,   100,    80,   128,    80,    77,
      77,    77,   165,    77,     3,   100,   100,   100,   127,   100,
      85,   169,    81,    83,   159,   160,   161,   162,   163,    77,
     148,   150,   157,    78,    79,    78,    79,   125,   151,    82,
      82,    34,    82,    87,   125,    85,   128,    79,   100,    80,
      85,    78,    78,    78,    79,   125,   125,    84,   113,    78,
      79,    82,    80,    78,    78,   125,   151,    82,    82,    34,
      82,   125,    78,   152,    34,    82,    87,   125,   151,    78,
     165,    80,   165,   127,   127,   127,    62,   129,   170,   100,
     100,   128,     3,    79,    85,   159,    99,   163,    56,   154,
       3,    82,   125,   125,    82,    82,   141,   128,    58,   107,
     108,   156,   160,   125,   124,    82,   125,   125,    82,    78,
     125,   151,    82,    82,    34,    82,   125,   100,   165,    78,
      78,    78,    77,   170,   170,    82,    85,   159,   161,    82,
      82,    80,    78,    79,    80,    79,    85,    82,    82,    82,
     125,   125,    82,   165,   165,   165,   127,    78,   127,    78,
     127,   159,   125,   108,   125,    85,    82,    82,    60,    78,
     165,    78,   165,    78,   165,   100,   165,   165
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   102,   102,   102,   102,   103,   103,   103,
     104,   105,   105,   106,   107,   107,   108,   108,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   112,   112,   112,
     112,   112,   112,   113,   113,   114,   114,   114,   114,   115,
     115,   115,   116,   116,   116,   117,   117,   117,   117,   117,
     118,   118,   118,   119,   119,   120,   120,   121,   121,   122,
     122,   123,   123,   124,   124,   125,   125,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   127,   127,
     128,   129,   129,   129,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   132,   132,   133,   133,
     133,   133,   133,   133,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   135,
     135,   135,   136,   136,   137,   137,   138,   138,   138,   139,
     139,   139,   139,   140,   140,   141,   141,   141,   142,   142,
     142,   142,   142,   143,   143,   144,   144,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     150,   150,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   154,   155,   155,   156,   156,   157,   157,   157,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   159,   159,   159,   160,   160,   160,   160,   161,   162,
     162,   163,   163,   164,   165,   165,   165,   165,   165,   165,
     165,   166,   166,   166,   167,   167,   168,   168,   169,   169,
     170,   170,   171,   171,   171,   172,   172,   172,   172,   172,
     172,   173,   173,   173,   173,   173,   174,   174,   175,   175,
     175,   176,   176,   177,   177
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     6,     1,     3,     3,     3,     1,     4,
       3,     4,     3,     3,     2,     2,     6,     7,     1,     3,
       1,     2,     2,     2,     2,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     5,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     3,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       5,     2,     1,     1,     1,     2,     2,     3,     1,     2,
       1,     2,     1,     1,     3,     2,     3,     1,     4,     5,
       5,     6,     2,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     4,     4,     2,     1,     1,     3,     3,     4,
       6,     5,     5,     6,     5,     4,     4,     4,     3,     4,
       3,     2,     2,     1,     1,     2,     3,     1,     1,     3,
       2,     2,     1,     1,     3,     2,     1,     2,     1,     1,
       3,     2,     3,     5,     4,     5,     4,     3,     3,     3,
       4,     6,     5,     5,     6,     4,     4,     2,     3,     3,
       4,     3,     4,     1,     2,     1,     4,     3,     2,     1,
       2,     3,     2,     7,     1,     1,     1,     1,     1,     1,
       2,     3,     4,     3,     2,     3,     1,     2,     1,     1,
       1,     2,     5,     7,     5,     5,     7,     6,     7,     6,
       7,     3,     2,     2,     2,     3,     1,     2,     1,     1,
       2,     4,     3,     1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* primary_expression: IDENTIFIER  */
#line 175 "c99.y"
                                        { (yyval.node) = makeAstTerm(AST_ID, (yyvsp[0].text)); }
#line 2421 "c99.y.gen.c"
    break;

  case 3: /* primary_expression: constant  */
#line 176 "c99.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2427 "c99.y.gen.c"
    break;

  case 4: /* primary_expression: string  */
#line 177 "c99.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2433 "c99.y.gen.c"
    break;

  case 5: /* primary_expression: '(' expression ')'  */
#line 178 "c99.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 2439 "c99.y.gen.c"
    break;

  case 6: /* primary_expression: generic_selection  */
#line 179 "c99.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 2445 "c99.y.gen.c"
    break;

  case 7: /* constant: I_CONSTANT  */
#line 183 "c99.y"
                                        { (yyval.node) = makeAstTerm(AST_LITERAL_INT, (yyvsp[0].text)); }
#line 2451 "c99.y.gen.c"
    break;

  case 8: /* constant: F_CONSTANT  */
#line 184 "c99.y"
                                        { (yyval.node) = makeAstTerm(AST_LITERAL_FLOAT, (yyvsp[0].text)); }
#line 2457 "c99.y.gen.c"
    break;

  case 9: /* constant: ENUMERATION_CONSTANT  */
#line 185 "c99.y"
                                { (yyval.node) = makeAstTerm(AST_ID, (yyvsp[0].text)); }
#line 2463 "c99.y.gen.c"
    break;

  case 10: /* enumeration_constant: IDENTIFIER  */
#line 189 "c99.y"
                                        { (yyval.node) = makeAstTerm(AST_ID, (yyvsp[0].text)); }
#line 2469 "c99.y.gen.c"
    break;

  case 11: /* string: STRING_LITERAL  */
#line 193 "c99.y"
                                        { (yyval.node) = makeAstTerm(AST_LITERAL_STRING, (yyvsp[0].text)); }
#line 2475 "c99.y.gen.c"
    break;

  case 12: /* string: FUNC_NAME  */
#line 194 "c99.y"
                                                { (yyval.node) = makeAstTerm(AST_ID, (yyvsp[0].text)); }
#line 2481 "c99.y.gen.c"
    break;

  case 13: /* generic_selection: GENERIC '(' assignment_expression ',' generic_assoc_list ')'  */
#line 198 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_GENERIC, (yyvsp[-3].node), (yyvsp[-1].node), NULL); }
#line 2487 "c99.y.gen.c"
    break;

  case 14: /* generic_assoc_list: generic_association  */
#line 202 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 2493 "c99.y.gen.c"
    break;

  case 15: /* generic_assoc_list: generic_assoc_list ',' generic_association  */
#line 203 "c99.y"
                                                                        { (yyval.node) = appendAstChild((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2499 "c99.y.gen.c"
    break;

  case 16: /* generic_association: type_name ':' assignment_expression  */
#line 207 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_GENERIC_ENTRY, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2505 "c99.y.gen.c"
    break;

  case 17: /* generic_association: DEFAULT ':' assignment_expression  */
#line 208 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_GENERIC_DEFAULT_ENTRY, (yyvsp[0].node), NULL); }
#line 2511 "c99.y.gen.c"
    break;

  case 18: /* postfix_expression: primary_expression  */
#line 212 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2517 "c99.y.gen.c"
    break;

  case 19: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 213 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_EXPR_INDEX, (yyvsp[-3].node), (yyvsp[-1].node), NULL); }
#line 2523 "c99.y.gen.c"
    break;

  case 20: /* postfix_expression: postfix_expression '(' ')'  */
#line 214 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CALL, (yyvsp[-2].node), NULL); }
#line 2529 "c99.y.gen.c"
    break;

  case 21: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 215 "c99.y"
                                                                { (yyval.node) = makeAstNode(AST_EXPR_CALL, (yyvsp[-3].node), (yyvsp[-1].node), NULL); }
#line 2535 "c99.y.gen.c"
    break;

  case 22: /* postfix_expression: postfix_expression '.' IDENTIFIER  */
#line 216 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_EXPR_ACCESS_DIRECT, (yyvsp[-2].node), makeAstTerm(AST_ID, (yyvsp[0].text)), NULL); }
#line 2541 "c99.y.gen.c"
    break;

  case 23: /* postfix_expression: postfix_expression PTR_OP IDENTIFIER  */
#line 217 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_EXPR_ACCESS_PTR, (yyvsp[-2].node), makeAstTerm(AST_ID, (yyvsp[0].text)), NULL); }
#line 2547 "c99.y.gen.c"
    break;

  case 24: /* postfix_expression: postfix_expression INC_OP  */
#line 218 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_POST_INC, (yyvsp[-1].node), NULL); }
#line 2553 "c99.y.gen.c"
    break;

  case 25: /* postfix_expression: postfix_expression DEC_OP  */
#line 219 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_POST_DEC, (yyvsp[-1].node), NULL); }
#line 2559 "c99.y.gen.c"
    break;

  case 26: /* postfix_expression: '(' type_name ')' '{' initializer_list '}'  */
#line 220 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_INIT, (yyvsp[-4].node), (yyvsp[-1].node), NULL); }
#line 2565 "c99.y.gen.c"
    break;

  case 27: /* postfix_expression: '(' type_name ')' '{' initializer_list ',' '}'  */
#line 221 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_INIT, (yyvsp[-5].node), (yyvsp[-2].node), NULL); }
#line 2571 "c99.y.gen.c"
    break;

  case 28: /* argument_expression_list: assignment_expression  */
#line 225 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 2577 "c99.y.gen.c"
    break;

  case 29: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 226 "c99.y"
                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2583 "c99.y.gen.c"
    break;

  case 30: /* unary_expression: postfix_expression  */
#line 230 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2589 "c99.y.gen.c"
    break;

  case 31: /* unary_expression: INC_OP unary_expression  */
#line 231 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_PRE_INC, (yyvsp[0].node), NULL); }
#line 2595 "c99.y.gen.c"
    break;

  case 32: /* unary_expression: DEC_OP unary_expression  */
#line 232 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_PRE_DEC, (yyvsp[0].node), NULL); }
#line 2601 "c99.y.gen.c"
    break;

  case 33: /* unary_expression: unary_operator cast_expression  */
#line 233 "c99.y"
                                                                                        { (yyval.node) = makeAstNode((yyvsp[-1].kind), (yyvsp[0].node), NULL); }
#line 2607 "c99.y.gen.c"
    break;

  case 34: /* unary_expression: SIZEOF unary_expression  */
#line 234 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_SIZEOF, (yyvsp[0].node), NULL); }
#line 2613 "c99.y.gen.c"
    break;

  case 35: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 235 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_SIZEOF, (yyvsp[-1].node), NULL); }
#line 2619 "c99.y.gen.c"
    break;

  case 36: /* unary_expression: ALIGNOF '(' type_name ')'  */
#line 236 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_ALIGNOF, (yyvsp[-1].node), NULL); }
#line 2625 "c99.y.gen.c"
    break;

  case 37: /* unary_operator: '&'  */
#line 240 "c99.y"
                                { (yyval.kind) = AST_EXPR_UNARY_REF; }
#line 2631 "c99.y.gen.c"
    break;

  case 38: /* unary_operator: '*'  */
#line 241 "c99.y"
                                { (yyval.kind) = AST_EXPR_UNARY_UNREF; }
#line 2637 "c99.y.gen.c"
    break;

  case 39: /* unary_operator: '+'  */
#line 242 "c99.y"
                                { (yyval.kind) = AST_EXPR_UNARY_PLUS; }
#line 2643 "c99.y.gen.c"
    break;

  case 40: /* unary_operator: '-'  */
#line 243 "c99.y"
                                { (yyval.kind) = AST_EXPR_UNARY_MINUS; }
#line 2649 "c99.y.gen.c"
    break;

  case 41: /* unary_operator: '~'  */
#line 244 "c99.y"
                                { (yyval.kind) = AST_EXPR_BITS_INV; }
#line 2655 "c99.y.gen.c"
    break;

  case 42: /* unary_operator: '!'  */
#line 245 "c99.y"
                                { (yyval.kind) = AST_EXPR_BOOL_NOT; }
#line 2661 "c99.y.gen.c"
    break;

  case 43: /* cast_expression: unary_expression  */
#line 249 "c99.y"
                                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 2667 "c99.y.gen.c"
    break;

  case 44: /* cast_expression: '(' type_name ')' cast_expression  */
#line 250 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CAST, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2673 "c99.y.gen.c"
    break;

  case 45: /* multiplicative_expression: cast_expression  */
#line 254 "c99.y"
                                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 2679 "c99.y.gen.c"
    break;

  case 46: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 255 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_MUL, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2685 "c99.y.gen.c"
    break;

  case 47: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 256 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_DIV, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2691 "c99.y.gen.c"
    break;

  case 48: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 257 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_REM, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2697 "c99.y.gen.c"
    break;

  case 49: /* additive_expression: multiplicative_expression  */
#line 261 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2703 "c99.y.gen.c"
    break;

  case 50: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 262 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_PLUS, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2709 "c99.y.gen.c"
    break;

  case 51: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 263 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_MINUS, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2715 "c99.y.gen.c"
    break;

  case 52: /* shift_expression: additive_expression  */
#line 267 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2721 "c99.y.gen.c"
    break;

  case 53: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 268 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_BITS_SHL, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2727 "c99.y.gen.c"
    break;

  case 54: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 269 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_BITS_SHR, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2733 "c99.y.gen.c"
    break;

  case 55: /* relational_expression: shift_expression  */
#line 273 "c99.y"
                                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 2739 "c99.y.gen.c"
    break;

  case 56: /* relational_expression: relational_expression '<' shift_expression  */
#line 274 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CMP_LT, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2745 "c99.y.gen.c"
    break;

  case 57: /* relational_expression: relational_expression '>' shift_expression  */
#line 275 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CMP_GT, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2751 "c99.y.gen.c"
    break;

  case 58: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 276 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CMP_LTEQ, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2757 "c99.y.gen.c"
    break;

  case 59: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 277 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CMP_GTEQ, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2763 "c99.y.gen.c"
    break;

  case 60: /* equality_expression: relational_expression  */
#line 281 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2769 "c99.y.gen.c"
    break;

  case 61: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 282 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CMP_EQ, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2775 "c99.y.gen.c"
    break;

  case 62: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 283 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_CMP_NEQ, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2781 "c99.y.gen.c"
    break;

  case 63: /* and_expression: equality_expression  */
#line 287 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2787 "c99.y.gen.c"
    break;

  case 64: /* and_expression: and_expression '&' equality_expression  */
#line 288 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_EXPR_BITS_AND, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2793 "c99.y.gen.c"
    break;

  case 65: /* exclusive_or_expression: and_expression  */
#line 292 "c99.y"
                                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 2799 "c99.y.gen.c"
    break;

  case 66: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 293 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_BITS_XOR, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2805 "c99.y.gen.c"
    break;

  case 67: /* inclusive_or_expression: exclusive_or_expression  */
#line 297 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2811 "c99.y.gen.c"
    break;

  case 68: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 298 "c99.y"
                                                                { (yyval.node) = makeAstNode(AST_EXPR_BITS_OR, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2817 "c99.y.gen.c"
    break;

  case 69: /* logical_and_expression: inclusive_or_expression  */
#line 302 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2823 "c99.y.gen.c"
    break;

  case 70: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 303 "c99.y"
                                                                { (yyval.node) = makeAstNode(AST_EXPR_BOOL_AND, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2829 "c99.y.gen.c"
    break;

  case 71: /* logical_or_expression: logical_and_expression  */
#line 307 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2835 "c99.y.gen.c"
    break;

  case 72: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 308 "c99.y"
                                                                { (yyval.node) = makeAstNode(AST_EXPR_BOOL_OR, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2841 "c99.y.gen.c"
    break;

  case 73: /* conditional_expression: logical_or_expression  */
#line 312 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2847 "c99.y.gen.c"
    break;

  case 74: /* conditional_expression: logical_or_expression '?' expression ':' conditional_expression  */
#line 313 "c99.y"
                                                                          { (yyval.node) = makeAstNode(AST_EXPR_CONDITIONAL, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2853 "c99.y.gen.c"
    break;

  case 75: /* assignment_expression: conditional_expression  */
#line 317 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2859 "c99.y.gen.c"
    break;

  case 76: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 318 "c99.y"
                                                                     { (yyval.node) = makeAstNode((yyvsp[-1].kind), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 2865 "c99.y.gen.c"
    break;

  case 77: /* assignment_operator: '='  */
#line 322 "c99.y"
                                { (yyval.kind) = AST_EXPR_ASSIGN; }
#line 2871 "c99.y.gen.c"
    break;

  case 78: /* assignment_operator: MUL_ASSIGN  */
#line 323 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_MUL; }
#line 2877 "c99.y.gen.c"
    break;

  case 79: /* assignment_operator: DIV_ASSIGN  */
#line 324 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_DIV; }
#line 2883 "c99.y.gen.c"
    break;

  case 80: /* assignment_operator: MOD_ASSIGN  */
#line 325 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_REM; }
#line 2889 "c99.y.gen.c"
    break;

  case 81: /* assignment_operator: ADD_ASSIGN  */
#line 326 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_PLUS; }
#line 2895 "c99.y.gen.c"
    break;

  case 82: /* assignment_operator: SUB_ASSIGN  */
#line 327 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_MINUS; }
#line 2901 "c99.y.gen.c"
    break;

  case 83: /* assignment_operator: LEFT_ASSIGN  */
#line 328 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_BITS_SHL; }
#line 2907 "c99.y.gen.c"
    break;

  case 84: /* assignment_operator: RIGHT_ASSIGN  */
#line 329 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_BITS_SHR; }
#line 2913 "c99.y.gen.c"
    break;

  case 85: /* assignment_operator: AND_ASSIGN  */
#line 330 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_BITS_AND; }
#line 2919 "c99.y.gen.c"
    break;

  case 86: /* assignment_operator: XOR_ASSIGN  */
#line 331 "c99.y"
                        { (yyval.kind) = AST_EXPR_ASS_BITS_XOR; }
#line 2925 "c99.y.gen.c"
    break;

  case 87: /* assignment_operator: OR_ASSIGN  */
#line 332 "c99.y"
                                { (yyval.kind) = AST_EXPR_ASS_BITS_OR; }
#line 2931 "c99.y.gen.c"
    break;

  case 88: /* expression: assignment_expression  */
#line 336 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_LIST, (yyvsp[0].node), NULL); }
#line 2937 "c99.y.gen.c"
    break;

  case 89: /* expression: expression ',' assignment_expression  */
#line 337 "c99.y"
                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2943 "c99.y.gen.c"
    break;

  case 90: /* constant_expression: conditional_expression  */
#line 341 "c99.y"
                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 2949 "c99.y.gen.c"
    break;

  case 91: /* declaration: declaration_specifiers ';'  */
#line 345 "c99.y"
                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION, (yyvsp[-1].node), NULL); }
#line 2955 "c99.y.gen.c"
    break;

  case 92: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 346 "c99.y"
                                                                                        { (yyval.node) = registerTypeName(makeAstNode(AST_DECLARATION, (yyvsp[-2].node), (yyvsp[-1].node), NULL)); }
#line 2961 "c99.y.gen.c"
    break;

  case 93: /* declaration: static_assert_declaration  */
#line 347 "c99.y"
                                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2967 "c99.y.gen.c"
    break;

  case 94: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 351 "c99.y"
                                                                                        { (yyval.node) = prependAstChild((yyvsp[0].node), (yyvsp[-1].node)); }
#line 2973 "c99.y.gen.c"
    break;

  case 95: /* declaration_specifiers: storage_class_specifier  */
#line 352 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 2979 "c99.y.gen.c"
    break;

  case 96: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 353 "c99.y"
                                                                                                { (yyval.node) = prependAstChild((yyvsp[0].node), (yyvsp[-1].node)); }
#line 2985 "c99.y.gen.c"
    break;

  case 97: /* declaration_specifiers: type_specifier  */
#line 354 "c99.y"
                                                                                                                        { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 2991 "c99.y.gen.c"
    break;

  case 98: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 355 "c99.y"
                                                                                                { (yyval.node) = prependAstChild((yyvsp[0].node), (yyvsp[-1].node)); }
#line 2997 "c99.y.gen.c"
    break;

  case 99: /* declaration_specifiers: type_qualifier  */
#line 356 "c99.y"
                                                                                                                        { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 3003 "c99.y.gen.c"
    break;

  case 100: /* declaration_specifiers: function_specifier declaration_specifiers  */
#line 357 "c99.y"
                                                                                                { (yyval.node) = prependAstChild((yyvsp[0].node), (yyvsp[-1].node)); }
#line 3009 "c99.y.gen.c"
    break;

  case 101: /* declaration_specifiers: function_specifier  */
#line 358 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 3015 "c99.y.gen.c"
    break;

  case 102: /* declaration_specifiers: alignment_specifier declaration_specifiers  */
#line 359 "c99.y"
                                                                                        { (yyval.node) = prependAstChild((yyvsp[0].node), (yyvsp[-1].node)); }
#line 3021 "c99.y.gen.c"
    break;

  case 103: /* declaration_specifiers: alignment_specifier  */
#line 360 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 3027 "c99.y.gen.c"
    break;

  case 104: /* init_declarator_list: init_declarator  */
#line 364 "c99.y"
                                                                                                                        { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 3033 "c99.y.gen.c"
    break;

  case 105: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 365 "c99.y"
                                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3039 "c99.y.gen.c"
    break;

  case 106: /* init_declarator: declarator '=' initializer  */
#line 369 "c99.y"
                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_VALUE_PLACE, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3045 "c99.y.gen.c"
    break;

  case 107: /* init_declarator: declarator  */
#line 370 "c99.y"
                                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_VALUE_PLACE, (yyvsp[0].node), NULL); }
#line 3051 "c99.y.gen.c"
    break;

  case 108: /* storage_class_specifier: TYPEDEF  */
#line 374 "c99.y"
                                                                                { (yyval.node) = makeAstTerm(AST_SSPEC_KW_TYPEDEF, (yyvsp[0].text)); }
#line 3057 "c99.y.gen.c"
    break;

  case 109: /* storage_class_specifier: EXTERN  */
#line 375 "c99.y"
                                                                                                                                { (yyval.node) = makeAstTerm(AST_SSPEC_KW_EXTERN, (yyvsp[0].text)); }
#line 3063 "c99.y.gen.c"
    break;

  case 110: /* storage_class_specifier: STATIC  */
#line 376 "c99.y"
                                                                                                                                { (yyval.node) = makeAstTerm(AST_SSPEC_KW_STATIC, (yyvsp[0].text)); }
#line 3069 "c99.y.gen.c"
    break;

  case 111: /* storage_class_specifier: THREAD_LOCAL  */
#line 377 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_SSPEC_KW_THREAD_LOCAL, (yyvsp[0].text));	}
#line 3075 "c99.y.gen.c"
    break;

  case 112: /* storage_class_specifier: AUTO  */
#line 378 "c99.y"
                                                                                                                                { (yyval.node) = makeAstTerm(AST_SSPEC_KW_AUTO, (yyvsp[0].text)); }
#line 3081 "c99.y.gen.c"
    break;

  case 113: /* storage_class_specifier: REGISTER  */
#line 379 "c99.y"
                                                                                                                                { (yyval.node) = makeAstTerm(AST_SSPEC_KW_REGISTER, (yyvsp[0].text)); }
#line 3087 "c99.y.gen.c"
    break;

  case 114: /* type_specifier: VOID  */
#line 383 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_VOID, (yyvsp[0].text)); }
#line 3093 "c99.y.gen.c"
    break;

  case 115: /* type_specifier: CHAR  */
#line 384 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_CHAR, (yyvsp[0].text)); }
#line 3099 "c99.y.gen.c"
    break;

  case 116: /* type_specifier: SHORT  */
#line 385 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_SHORT, (yyvsp[0].text)); }
#line 3105 "c99.y.gen.c"
    break;

  case 117: /* type_specifier: INT  */
#line 386 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_INT, (yyvsp[0].text)); }
#line 3111 "c99.y.gen.c"
    break;

  case 118: /* type_specifier: LONG  */
#line 387 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_LONG, (yyvsp[0].text)); }
#line 3117 "c99.y.gen.c"
    break;

  case 119: /* type_specifier: FLOAT  */
#line 388 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_FLOAT, (yyvsp[0].text)); }
#line 3123 "c99.y.gen.c"
    break;

  case 120: /* type_specifier: DOUBLE  */
#line 389 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_DOUBLE, (yyvsp[0].text)); }
#line 3129 "c99.y.gen.c"
    break;

  case 121: /* type_specifier: SIGNED  */
#line 390 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_SIGNED, (yyvsp[0].text)); }
#line 3135 "c99.y.gen.c"
    break;

  case 122: /* type_specifier: UNSIGNED  */
#line 391 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_UNSIGNED, (yyvsp[0].text)); }
#line 3141 "c99.y.gen.c"
    break;

  case 123: /* type_specifier: BOOL  */
#line 392 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_BOOL, (yyvsp[0].text)); }
#line 3147 "c99.y.gen.c"
    break;

  case 124: /* type_specifier: COMPLEX  */
#line 393 "c99.y"
                                                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_COMPLEX, (yyvsp[0].text)); }
#line 3153 "c99.y.gen.c"
    break;

  case 125: /* type_specifier: IMAGINARY  */
#line 394 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_TYPE_IMAGINARY, (yyvsp[0].text)); }
#line 3159 "c99.y.gen.c"
    break;

  case 126: /* type_specifier: struct_or_union_specifier  */
#line 396 "c99.y"
                                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3165 "c99.y.gen.c"
    break;

  case 127: /* type_specifier: enum_specifier  */
#line 397 "c99.y"
                                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3171 "c99.y.gen.c"
    break;

  case 128: /* type_specifier: TYPEDEF_NAME  */
#line 398 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_TYPE_NAMED, makeAstTerm(AST_ID, (yyvsp[0].text)), NULL); }
#line 3177 "c99.y.gen.c"
    break;

  case 129: /* struct_or_union_specifier: struct_or_union '{' struct_declaration_list '}'  */
#line 402 "c99.y"
                                                                                { (yyval.node) = makeAstNode((yyvsp[-3].kind), (yyvsp[-1].node), NULL); }
#line 3183 "c99.y.gen.c"
    break;

  case 130: /* struct_or_union_specifier: struct_or_union IDENTIFIER '{' struct_declaration_list '}'  */
#line 403 "c99.y"
                                                                    { (yyval.node) = makeAstNode((yyvsp[-4].kind), makeAstTerm(AST_ID, (yyvsp[-3].text)), (yyvsp[-1].node), NULL); }
#line 3189 "c99.y.gen.c"
    break;

  case 131: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 404 "c99.y"
                                                                                                { (yyval.node) = makeAstNode((yyvsp[-1].kind), makeAstTerm(AST_ID, (yyvsp[0].text)), NULL); }
#line 3195 "c99.y.gen.c"
    break;

  case 132: /* struct_or_union: STRUCT  */
#line 408 "c99.y"
                                                                                                                        { (yyval.kind) = AST_TYPE_STRUCT; }
#line 3201 "c99.y.gen.c"
    break;

  case 133: /* struct_or_union: UNION  */
#line 409 "c99.y"
                                                                                                                        { (yyval.kind) = AST_TYPE_UNION; }
#line 3207 "c99.y.gen.c"
    break;

  case 134: /* struct_declaration_list: struct_declaration  */
#line 413 "c99.y"
                                                                                                        { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 3213 "c99.y.gen.c"
    break;

  case 135: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 414 "c99.y"
                                                                                { (yyval.node) = appendAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3219 "c99.y.gen.c"
    break;

  case 138: /* struct_declaration: static_assert_declaration  */
#line 420 "c99.y"
                                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3225 "c99.y.gen.c"
    break;

  case 139: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 424 "c99.y"
                                                                                        { (yyval.node) = prependAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3231 "c99.y.gen.c"
    break;

  case 140: /* specifier_qualifier_list: type_specifier  */
#line 425 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 3237 "c99.y.gen.c"
    break;

  case 141: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 426 "c99.y"
                                                                                        { (yyval.node) = prependAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3243 "c99.y.gen.c"
    break;

  case 142: /* specifier_qualifier_list: type_qualifier  */
#line 427 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 3249 "c99.y.gen.c"
    break;

  case 145: /* struct_declarator: ':' constant_expression  */
#line 436 "c99.y"
                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_VALUE_PLACE, (yyvsp[0].node), NULL); }
#line 3255 "c99.y.gen.c"
    break;

  case 146: /* struct_declarator: declarator ':' constant_expression  */
#line 437 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_VALUE_PLACE, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3261 "c99.y.gen.c"
    break;

  case 147: /* struct_declarator: declarator  */
#line 438 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_DECLARATION_VALUE_PLACE, (yyvsp[0].node), NULL); }
#line 3267 "c99.y.gen.c"
    break;

  case 148: /* enum_specifier: ENUM '{' enumerator_list '}'  */
#line 442 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_TYPE_ENUM, (yyvsp[-1].node), NULL); }
#line 3273 "c99.y.gen.c"
    break;

  case 149: /* enum_specifier: ENUM '{' enumerator_list ',' '}'  */
#line 443 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_TYPE_ENUM, (yyvsp[-2].node), NULL); }
#line 3279 "c99.y.gen.c"
    break;

  case 150: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list '}'  */
#line 444 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_TYPE_ENUM, (yyvsp[-3].text), (yyvsp[-1].node), NULL); }
#line 3285 "c99.y.gen.c"
    break;

  case 151: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list ',' '}'  */
#line 445 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_TYPE_ENUM, (yyvsp[-4].text), (yyvsp[-2].node), NULL); }
#line 3291 "c99.y.gen.c"
    break;

  case 152: /* enum_specifier: ENUM IDENTIFIER  */
#line 446 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_TYPE_ENUM, (yyvsp[0].text), NULL); }
#line 3297 "c99.y.gen.c"
    break;

  case 153: /* enumerator_list: enumerator  */
#line 450 "c99.y"
                                                                                                                { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 3303 "c99.y.gen.c"
    break;

  case 154: /* enumerator_list: enumerator_list ',' enumerator  */
#line 451 "c99.y"
                                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3309 "c99.y.gen.c"
    break;

  case 155: /* enumerator: enumeration_constant '=' constant_expression  */
#line 455 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_ENUM_ENTRY, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3315 "c99.y.gen.c"
    break;

  case 156: /* enumerator: enumeration_constant  */
#line 456 "c99.y"
                                                                                                        { (yyval.node) = makeAstNode(AST_ENUM_ENTRY, (yyvsp[0].node), NULL); }
#line 3321 "c99.y.gen.c"
    break;

  case 157: /* type_qualifier: CONST  */
#line 464 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_TSPEC_KW_CONST, (yyvsp[0].text)); }
#line 3327 "c99.y.gen.c"
    break;

  case 158: /* type_qualifier: RESTRICT  */
#line 465 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_TSPEC_KW_RESTRICT, (yyvsp[0].text)); }
#line 3333 "c99.y.gen.c"
    break;

  case 159: /* type_qualifier: VOLATILE  */
#line 466 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_TSPEC_KW_VOLATILE, (yyvsp[0].text)); }
#line 3339 "c99.y.gen.c"
    break;

  case 160: /* function_specifier: INLINE  */
#line 471 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_FSPEC_KW_INLINE, (yyvsp[0].text)); }
#line 3345 "c99.y.gen.c"
    break;

  case 161: /* function_specifier: NORETURN  */
#line 472 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_FSPEC_KW_NORETURN, (yyvsp[0].text)); }
#line 3351 "c99.y.gen.c"
    break;

  case 162: /* alignment_specifier: ALIGNAS '(' type_name ')'  */
#line 476 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_SPEC_ALIGNAS_TYPE, (yyvsp[-1].node), NULL); }
#line 3357 "c99.y.gen.c"
    break;

  case 163: /* alignment_specifier: ALIGNAS '(' constant_expression ')'  */
#line 477 "c99.y"
                                                        { (yyval.node) = makeAstNode(AST_SPEC_ALIGNAS_CONST, (yyvsp[-1].node), NULL); }
#line 3363 "c99.y.gen.c"
    break;

  case 164: /* declarator: pointer direct_declarator  */
#line 481 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_ENTRY, (yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 3369 "c99.y.gen.c"
    break;

  case 165: /* declarator: direct_declarator  */
#line 482 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_DECLARATION_ENTRY, (yyvsp[0].node), NULL); }
#line 3375 "c99.y.gen.c"
    break;

  case 166: /* direct_declarator: IDENTIFIER  */
#line 486 "c99.y"
                                                                                                                                                        { (yyval.node) = makeAstNode(AST_LIST, makeAstTerm(AST_ID, (yyvsp[0].text)), NULL); }
#line 3381 "c99.y.gen.c"
    break;

  case 167: /* direct_declarator: '(' declarator ')'  */
#line 487 "c99.y"
                                                                                                                                                { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[-1].node), NULL); }
#line 3387 "c99.y.gen.c"
    break;

  case 168: /* direct_declarator: direct_declarator '[' ']'  */
#line 488 "c99.y"
                                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), makeAstTerm(AST_DECLARATION_ARRAY_SPEC, "")); }
#line 3393 "c99.y.gen.c"
    break;

  case 170: /* direct_declarator: direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'  */
#line 490 "c99.y"
                                                                                        { (yyval.node) = appendAstChild((yyvsp[-5].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "21"), (yyvsp[-2].node), (yyvsp[-1].node), NULL)); }
#line 3399 "c99.y.gen.c"
    break;

  case 171: /* direct_declarator: direct_declarator '[' STATIC assignment_expression ']'  */
#line 491 "c99.y"
                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-4].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "22"), (yyvsp[-1].node), NULL)); }
#line 3405 "c99.y.gen.c"
    break;

  case 172: /* direct_declarator: direct_declarator '[' type_qualifier_list '*' ']'  */
#line 492 "c99.y"
                                                                                                                        { (yyval.node) = appendAstChild((yyvsp[-4].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "23"), (yyvsp[-2].node), NULL)); }
#line 3411 "c99.y.gen.c"
    break;

  case 173: /* direct_declarator: direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'  */
#line 493 "c99.y"
                                                                                        { (yyval.node) = appendAstChild((yyvsp[-5].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "24"), (yyvsp[-3].node), (yyvsp[-1].node), NULL)); }
#line 3417 "c99.y.gen.c"
    break;

  case 174: /* direct_declarator: direct_declarator '[' type_qualifier_list assignment_expression ']'  */
#line 494 "c99.y"
                                                                                                { (yyval.node) = appendAstChild((yyvsp[-4].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "25"), (yyvsp[-2].node), (yyvsp[-1].node), NULL)); }
#line 3423 "c99.y.gen.c"
    break;

  case 175: /* direct_declarator: direct_declarator '[' type_qualifier_list ']'  */
#line 495 "c99.y"
                                                                                                                        { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "26"), (yyvsp[-1].node), NULL)); }
#line 3429 "c99.y.gen.c"
    break;

  case 176: /* direct_declarator: direct_declarator '[' assignment_expression ']'  */
#line 496 "c99.y"
                                                                                                                        { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_DECLARATION_ARRAY_SPEC, (yyvsp[-1].node), NULL)); }
#line 3435 "c99.y.gen.c"
    break;

  case 177: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 497 "c99.y"
                                                                                                                        { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_DECLARATION_PARAMS_SPEC, (yyvsp[-1].node), NULL)); }
#line 3441 "c99.y.gen.c"
    break;

  case 178: /* direct_declarator: direct_declarator '(' ')'  */
#line 498 "c99.y"
                                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), makeAstNode(AST_DECLARATION_PARAMS_SPEC, makeAstNode(AST_LIST, NULL), NULL)); }
#line 3447 "c99.y.gen.c"
    break;

  case 179: /* direct_declarator: direct_declarator '(' identifier_list ')'  */
#line 499 "c99.y"
                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_DECLARATION_PARAMS_SPEC, (yyvsp[-1].node), NULL)); }
#line 3453 "c99.y.gen.c"
    break;

  case 180: /* pointer: '*' type_qualifier_list pointer  */
#line 503 "c99.y"
                                                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_PTR_SPEC, (yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 3459 "c99.y.gen.c"
    break;

  case 181: /* pointer: '*' type_qualifier_list  */
#line 504 "c99.y"
                                                                                                                                                { (yyval.node) = makeAstNode(AST_DECLARATION_PTR_SPEC, (yyvsp[0].node), NULL); }
#line 3465 "c99.y.gen.c"
    break;

  case 182: /* pointer: '*' pointer  */
#line 505 "c99.y"
                                                                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_PTR_SPEC, (yyvsp[0].node), NULL); }
#line 3471 "c99.y.gen.c"
    break;

  case 183: /* pointer: '*'  */
#line 506 "c99.y"
                                                                                                                                                                { (yyval.node) = makeAstTerm(AST_DECLARATION_PTR_SPEC, NULL); }
#line 3477 "c99.y.gen.c"
    break;

  case 184: /* type_qualifier_list: type_qualifier  */
#line 510 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_DECL_SPECS, (yyvsp[0].node), NULL); }
#line 3483 "c99.y.gen.c"
    break;

  case 185: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 511 "c99.y"
                                                                        { (yyval.node) = prependAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3489 "c99.y.gen.c"
    break;

  case 186: /* parameter_type_list: parameter_list ',' ELLIPSIS  */
#line 515 "c99.y"
                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), makeAstTerm(AST_DECLARATION_PARAM_ELLIPSIS, (yyvsp[0].text))); }
#line 3495 "c99.y.gen.c"
    break;

  case 187: /* parameter_type_list: parameter_list  */
#line 516 "c99.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3501 "c99.y.gen.c"
    break;

  case 188: /* parameter_list: parameter_declaration  */
#line 520 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 3507 "c99.y.gen.c"
    break;

  case 189: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 521 "c99.y"
                                                                        { (yyval.node) = appendAstChild((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3513 "c99.y.gen.c"
    break;

  case 190: /* parameter_declaration: declaration_specifiers declarator  */
#line 525 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_DECLARATION_PARAM_ENTRY, (yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 3519 "c99.y.gen.c"
    break;

  case 191: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 526 "c99.y"
                                                                { (yyval.node) = makeAstNode(AST_DECLARATION_PARAM_ENTRY, (yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 3525 "c99.y.gen.c"
    break;

  case 192: /* parameter_declaration: declaration_specifiers  */
#line 527 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_PARAM_ENTRY, (yyvsp[0].node), NULL); }
#line 3531 "c99.y.gen.c"
    break;

  case 193: /* identifier_list: IDENTIFIER  */
#line 531 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_LIST, makeAstTerm(AST_ID, (yyvsp[0].text)), NULL); }
#line 3537 "c99.y.gen.c"
    break;

  case 194: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 532 "c99.y"
                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), makeAstTerm(AST_ID, (yyvsp[0].text))); }
#line 3543 "c99.y.gen.c"
    break;

  case 197: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 541 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 3549 "c99.y.gen.c"
    break;

  case 198: /* abstract_declarator: pointer  */
#line 542 "c99.y"
                                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3555 "c99.y.gen.c"
    break;

  case 199: /* abstract_declarator: direct_abstract_declarator  */
#line 543 "c99.y"
                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3561 "c99.y.gen.c"
    break;

  case 200: /* direct_abstract_declarator: '(' abstract_declarator ')'  */
#line 547 "c99.y"
                                                                                                                                                        { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[-1].node), NULL); }
#line 3567 "c99.y.gen.c"
    break;

  case 201: /* direct_abstract_declarator: '[' ']'  */
#line 548 "c99.y"
                                                                                                                                                                                { (yyval.node) = makeAstNode(AST_LIST, makeAstTerm(AST_DECLARATION_ARRAY_SPEC, NULL), NULL); }
#line 3573 "c99.y.gen.c"
    break;

  case 202: /* direct_abstract_declarator: '[' '*' ']'  */
#line 549 "c99.y"
                                                                                                                                                                        { (yyval.node) = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "1"), NULL); }
#line 3579 "c99.y.gen.c"
    break;

  case 203: /* direct_abstract_declarator: '[' STATIC type_qualifier_list assignment_expression ']'  */
#line 550 "c99.y"
                                                                                                                                { (yyval.node) = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "2"), (yyvsp[-2].node), (yyvsp[-1].node), NULL); }
#line 3585 "c99.y.gen.c"
    break;

  case 204: /* direct_abstract_declarator: '[' STATIC assignment_expression ']'  */
#line 551 "c99.y"
                                                                                                                                                { (yyval.node) = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "3"), (yyvsp[-1].node), NULL); }
#line 3591 "c99.y.gen.c"
    break;

  case 205: /* direct_abstract_declarator: '[' type_qualifier_list STATIC assignment_expression ']'  */
#line 552 "c99.y"
                                                                                                                                { (yyval.node) = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "4"), (yyvsp[-3].node), (yyvsp[-1].node), NULL); }
#line 3597 "c99.y.gen.c"
    break;

  case 206: /* direct_abstract_declarator: '[' type_qualifier_list assignment_expression ']'  */
#line 553 "c99.y"
                                                                                                                                        { (yyval.node) = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "5"), (yyvsp[-2].node), (yyvsp[-1].node), NULL); }
#line 3603 "c99.y.gen.c"
    break;

  case 207: /* direct_abstract_declarator: '[' type_qualifier_list ']'  */
#line 554 "c99.y"
                                                                                                                                                        { (yyval.node) = makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "6"), (yyvsp[-1].node), NULL); }
#line 3609 "c99.y.gen.c"
    break;

  case 208: /* direct_abstract_declarator: '[' assignment_expression ']'  */
#line 555 "c99.y"
                                                                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_ARRAY_SPEC, (yyvsp[-1].node), NULL); }
#line 3615 "c99.y.gen.c"
    break;

  case 209: /* direct_abstract_declarator: direct_abstract_declarator '[' ']'  */
#line 556 "c99.y"
                                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), makeAstTerm(AST_DECLARATION_ARRAY_SPEC, NULL)); }
#line 3621 "c99.y.gen.c"
    break;

  case 210: /* direct_abstract_declarator: direct_abstract_declarator '[' '*' ']'  */
#line 557 "c99.y"
                                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstTerm(AST_DECLARATION_ARRAY_SPEC, NULL)); }
#line 3627 "c99.y.gen.c"
    break;

  case 211: /* direct_abstract_declarator: direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'  */
#line 558 "c99.y"
                                                                                                { (yyval.node) = appendAstChild((yyvsp[-5].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "8"), (yyvsp[-2].node), (yyvsp[-1].node), NULL)); }
#line 3633 "c99.y.gen.c"
    break;

  case 212: /* direct_abstract_declarator: direct_abstract_declarator '[' STATIC assignment_expression ']'  */
#line 559 "c99.y"
                                                                                                                        { (yyval.node) = appendAstChild((yyvsp[-4].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "9"), (yyvsp[-1].node), NULL)); }
#line 3639 "c99.y.gen.c"
    break;

  case 213: /* direct_abstract_declarator: direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'  */
#line 560 "c99.y"
                                                                                                        { (yyval.node) = appendAstChild((yyvsp[-4].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "10"), (yyvsp[-2].node), (yyvsp[-1].node), NULL)); }
#line 3645 "c99.y.gen.c"
    break;

  case 214: /* direct_abstract_declarator: direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'  */
#line 561 "c99.y"
                                                                                                { (yyval.node) = appendAstChild((yyvsp[-5].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "11"), (yyvsp[-3].node), (yyvsp[-1].node), NULL)); }
#line 3651 "c99.y.gen.c"
    break;

  case 215: /* direct_abstract_declarator: direct_abstract_declarator '[' type_qualifier_list ']'  */
#line 562 "c99.y"
                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_TODO, makeAstTerm(AST_TODO, "12"), (yyvsp[-1].node), NULL)); }
#line 3657 "c99.y.gen.c"
    break;

  case 216: /* direct_abstract_declarator: direct_abstract_declarator '[' assignment_expression ']'  */
#line 563 "c99.y"
                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_DECLARATION_ARRAY_SPEC, (yyvsp[-1].node), NULL)); }
#line 3663 "c99.y.gen.c"
    break;

  case 217: /* direct_abstract_declarator: '(' ')'  */
#line 564 "c99.y"
                                                                                                                                                                                { (yyval.node) = makeAstNode(AST_DECLARATION_PARAMS_SPEC, makeAstNode(AST_LIST, NULL), NULL); }
#line 3669 "c99.y.gen.c"
    break;

  case 218: /* direct_abstract_declarator: '(' parameter_type_list ')'  */
#line 565 "c99.y"
                                                                                                                                                        { (yyval.node) = makeAstNode(AST_DECLARATION_PARAMS_SPEC, (yyvsp[-1].node), NULL); }
#line 3675 "c99.y.gen.c"
    break;

  case 219: /* direct_abstract_declarator: direct_abstract_declarator '(' ')'  */
#line 566 "c99.y"
                                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-2].node), makeAstNode(AST_DECLARATION_PARAMS_SPEC, makeAstNode(AST_LIST, NULL), NULL)); }
#line 3681 "c99.y.gen.c"
    break;

  case 220: /* direct_abstract_declarator: direct_abstract_declarator '(' parameter_type_list ')'  */
#line 567 "c99.y"
                                                                                                                                { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_DECLARATION_PARAMS_SPEC, (yyvsp[-1].node), NULL)); }
#line 3687 "c99.y.gen.c"
    break;

  case 221: /* initializer: '{' initializer_list '}'  */
#line 571 "c99.y"
                                                                                                        { (yyval.node) = makeAstNode(AST_EXPR_INIT, (yyvsp[-1].node), NULL); }
#line 3693 "c99.y.gen.c"
    break;

  case 222: /* initializer: '{' initializer_list ',' '}'  */
#line 572 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_EXPR_INIT, (yyvsp[-2].node), NULL); }
#line 3699 "c99.y.gen.c"
    break;

  case 223: /* initializer: assignment_expression  */
#line 573 "c99.y"
                                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3705 "c99.y.gen.c"
    break;

  case 224: /* initializer_list: designation initializer  */
#line 577 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_LIST, makeAstNode(AST_EXPR_INIT_MEMBER, (yyvsp[-1].node), (yyvsp[0].node), NULL), NULL); }
#line 3711 "c99.y.gen.c"
    break;

  case 225: /* initializer_list: initializer  */
#line 578 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_LIST, makeAstNode(AST_EXPR_INIT_MEMBER, (yyvsp[0].node), NULL), NULL); }
#line 3717 "c99.y.gen.c"
    break;

  case 226: /* initializer_list: initializer_list ',' designation initializer  */
#line 579 "c99.y"
                                                        { (yyval.node) = appendAstChild((yyvsp[-3].node), makeAstNode(AST_EXPR_INIT_MEMBER, (yyvsp[-1].node), (yyvsp[0].node), NULL)); }
#line 3723 "c99.y.gen.c"
    break;

  case 227: /* initializer_list: initializer_list ',' initializer  */
#line 580 "c99.y"
                                                                        { (yyval.node) = appendAstChild((yyvsp[-2].node), makeAstNode(AST_EXPR_INIT_MEMBER, (yyvsp[0].node), NULL)); }
#line 3729 "c99.y.gen.c"
    break;

  case 228: /* designation: designator_list '='  */
#line 584 "c99.y"
                                                                                { (yyval.node) = (yyvsp[-1].node); }
#line 3735 "c99.y.gen.c"
    break;

  case 229: /* designator_list: designator  */
#line 588 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_EXPR_INIT_MEMBER_TARGET, (yyvsp[0].node), NULL); }
#line 3741 "c99.y.gen.c"
    break;

  case 230: /* designator_list: designator_list designator  */
#line 589 "c99.y"
                                                                        { (yyval.node) = appendAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3747 "c99.y.gen.c"
    break;

  case 231: /* designator: '[' constant_expression ']'  */
#line 593 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_EXPR_INIT_MEMBER_TARGET_INDEX, (yyvsp[-1].node), NULL); }
#line 3753 "c99.y.gen.c"
    break;

  case 232: /* designator: '.' IDENTIFIER  */
#line 594 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_EXPR_INIT_MEMBER_TARGET_FIELD, (yyvsp[0].text)); }
#line 3759 "c99.y.gen.c"
    break;

  case 233: /* static_assert_declaration: STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'  */
#line 598 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_STATIC_ASSERT, (yyvsp[-4].node), makeAstTerm(AST_LITERAL_STRING, (yyvsp[-2].text)), NULL); }
#line 3765 "c99.y.gen.c"
    break;

  case 234: /* statement: labeled_statement  */
#line 602 "c99.y"
                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3771 "c99.y.gen.c"
    break;

  case 235: /* statement: compound_statement  */
#line 603 "c99.y"
                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3777 "c99.y.gen.c"
    break;

  case 236: /* statement: expression_statement  */
#line 604 "c99.y"
                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3783 "c99.y.gen.c"
    break;

  case 237: /* statement: selection_statement  */
#line 605 "c99.y"
                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3789 "c99.y.gen.c"
    break;

  case 238: /* statement: iteration_statement  */
#line 606 "c99.y"
                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3795 "c99.y.gen.c"
    break;

  case 239: /* statement: jump_statement  */
#line 607 "c99.y"
                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3801 "c99.y.gen.c"
    break;

  case 240: /* statement: error ';'  */
#line 608 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_STMT_ERROR, NULL); }
#line 3807 "c99.y.gen.c"
    break;

  case 241: /* labeled_statement: IDENTIFIER ':' statement  */
#line 612 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_STMT_LABELED, makeAstTerm(AST_ID, (yyvsp[-2].text)), (yyvsp[0].node), NULL); }
#line 3813 "c99.y.gen.c"
    break;

  case 242: /* labeled_statement: CASE constant_expression ':' statement  */
#line 613 "c99.y"
                                                        { (yyval.node) = makeAstNode(AST_STMT_LABELED, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3819 "c99.y.gen.c"
    break;

  case 243: /* labeled_statement: DEFAULT ':' statement  */
#line 614 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_STMT_LABELED, makeAstTerm(AST_ID, (yyvsp[-2].text)), (yyvsp[0].node), NULL); }
#line 3825 "c99.y.gen.c"
    break;

  case 244: /* compound_statement: '{' '}'  */
#line 618 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_STMT_BLOCK, NULL); }
#line 3831 "c99.y.gen.c"
    break;

  case 245: /* compound_statement: '{' block_item_list '}'  */
#line 619 "c99.y"
                                                                        { (yyval.node) = (yyvsp[-1].node); }
#line 3837 "c99.y.gen.c"
    break;

  case 246: /* block_item_list: block_item  */
#line 623 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_STMT_BLOCK, (yyvsp[0].node), NULL); }
#line 3843 "c99.y.gen.c"
    break;

  case 247: /* block_item_list: block_item_list block_item  */
#line 624 "c99.y"
                                                                { (yyval.node) = appendAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3849 "c99.y.gen.c"
    break;

  case 248: /* block_item: declaration  */
#line 628 "c99.y"
                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3855 "c99.y.gen.c"
    break;

  case 249: /* block_item: statement  */
#line 629 "c99.y"
                                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3861 "c99.y.gen.c"
    break;

  case 250: /* expression_statement: ';'  */
#line 633 "c99.y"
                                                                                        { (yyval.node) = makeAstNode(AST_STMT_EMPTY, NULL); }
#line 3867 "c99.y.gen.c"
    break;

  case 251: /* expression_statement: expression ';'  */
#line 634 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_STMT_EXPR, (yyvsp[-1].node), NULL); }
#line 3873 "c99.y.gen.c"
    break;

  case 252: /* selection_statement: IF '(' expression ')' statement  */
#line 638 "c99.y"
                                                                      { (yyval.node) = makeAstNode(AST_STMT_IF, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3879 "c99.y.gen.c"
    break;

  case 253: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 639 "c99.y"
                                                                                  { (yyval.node) = makeAstNode(AST_STMT_IF, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3885 "c99.y.gen.c"
    break;

  case 254: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 640 "c99.y"
                                                                                          { (yyval.node) = makeAstNode(AST_STMT_SWITCH, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3891 "c99.y.gen.c"
    break;

  case 255: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 644 "c99.y"
                                                                                                                        { (yyval.node) = makeAstNode(AST_STMT_WHILE, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3897 "c99.y.gen.c"
    break;

  case 256: /* iteration_statement: DO statement WHILE '(' expression ')' ';'  */
#line 645 "c99.y"
                                                                                                                        { (yyval.node) = makeAstNode(AST_STMT_DO, (yyvsp[-5].node), (yyvsp[-2].node), NULL); }
#line 3903 "c99.y.gen.c"
    break;

  case 257: /* iteration_statement: FOR '(' expression_statement expression_statement ')' statement  */
#line 646 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_STMT_FOR, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3909 "c99.y.gen.c"
    break;

  case 258: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 647 "c99.y"
                                                                                    { (yyval.node) = makeAstNode(AST_STMT_FOR, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3915 "c99.y.gen.c"
    break;

  case 259: /* iteration_statement: FOR '(' declaration expression_statement ')' statement  */
#line 648 "c99.y"
                                                                                                        { (yyval.node) = makeAstNode(AST_STMT_FOR, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3921 "c99.y.gen.c"
    break;

  case 260: /* iteration_statement: FOR '(' declaration expression_statement expression ')' statement  */
#line 649 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_STMT_FOR, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 3927 "c99.y.gen.c"
    break;

  case 261: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 653 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_STMT_GOTO, makeAstTerm(AST_ID, (yyvsp[-1].text)), NULL); }
#line 3933 "c99.y.gen.c"
    break;

  case 262: /* jump_statement: CONTINUE ';'  */
#line 654 "c99.y"
                                                                                { (yyval.node) = makeAstTerm(AST_STMT_CONTINUE, NULL); }
#line 3939 "c99.y.gen.c"
    break;

  case 263: /* jump_statement: BREAK ';'  */
#line 655 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_STMT_BREAK, NULL); }
#line 3945 "c99.y.gen.c"
    break;

  case 264: /* jump_statement: RETURN ';'  */
#line 656 "c99.y"
                                                                                { (yyval.node) = makeAstTerm(AST_STMT_RETURN, NULL); }
#line 3951 "c99.y.gen.c"
    break;

  case 265: /* jump_statement: RETURN expression ';'  */
#line 657 "c99.y"
                                                                        { (yyval.node) = makeAstNode(AST_STMT_RETURN, (yyvsp[-1].node), NULL); }
#line 3957 "c99.y.gen.c"
    break;

  case 266: /* translation_unit: external_declaration  */
#line 661 "c99.y"
                                                                        { (yyval.node) = ast = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 3963 "c99.y.gen.c"
    break;

  case 267: /* translation_unit: translation_unit external_declaration  */
#line 662 "c99.y"
                                                        { (yyval.node) = ast = appendAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 3969 "c99.y.gen.c"
    break;

  case 268: /* external_declaration: function_definition  */
#line 666 "c99.y"
                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 3975 "c99.y.gen.c"
    break;

  case 269: /* external_declaration: declaration  */
#line 667 "c99.y"
                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 3981 "c99.y.gen.c"
    break;

  case 270: /* external_declaration: error ';'  */
#line 668 "c99.y"
                                                                                        { (yyval.node) = makeAstTerm(AST_STMT_ERROR, NULL); }
#line 3987 "c99.y.gen.c"
    break;

  case 271: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 672 "c99.y"
                                                                                { (yyval.node) = makeAstNode(AST_DEF_FUNCTION_IMPL, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 3993 "c99.y.gen.c"
    break;

  case 272: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 673 "c99.y"
                                                                                                { (yyval.node) = makeAstNode(AST_DEF_FUNCTION_IMPL, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), NULL); }
#line 3999 "c99.y.gen.c"
    break;

  case 273: /* declaration_list: declaration  */
#line 677 "c99.y"
                                                                { (yyval.node) = makeAstNode(AST_LIST, (yyvsp[0].node), NULL); }
#line 4005 "c99.y.gen.c"
    break;

  case 274: /* declaration_list: declaration_list declaration  */
#line 678 "c99.y"
                                                { (yyval.node) = appendAstChild((yyvsp[-1].node), (yyvsp[0].node)); }
#line 4011 "c99.y.gen.c"
    break;


#line 4015 "c99.y.gen.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 681 "c99.y"

