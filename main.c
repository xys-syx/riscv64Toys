#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

#include "ast.h"
#include "model.h"
#include "code.h"
#include "c99.y.gen.h"
#include "c99.l.gen.h"
#include "utils.h"
#include "collections.h"

OPT_OPTIONS(
	parseCmdLineArgs, CmdLineArgs,
	OPT_FLAG(version, "version", "v", "print version info"),
	OPT_FLAG(forceOk, "force", "f", "force the result code to zero no matter if some errors were detected"),
	OPT_PARAMETER(output, "output", "o", "output file name"),
	OPT_PARAMETER(astXmlName, "print-ast", "s", "write AST representation to the file"),
	OPT_PARAMETER(cfgDgmlName, "print-cfg", "c", "write CFG representation to the file"),
	OPT_PARAMETER(cleanCfgDgmlName, "print-clean-cfg", "a", "write CFG after analysis representation to the file")
)

ProgramUnit* model; // shared with error reporting, see ast.c

AstNode* ast = NULL; // shared with parser, see c99.y

static void traceArgs(CmdLineArgs* args)
{
	printf("ast: %s\n", args->astXmlName ? args->astXmlName : "NULL");
	printf("cfg: %s\n", args->cfgDgmlName ? args->cfgDgmlName : "NULL");
	printf("ccfg: %s\n", args->cleanCfgDgmlName ? args->cleanCfgDgmlName : "NULL");
	printf("output: %s\n", args->output ? args->output : "NULL");
	printf("version: %s\n", args->version ? "+" : "-");
	printf("rest[%d]: {\n", args->restCount);
	for (int i = 0; i < args->restCount; i++)
	{
		printf("  %s\n", args->rest[i]);
	}
	printf("}\n");
}

static int getFileSize(char* fname)
{
	// https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
	struct stat st;
	int rc = stat(fname, &st);
	return rc == 0 && S_ISREG(st.st_mode) ? (int)st.st_size : -1;
}

static FILE* openOutFile(char* fname)
{
	struct stat st;
	int rc = stat(fname, &st);
	FILE* fp = fopen(fname, "wb");

	if (rc == 0 && S_ISREG(st.st_mode) && st.st_size > 0)
	{
		if (ftruncate(fileno(fp), 0) != 0)
		{
			// TODO error handling
		}
	}

	return fp;
}

static int lastIndexOfChar(char* str, char ch)
{
	int i = 0;
	int result = -1;

	char sc = str[i];
	while (sc != 0)
	{
		if (sc == ch)
		{
			result = i;
		}

		sc = str[++i];
	}

	return result;
}

static char* makeDgmlName(char* specified, char* funcName)
{
	int slen = strlen(specified);
	int nlen = strlen(funcName);
	int resultLen = slen + nlen + 6;
	char* result = allocArray(char, resultLen + 1);
	
	int extPos = lastIndexOfChar(specified, '/');
	if (extPos < 0)
		extPos = 0;

	char sc = specified[extPos];
	while (sc != 0 && sc != '.')
		sc = specified[++extPos];

	memcpy(&result[0], &specified[0], extPos);
	result[extPos] = '.';
	memcpy(&result[extPos + 1], funcName, nlen);

	if (sc == 0) // no extension specified
	{
		extPos += nlen + 1;
		memcpy(&result[extPos], ".dgml", 5);
		result[extPos + 5] = 0;
	}
	else // extension starts at extPos
	{
		int nameEnd = extPos + nlen + 1;
		int extLen = slen - extPos;
		memcpy(&result[nameEnd], &specified[extPos], extLen);
		result[nameEnd + extLen] = 0;
	}
	
	return result;
}

static void traceFunctionCfg(Function* func, char* specifiedDgmlName)
{
	char* funcDgmlName = makeDgmlName(specifiedDgmlName, func->name);
	FILE* cfgFile = openOutFile(funcDgmlName);
	if (cfgFile != NULL)
	{
		traceControlFlowGraph(func->body, cfgFile); // , rawInputBuffer);
		fclose(cfgFile);
	}
	else
	{
		printError(NULL, "Failed to open CFG output file %s", funcDgmlName);
	}
	free(funcDgmlName);
}

static int doWork(CmdLineArgs* args) 
{
	char* sourceFileName = args->rest[0];
	model = createModule(sourceFileName);

	yylloc.first_column = 0;
	yylloc.first_line = 0;
	yylloc.last_column = 0;
	yylloc.last_line = 0;

	int rawInputLength = (int)getFileSize(sourceFileName);
	char* rawInputBuffer = allocArray(char, rawInputLength + 1);

	FILE *inputFile = fopen(sourceFileName, "rb");
	if (inputFile != NULL)
	{
		fread(rawInputBuffer, rawInputLength, 1, inputFile);
		fclose(inputFile);
	}
	else
	{
		printError(NULL, "Failed to open input file %s", sourceFileName);
	}

	rawInputBuffer[rawInputLength] = 0;

	// explicitly tell the lexer to read the text from the in-memory buffer
	yy_scan_bytes(rawInputBuffer, rawInputLength);

	// yyset_debug(1);
	// yydebug = 1;
	// 
	//YYSTYPE tt;
	//YYLTYPE ll;
	//int x;
	//while ((x = yylex(&tt, &ll)) > 0) printf("%d\n", x);
	//return 0;
	
	int result = yyparse();
	if (ast != NULL)
	{
		if (args->astXmlName != NULL)
		{
			FILE* astFile = openOutFile(args->astXmlName);
			if (astFile != NULL)
			{
				//traceAst(ast, astFile);
				traceAstRecursively(ast, astFile);
				fclose(astFile);
			}
			else 
			{
				printError(NULL, "Failed to open AST output file %s", args->astXmlName);
			}
		}

		collectSource(model, ast);

		if (args->cfgDgmlName != NULL)
		{
			traverseLinkedList(model->functionDefinitions, (action2)traceFunctionCfg, args->cfgDgmlName);
		}

		performAnalysis(model);

		if (args->cleanCfgDgmlName != NULL)
		{
			traverseLinkedList(model->functionDefinitions, (action2)traceFunctionCfg, args->cleanCfgDgmlName);
		}

		// traceAllTypes();

		if (args->output != NULL && (model->errorsCount == 0 || args->forceOk))
		{
			FILE* outFile = openOutFile(args->output);
			if (outFile != NULL)
			{
				Module* compiled = generate(model);
				serialize(compiled, outFile);

				fclose(outFile);
			}
			else 
			{
				printError(NULL, "Failed to open output file %s", args->output);
			}
		}

		// cleanupCfg(cfg);
		// cleanupAst(ast);
	}
	else 
	{
		printf("parse result = %d\n", result);
		printf("wtf\n");
	}

	return (model->errorsCount == 0 || args->forceOk) ? 0 : -1;
}


int main(int argc, char** argv)
{
	CmdLineArgs args;
	if (parseCmdLineArgs(argc, argv, &args))
	{
		if (args.restCount > 0)
		{
			return doWork(&args);
		}
		else
		{
			fprintf(stderr, "\nInput file not specified!\n");
			printHelpForCmdLineArgs(argc, argv, "inputFileName");
			return -1;
		}
	}
	else
	{
		printHelpForCmdLineArgs(argc, argv, "inputFileName");
		// traceArgs(&args);
		return -1;
	}
}

