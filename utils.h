#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "map.h"

// A set of macro-definitions for a nice command-line arguments parsing

#if 1 // region OPT_OPTIONS(...) {

#define CONCAT(a,b) a##b

#define OPT_EXPAND_SHORT_SPEC_IMPL(name, fullKey, argsSpec, shortKey, spec, helpMsg)     spec
#define OPT_EXPAND_FULL_SPEC_IMPL(name, fullKey, argsSpec, shortKey, spec, helpMsg)      {fullKey, argsSpec, 0, shortKey[0]},

#define OPT_EXPAND_ARGS_STRUCT_TYPE_0   bool
#define OPT_EXPAND_ARGS_STRUCT_TYPE_1   char*
#define OPT_EXPAND_ARGS_STRUCT_IMPL(name, fullKey, argsSpec, shortKey, spec, helpMsg)    CONCAT(OPT_EXPAND_ARGS_STRUCT_TYPE_, argsSpec) name;

#define OPT_EXPAND_ARGS_HELP_IMPL_0(name, fullKey, shortKey)   "-" shortKey "\n" "--" fullKey "\t\t\t"
#define OPT_EXPAND_ARGS_HELP_IMPL_1(name, fullKey, shortKey)   "-" shortKey "<" #name ">\n" "--" fullKey "<" #name ">" "\t\t"
#define OPT_EXPAND_ARGS_HELP_IMPL(name, fullKey, argsSpec, shortKey, spec, helpMsg)    CONCAT(OPT_EXPAND_ARGS_HELP_IMPL_, argsSpec)(name, fullKey, shortKey) helpMsg "\n"

#define OPT_EXPAND_DEFAULTS_IMPL_0(name)   args->name = false;
#define OPT_EXPAND_DEFAULTS_IMPL_1(name)   args->name = NULL;
#define OPT_EXPAND_DEFAULTS_IMPL(name, fullKey, argsSpec, shortKey, spec, helpMsg)  CONCAT(OPT_EXPAND_DEFAULTS_IMPL_, argsSpec)(name)

#define OPT_EXPAND_PARSE_IMPL_0(name)   args->name = true;
#define OPT_EXPAND_PARSE_IMPL_1(name)   args->name = optarg;
#define OPT_EXPAND_PARSE_IMPL(name, fullKey, argsSpec, shortKey, spec, helpMsg)  else if (optionKey == shortKey[0]) CONCAT(OPT_EXPAND_PARSE_IMPL_, argsSpec)(name)

#define OPT_EXPAND_SHORT_SPEC(x)    OPT_EXPAND_SHORT_SPEC_IMPL x
#define OPT_EXPAND_FULL_SPEC(x)     OPT_EXPAND_FULL_SPEC_IMPL x
#define OPT_EXPAND_ARGS_STRUCT(x)   OPT_EXPAND_ARGS_STRUCT_IMPL x
#define OPT_EXPAND_ARGS_HELP(x)   OPT_EXPAND_ARGS_HELP_IMPL x
#define OPT_EXPAND_DEFAULTS(x)   OPT_EXPAND_DEFAULTS_IMPL x
#define OPT_EXPAND_PARSE(x)   OPT_EXPAND_PARSE_IMPL x

/*
OPT_OPTIONS(
    parseCmdLineArgs, CmdLineArgs,
    OPT_PARAMETER(paramA, "paramA", "a"),
    OPT_PARAMETER(paramB, "paramB", "b"),
    OPT_FLAG(optC, "optC", "c"),
    OPT_FLAG(optD, "optD", "d")
)
*/
#define OPT_OPTIONS(parseFuncName, argsType, ...)   \
                                                    \
    static const char* CONCAT(parseFuncName,_shortSpec) = MAP(OPT_EXPAND_SHORT_SPEC, __VA_ARGS__);     \
                                                                                        \
    static struct option CONCAT(parseFuncName,_fullSpec)[] = {                          \
    MAP(OPT_EXPAND_FULL_SPEC, __VA_ARGS__)                                              \
        {0, 0, 0, 0}                                                                    \
    };                                                                                  \
                                                                                        \
    typedef struct argsType {                                                           \
        MAP(OPT_EXPAND_ARGS_STRUCT, __VA_ARGS__)                                        \
        char** rest;                                                                    \
        int restCount;                                                                  \
    } argsType;                                                                         \
                                                                                        \
    static void CONCAT(printHelpFor, argsType)(int argc, char** argv, char* restName)   \
    {                                                                                   \
        UNUSED(argc);                                                                   \
        printf("Usage: %s [options] %s\n", argv[0], restName);                          \
        printf(MAP(OPT_EXPAND_ARGS_HELP, __VA_ARGS__));                                 \
    }                                                                                   \
                                                                                        \
    static bool parseFuncName(int argc, char** argv, argsType* args)                    \
    {                                                                                   \
        int optionKey = 0;                                                              \
        int optionIndex = 0;                                                            \
        MAP(OPT_EXPAND_DEFAULTS, __VA_ARGS__)                                           \
        optionKey = getopt_long(argc, argv, CONCAT(parseFuncName,_shortSpec), CONCAT(parseFuncName,_fullSpec), &optionIndex);     \
        while (optionKey > 0)                                                           \
        {                                                                               \
            if (optionKey == '?') return false;                                         \
            MAP(OPT_EXPAND_PARSE, __VA_ARGS__)                                          \
            else return false;                                                          \
            optionKey = getopt_long(argc, argv, CONCAT(parseFuncName,_shortSpec), CONCAT(parseFuncName,_fullSpec), &optionIndex); \
        }                                                                               \
        args->rest = optind < argc ? &argv[optind] : NULL;                              \
        args->restCount = argc - optind;                                                \
        return true;                                                                    \
    }

#define OPT_OPTION_ENTRY(name, fullKey, argsSpec, shortKey, spec, helpMsg)     (name, fullKey, argsSpec, shortKey, spec, helpMsg)

#define OPT_PARAMETER(name, fullKey, shortKey, helpMsg)     OPT_OPTION_ENTRY(name, fullKey, required_argument, shortKey, shortKey ":", helpMsg)
#define OPT_FLAG(name, fullKey, shortKey, helpMsg)          OPT_OPTION_ENTRY(name, fullKey, no_argument, shortKey, shortKey, helpMsg)

#endif // } region OPT_OPTIONS(...)


// A number of macro-definitions for type-check-friendly memory manupulations

#define allocStruct(t) ((t*)malloc(sizeof(t)))
#define allocArray(t, n) ((t*)malloc(sizeof(t) * (n)))
#define clearStructure(s) (memset(s, 0, sizeof(*s)))

#define copyArray(from, to, count) (memcpy(to, from, sizeof(*from) * (count)))

// Some minor helpful definitions

#define exitWithMessage(msg) { fprintf(stderr, "\n%s\n", msg); exit(1); }

//long min(long a, long b);
//long max(long a, long b);

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#ifndef NULL
#define NULL 0
#endif

#define UNUSED(x) ((void)&x)

//typedef int bool;
//
//#define true (0==0)
//#define false (0!=0)

typedef void (*action)(void* arg);
typedef void (*action2)(void* arg, void* arg2);
typedef void (*action3)(void* arg, void* arg2, void* arg3);
typedef void (*action4)(void* arg, void* arg2, void* arg3, void* arg4);

typedef void* (*func1)(void* arg);
typedef void* (*func2)(void* arg, void* arg2);
typedef void* (*func3)(void* arg, void* arg2, void* arg3);
typedef void* (*func4)(void* arg, void* arg2, void* arg3, void* arg4);

typedef bool (*boolFunc1)(void* arg);
typedef bool (*boolFunc2)(void* arg, void* arg2);
typedef bool (*boolFunc3)(void* arg, void* arg2, void* arg3);

typedef int (*intFunc1)(void* arg);
typedef int (*intFunc2)(void* arg, void* arg2);
typedef int (*intFunc3)(void* arg, void* arg2, void* arg3);

// An attempt to implement the generalized tree traversing aglorithm to get rid of complicated recursion and loops everywhere

typedef struct {
    void* state;
    int iterStateSize;
    action3 onEnterNode;
    action3 onExitNode;
    func4 takeFirstChild;
    func4 takeNextChild;
} traverseTreeParams;


void traverseTree(void* root, traverseTreeParams* params);

/// <summary>
/// Write the correctly xml-escaped data string to the output file
/// </summary>
void writeXmlEscapedDataString(FILE* out, char* str, int length);

/// <summary>
/// Round the given size up to the given alignment requirement
/// </summary>
int alignSize(int size, int alignment);

#endif

// A set of macro-definitions for a nice enums definition supporting the string representation for each value being introduced

#if 1 // region BEGIN_ENUM(..)...END_ENUM(..) {

#undef DECL_ENUM_ELEMENT
#undef DECL_ENUM_ELEMENT_VAL
#undef DECL_ENUM_ELEMENT_STR
#undef DECL_ENUM_ELEMENT_VAL_STR
#undef BEGIN_ENUM
#undef END_ENUM

#ifndef GENERATE_ENUM_STRINGS
#define DECL_ENUM_ELEMENT( element ) element,
#define DECL_ENUM_ELEMENT_VAL( element, value ) element = value,
#define DECL_ENUM_ELEMENT_STR( element, descr ) DECL_ENUM_ELEMENT( element )
#define DECL_ENUM_ELEMENT_VAL_STR( element, value, descr ) DECL_ENUM_ELEMENT_VAL( element, value )
#define BEGIN_ENUM( ENUM_NAME ) typedef enum tag##ENUM_NAME
#define END_ENUM( ENUM_NAME ) ENUM_NAME; \
            const char* getString##ENUM_NAME(enum tag##ENUM_NAME index);
#else
#define BEGIN_ENUM( ENUM_NAME) const char * getString##ENUM_NAME( enum tag##ENUM_NAME index ) {\
        switch( index ) { 
#define DECL_ENUM_ELEMENT( element ) case element: return #element; break;
#define DECL_ENUM_ELEMENT_VAL( element, value ) DECL_ENUM_ELEMENT( element )
#define DECL_ENUM_ELEMENT_STR( element, descr ) case element: return descr; break;
#define DECL_ENUM_ELEMENT_VAL_STR( element, value, descr ) DECL_ENUM_ELEMENT_STR( element, descr )

#define END_ENUM( ENUM_NAME ) default: return "Unknown value"; } }

#endif

#endif // } region OPT_OPTIONS(...)
