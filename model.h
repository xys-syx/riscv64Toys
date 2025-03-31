#pragma once

#include "collections.h"

#include "types.h"
#include "cfg.h"

/**
 * The complete semantic model of a program translation unit consists of a following things:
 *  - global variables
 *  - type declarations for each of hierarchycally-organized lexical scopes
 *  - named function declarations having corresponding signatures
 *  - named function definitions  having corresponding signatures, and for each implemented definition
 *		- control-flow graph with its own hierarchycally-organized lexical scopes for both declarations and variables
 *
 * * * * * * * * * * * * * * * * * * * * * */


/// <summary>
/// A semantic model for a function declaration or definition
/// </summary>
typedef struct Function {
	/// A numberical identifier
	int id;
	/// The name of the function
	char* name;
	/// Visibility information about the function
	bool isPublic, isExternal;
	/// The corresponding function type
	TypeInfo* type;
	/// The signature of the function
	FunctionSignature* signature;
	/// The complete control-flow graph of the function body statement (NULL for declaration)
	CfgInstance* body;
	/// The evaluation-stack depth required to evaluate any expression-tree in this function
	int maxStackDepth;
	/// The reference to the syntax node describing this declaration (NULL for definition)
	AstNode* declAst;
	/// The reference to the syntax node describing this definition (NULL for declaration)
	AstNode* implAst;
} Function;

/// <summary>
/// A semantic model for a whole program translation unit
/// </summary>
typedef struct ProgramUnit {
	/// The name of the initial source file
	char* sourceFileName;
	/// All the top-level type declarations
	Declarations* types;
	/// All the top-level global variables 
	ValuePlacesMap* globalVars;
	/// A list of all the top-level function declarations
	LinkedList* functionDeclarations;
	/// A map of all the top-level function declarations by name
	RbTree* functionDeclarationsByName;
	/// A list of all the top-level function definitions
	LinkedList* functionDefinitions;
	/// A map of all the top-level function defnitions by name
	RbTree* functionDefinitionsByName;
	/// The total amount of errors reported during program analysis and compilation
	int errorsCount;
} ProgramUnit;


/// <summary>
/// Create a new semantic model for a program
/// </summary>
ProgramUnit* createModule(char* sourceFileName);

/// <summary>
/// Collect the declarations info from the given AST augmenting the program context and resolving the known types
/// </summary>
/// <param name="model">The model of program to introduce function declaration to</param>
/// <param name="decls">The declarations scope to introduce type declarations to</param>
/// <param name="vars">The variables collection to introduce variable value-place definition to</param>
/// <param name="scope">The lexical scope to associate value-place with</param>
/// <param name="ast"></param>
/// <returns></returns>
LinkedList* collectDeclaration(ProgramUnit* model, Declarations* decls, ValuePlacesMap* vars, ValuePlacesMap* scope, AstNode* ast);

/// <summary>
/// Augment the translation unit model by collecting the information from a given AST
/// </summary>
void collectSource(ProgramUnit* model, AstNode* ast);

/// <summary>
/// Analyse and refine the given translation unit model
/// </summary>
/// <param name="model"></param>
void performAnalysis(ProgramUnit* model);

