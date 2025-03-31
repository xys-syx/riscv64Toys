#include "utils.h"
#include "ast.h"

/**
 * Object module is the result of program translation unit compilation. 
 * The object module described as:
 *	- a number of uniquely-named symbols for each global variable or function
 *	- a number of uniquely-named labels in a .text section for control-flow transfers (function calls or jumps)
 *  - each function' instructions flow consist of
 *		- labels
 *		- source references for debugging
 *		- actual instruction entries, each instruction having its operands and formatted with its mnemonic
 *			- instruction operands represent the information provided by code generator to build-up the instruction
 *				- register references
 *				- immediate values
 *				- data and code labels
 *			- instruction mnemonic describe the output string structure for an assembler listing being generated, mnemonic format string consists of:
 *				- fixed string parts, which represented as-is in a listing (such as mnemonic name or operands' surrounding formatting)
 *				- operand parts, which depresented in a different way depending on the particular instruction operand
 *
 * * * * * * * * * * * * * * * * * * * * * */

#ifndef CODE_E_H
#define CODE_E_H

/// <summary>
/// The instruction operand type code
/// </summary>
BEGIN_ENUM(OperandKind)
{
	DECL_ENUM_ELEMENT_VAL(OPND_UNKNOWN, 0)
	DECL_ENUM_ELEMENT(OPND_INT_REG)
	DECL_ENUM_ELEMENT(OPND_FP_REG)
	DECL_ENUM_ELEMENT(OPND_IMMEDIATE)
	// DECL_ENUM_ELEMENT(OPND_OFFSET)
	DECL_ENUM_ELEMENT(OPND_DATA_LABEL)
	DECL_ENUM_ELEMENT(OPND_CODE_LABEL)
}
END_ENUM(OperandKind)

/// <summary>
/// The instruction type code
/// </summary>
BEGIN_ENUM(InstructionKind)
{
	DECL_ENUM_ELEMENT_VAL(KNOWN_INSNS_COUNT_START, 0)

	DECL_ENUM_ELEMENT(INSN_NOP)

	DECL_ENUM_ELEMENT(INSN_NOT)
	DECL_ENUM_ELEMENT(INSN_NEG)
	DECL_ENUM_ELEMENT(INSN_NEG_WORD)

	DECL_ENUM_ELEMENT(INSN_SIGN_EXTEND_BYTE)
	DECL_ENUM_ELEMENT(INSN_SIGN_EXTEND_HALF_WORD)
	DECL_ENUM_ELEMENT(INSN_SIGN_EXTEND_WORD)

	DECL_ENUM_ELEMENT(INSN_ZERO_EXTEND_BYTE)
	DECL_ENUM_ELEMENT(INSN_ZERO_EXTEND_HALF_WORD)
	DECL_ENUM_ELEMENT(INSN_ZERO_EXTEND_WORD)

	DECL_ENUM_ELEMENT(INSN_ADD)
	DECL_ENUM_ELEMENT(INSN_ADD_IMM)
	DECL_ENUM_ELEMENT(INSN_SUB)
	DECL_ENUM_ELEMENT(INSN_XOR)
	DECL_ENUM_ELEMENT(INSN_XOR_IMM)
	DECL_ENUM_ELEMENT(INSN_OR)
	DECL_ENUM_ELEMENT(INSN_OR_IMM)
	DECL_ENUM_ELEMENT(INSN_AND)
	DECL_ENUM_ELEMENT(INSN_AND_IMM)
	DECL_ENUM_ELEMENT(INSN_SHIFT_LEFT_LOGICAL)
	DECL_ENUM_ELEMENT(INSN_SHIFT_RIGHT_LOGICAL)
	DECL_ENUM_ELEMENT(INSN_SHIFT_RIGHT_ARITHMETIC)
	DECL_ENUM_ELEMENT(INSN_SET_LESS_SIGNED)
	DECL_ENUM_ELEMENT(INSN_SET_LESS_UNSIGNED)
	DECL_ENUM_ELEMENT(INSN_SGT)

	DECL_ENUM_ELEMENT(INSN_STORE_8)
	DECL_ENUM_ELEMENT(INSN_STORE_16)
	DECL_ENUM_ELEMENT(INSN_STORE_32)
	DECL_ENUM_ELEMENT(INSN_STORE_64)
	DECL_ENUM_ELEMENT(INSN_LOAD_8_SE)
	DECL_ENUM_ELEMENT(INSN_LOAD_8_ZE)
	DECL_ENUM_ELEMENT(INSN_LOAD_16_SE)
	DECL_ENUM_ELEMENT(INSN_LOAD_16_ZE)
	DECL_ENUM_ELEMENT(INSN_LOAD_32_SE)
	DECL_ENUM_ELEMENT(INSN_LOAD_64)

	DECL_ENUM_ELEMENT(INSN_MUL)
	DECL_ENUM_ELEMENT(INSN_DIV)
	DECL_ENUM_ELEMENT(INSN_REM)
		
	DECL_ENUM_ELEMENT(INSN_SEQ)
	DECL_ENUM_ELEMENT(INSN_SNE)
	DECL_ENUM_ELEMENT(INSN_BRANCH_EQUAL)
	DECL_ENUM_ELEMENT(INSN_BRANCH_NOT_EQUAL)
	DECL_ENUM_ELEMENT(INSN_BRANCH_LESS_SIGNED)
	DECL_ENUM_ELEMENT(INSN_BRANCH_GREATER_EQUAL)
	DECL_ENUM_ELEMENT(INSN_BRANCH_LESS_UNSIGNED)
	DECL_ENUM_ELEMENT(INSN_BRANCH_GREATER_EQUAL_UNSIGNED)

	DECL_ENUM_ELEMENT(INSN_BRANCH_IF_NOT_ZERO)
	DECL_ENUM_ELEMENT(INSN_JUMP)
	DECL_ENUM_ELEMENT(INSN_JUMP_AND_LINK)
	DECL_ENUM_ELEMENT(INSN_JUMP_REG)
	DECL_ENUM_ELEMENT(INSN_JUMP_REG_AND_LINK)
	DECL_ENUM_ELEMENT(INSN_CALL)
	DECL_ENUM_ELEMENT(INSN_RET)
	DECL_ENUM_ELEMENT(INSN_RE)
	DECL_ENUM_ELEMENT(INSN_LOAD_IMM)
	DECL_ENUM_ELEMENT(INSN_LOAD_IMM_UPPER)
	DECL_ENUM_ELEMENT(INSN_LOAD_ADDRESS)
	DECL_ENUM_ELEMENT(INSN_LOAD_ADDRESS_OF)
	DECL_ENUM_ELEMENT(INSN_MOVE)

	DECL_ENUM_ELEMENT(INSN_FLW)
	DECL_ENUM_ELEMENT(INSN_FSW)

	DECL_ENUM_ELEMENT(INSN_FADD)
	DECL_ENUM_ELEMENT(INSN_FSUB)
	DECL_ENUM_ELEMENT(INSN_FMUL)
	DECL_ENUM_ELEMENT(INSN_FDIV)
	DECL_ENUM_ELEMENT(INSN_FSQRT)
	DECL_ENUM_ELEMENT(INSN_FMIN)
	DECL_ENUM_ELEMENT(INSN_FMAX)
	DECL_ENUM_ELEMENT(INSN_F)

	DECL_ENUM_ELEMENT(KNOWN_INSNS_COUNT_END)
}
END_ENUM(InstructionKind)

/// <summary>
/// The known registers
/// </summary>
BEGIN_ENUM(RegisterId)
{
	DECL_ENUM_ELEMENT_VAL_STR(REG_UNKNOWN, -1, "UNK")
	// always has zero value (immutable)
	DECL_ENUM_ELEMENT_VAL_STR(REG_INT_ZERO, 0, "x0")
	// return address for jumps
	DECL_ENUM_ELEMENT_STR(REG_INT_RA, "ra")
	// stack pointer (saved across call)
	DECL_ENUM_ELEMENT_STR(REG_INT_SP, "sp")
	// global pointer (unallocatable)
	DECL_ENUM_ELEMENT_STR(REG_INT_GP, "gp")
	// thread pointer (unallocatable)
	DECL_ENUM_ELEMENT_STR(REG_INT_TP, "tp")
	// temporary register 0 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_T0, "t0")
	// temporary register 1 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_T1, "t1")
	// temporary register 2 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_T2, "t2")
	// saved register 0 or frame pointer (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S0FP, "s0")
	// saved register 1  (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S1, "s1")
	// return value or function argument 0 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A0, "a0")
	// return value or function argument 1 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A1, "a1")
	// function argument 2 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A2, "a2")
	// function argument 3 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A3, "a3")
	// function argument 4 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A4, "a4")
	// function argument 5 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A5, "a5")
	// function argument 6 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A6, "a6")
	// function argument 7 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_A7, "a7")
	// saved register 2 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S2, "s2")
	// saved register 3 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S3, "s3")
	// saved register 4 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S4, "s4")
	// saved register 5 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S5, "s5")
	// saved register 6 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S6, "s6")
	// saved register 7 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S7, "s7")
	// saved register 8 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S8, "s8")
	// saved register 9 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S9, "s9")
	// saved register 10 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S10, "s10")
	// saved register 11 (saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_S11, "s11")
	// temporary register 3 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_T3, "t3")
	// temporary register 4 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_T4, "t4")
	// temporary register 5 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_T5, "t5")
	// temporary register 6 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_T6, "t6")
	// temporary register 7 (not saved)
	DECL_ENUM_ELEMENT_STR(REG_INT_PC, "pc")

	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T0, "ft0")
	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T1, "ft1")
	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T2, "ft2")
	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T3, "ft3")
	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T4, "ft4")
	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T5, "ft5")
	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T6, "ft6")
	// FP temporary (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T7, "ft7")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S0, "fs0")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S1, "fs1")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A0, "fa0")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A1, "fa1")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A2, "fa2")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A3, "fa3")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A4, "fa4")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A5, "fa5")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A6, "fa6")
	// FP Argument register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_A7, "fa7")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S2, "fs2")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S3, "fs3")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S4, "fs4")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S5, "fs5")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S6, "fs6")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S7, "fs7")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S8, "fs8")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S9, "fs9")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S10, "fs10")
	// FP Callee-saved register (saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_S11, "fs11")
	// FP Temporary register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T8, "ft8")
	// FP Temporary register (not saved
	DECL_ENUM_ELEMENT_STR(REG_FP_T9, "ft9")
	// FP Temporary register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T10, "ft10")
	// FP Temporary register (not saved)
	DECL_ENUM_ELEMENT_STR(REG_FP_T11, "ft11")

	DECL_ENUM_ELEMENT(KNOWN_REGS_COUNT_END)
}
END_ENUM(RegisterId)

/// <summary>
/// The kind of instruction mnemonic' piece
/// </summary>
BEGIN_ENUM(InstructionMnemonicPartKind)
{
	DECL_ENUM_ELEMENT_VAL(MNEMONIC_PART_UNKNOWN, 0)
	DECL_ENUM_ELEMENT(MNEMONIC_PART_STRING)
	DECL_ENUM_ELEMENT(MNEMONIC_PART_OPERAND)
}
END_ENUM(InstructionMnemonicPartKind)

/// <summary>
/// The kind of instruction flow' item
/// </summary>
BEGIN_ENUM(InstructionFlowItemKind)
{
	DECL_ENUM_ELEMENT_VAL(FLOW_EMPTY, 0)
	DECL_ENUM_ELEMENT(FLOW_INSTRUCTION)
	DECL_ENUM_ELEMENT(FLOW_LABEL)
	DECL_ENUM_ELEMENT(FLOW_SOURCE_REF)
}
END_ENUM(InstructionFlowItemKind)

/// <summary>
/// The kind of global symbol represented in a module
/// </summary>
BEGIN_ENUM(SymbolKind)
{
	DECL_ENUM_ELEMENT(SYMBOL_PRIVATE_FUNCTION)
	DECL_ENUM_ELEMENT(SYMBOL_PUBLIC_FUNCTION)
	DECL_ENUM_ELEMENT(SYMBOL_PRIVATE_VARIABLE)
	DECL_ENUM_ELEMENT(SYMBOL_PUBLIC_VARIABLE)
	DECL_ENUM_ELEMENT(SYMBOL_PRIVATE_CONSTANT)
}
END_ENUM(SymbolKind)

#endif

#ifndef CODE_H
#define CODE_H

/// <summary>
/// A memory-referencing label
/// </summary>
typedef struct {
	int id;
	char* name;
	bool isExternal;
	// TODO it might be useful to distinguish data/code labels here
} LabelInfo;

/// <summary>
/// Instruction operand description
/// </summary>
typedef struct {
	/// The index of operand in the instruction description
	int index;
	/// The kind of operand denoting which information does it represent in the instruction
	OperandKind kind;
} InstructionOperandDescription;

/// <summary>
/// Instruction mnemonic string part description
/// </summary>
typedef struct {
	/// The kind of mnemonic piece denoting its interpretation during listing formatting
	InstructionMnemonicPartKind kind;
	union {
		char* string;
		int operandIndex;
	};
} InstructionMnemonicPart;

/// <summary>
/// Known native instruction description
/// </summary>
typedef struct {
	/// The kind of instruction identifying this description
	InstructionKind kind;
	/// The complete mnemonic format string template
	char* mnemonicFormat;
	/// The name of instruction mnemonic extracted from the its format string
	char* mnemonicName;
	/// The amount of mnemonic format pieces to interpret during listing formatting
	int mnemonicPartsCount;
	/// The array of mnemonic format pieces to print out for a listing
	InstructionMnemonicPart* mnemonicParts;
	/// The amount of instruction operands
	int operandsCount;
	/// The array of operand descriptions for this instruction
	InstructionOperandDescription* operands;
} InstructionDescription;

/// <summary>
/// Instruction operand instance carrying different meaning depending on the described type
/// </summary>
typedef struct {
	/// Corresnponding operand description
	InstructionOperandDescription* descr;
	union {
		int immediate;
		RegisterId reg;
		LabelInfo* label;
	};
} InstructionOperand;

/// <summary>
/// The native instruction instance
/// </summary>
typedef struct {
	/// Corresponding native instruction description
	InstructionDescription* descr;
	/// The array of operands belonging to this instruction instance
	InstructionOperand* operands;
} InstructionInfo;

/// <summary>
/// The instruction entry in a module' code section
/// </summary>
typedef struct {
	/// The kind of this instruction entry describing which information does it carry
	InstructionFlowItemKind kind;
	union {
		/// Actual native instruction instance
		InstructionInfo* instruction;
		/// Code label used for control-flow transfer
		LabelInfo* label;
		/// Syntax reference for a source relation
		AstNode* source;
	};
	/// Trailing comment string for the instruction line
	const char* comment;
} InsnFlowItem;

/// <summary>
/// The function routine in the object module context
/// </summary>
typedef struct {
	int id;
	/// The symbol used to reference this function implementation and representing it in the module
	struct SymbolInfo* symbol;
	/// The list of instruction entires representing the generated code
	LinkedList* flow;
} Routine;

typedef struct SymbolInfo {
	int id;
	SymbolKind kind;
	LabelInfo* label;
	int alignment;
	union {
		Routine* routine;
		int size;
	};
	char* rawData;
} SymbolInfo;

/// <summary>
/// Object module information
/// </summary>
typedef struct {
	/// The source name to reference
	char* sourceName;
	/// The list of all the symbols defined in a module
	LinkedList* symbols;
	/// The map of all the symbols defined in a module by their name
	RbTree* symbolsByName;
	/// The list of all the function routines represented in a module
	LinkedList* routines;
	/// The map of all the labels defined in a module' code by their name
	RbTree* labelsByName;
} Module;


/// <summary>
/// Generate the object module based on a given model of program translation unit
/// </summary>
/// <param name="model"></param>
/// <returns></returns>
Module* generate(ProgramUnit* model);

/// <summary>
/// Write the object module listing to the output file
/// </summary>
void serialize(Module* unit, FILE* out);

#endif
