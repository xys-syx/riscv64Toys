#include <stdarg.h>

#include "cfg.h"
#include "model.h"

#include "code.h"
#undef CODE_E_H
#define GENERATE_ENUM_STRINGS  // Start string generation
#include "code.h"
#undef GENERATE_ENUM_STRINGS   // Stop string generation


#if 1 // region INSN_SIGNATURE(...) {

#define INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL_OPND_INT_REG(type, name)		, RegisterId name
#define INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL_OPND_FP_REG(type, name)		, RegisterId name
#define INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL_OPND_IMMEDIATE(type, name)		, int name
#define INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL_OPND_DATA_LABEL(type, name)	, LabelInfo* name
#define INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL_OPND_CODE_LABEL(type, name)	, LabelInfo* name
#define INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL(type, name)					CONCAT(INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL_, type)(type, name)
#define INSN_SIGNATURE_EXPAND_EMITFNAME(x)	INSN_SIGNATURE_EXPAND_EMITFNAME_IMPL x

#define INSN_SIGNATURE_EXPAND_OPND_KIND_IMPL(type, name)					type, 
#define INSN_SIGNATURE_EXPAND_OPND_KIND(x)	INSN_SIGNATURE_EXPAND_OPND_KIND_IMPL x

#define INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL_OPND_INT_REG(type, name)		.reg = name;
#define INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL_OPND_INT_REG(type, name)		.reg = name;
#define INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL_OPND_FP_REG(type, name)		.reg = name;
#define INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL_OPND_IMMEDIATE(type, name)	.immediate = name;
#define INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL_OPND_DATA_LABEL(type, name)	.label = name;
#define INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL_OPND_CODE_LABEL(type, name)	.label = name;
#define INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL(type, name)					insnInfo->operands[opndIndex++]CONCAT(INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL_, type)(type, name)
#define INSN_SIGNATURE_EXPAND_SETOPERAND(x)	INSN_SIGNATURE_EXPAND_SETOPERAND_IMPL x

#define INSN_OPERAND(type, name)     (type, name)

#define INSN_SIGNATURE(fname, ...)																								\
																																\
	static void fname(CodeGenerationContext* ctx, InstructionKind insnKind MAP(INSN_SIGNATURE_EXPAND_EMITFNAME, __VA_ARGS__))	\
	{																															\
		OperandKind opndKinds[] = { MAP(INSN_SIGNATURE_EXPAND_OPND_KIND, __VA_ARGS__) OPND_UNKNOWN };								\
		InstructionInfo* insnInfo = prepareInstruction(ctx->routine->flow, insnKind, opndKinds);								\
		int opndIndex = 0;																										\
		MAP(INSN_SIGNATURE_EXPAND_SETOPERAND, __VA_ARGS__)																		\
		validateInstructionOperands(insnInfo);																					\
	}

#endif // } region INSN_SIGNATURE(...)



#define INSN_MAX_OPNDS 5

static InstructionDescription _knownInstructions[KNOWN_INSNS_COUNT_END - KNOWN_INSNS_COUNT_START];

static bool isLetterOrDigit(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= '0' && ch <= '9');
}

static char* extractFirstWord(char* str)
{
	if (str == NULL || *str == '0')
		return NULL;

	char* p = str;
	while (p != 0 && !isLetterOrDigit(*p)) p++;
	char* start = p;
	while (p != 0 && isLetterOrDigit(*p)) p++;
	char* end = p;

	int length = end - start;
	if (length == 0)
		return NULL;

	char* result = allocArray(char, length + 1);
	strncpy(result, start, length);
	result[length] = 0;
	return result;
}

static void registerInstruction(InstructionKind insn, char* mnemonicFormat, ...)
{
	InstructionMnemonicPart mnemonicParts[INSN_MAX_OPNDS * 2];
	InstructionOperandDescription operands[INSN_MAX_OPNDS];
	int operandsCount = 0, mnemonicPartsCount = 0;

	char* mnemonicName = extractFirstWord(mnemonicFormat);

	char* partStart = mnemonicFormat;
	char* p = mnemonicFormat;
	while (*p != 0)
	{
		if (*p == '$')
		{
			int strLength = p - partStart;
			char* str = allocArray(char, strLength + 1);
			strncpy(str, partStart, strLength);
			str[strLength] = 0;
			mnemonicParts[mnemonicPartsCount] = (InstructionMnemonicPart){
				.kind = MNEMONIC_PART_STRING,
				.string = str
			};
			mnemonicPartsCount++;

			partStart = p + 1;
			for (char ch = *partStart; isLetterOrDigit(ch); ch = *++p);

			mnemonicParts[mnemonicPartsCount] = (InstructionMnemonicPart){
				.kind = MNEMONIC_PART_OPERAND,
				.operandIndex = operandsCount++
			};
			mnemonicPartsCount++;

			partStart = p;
		}
		else 
		{
			++p;
		}
	}
	{
		int strLength = p - partStart;
		char* str = allocArray(char, strLength + 1);
		strncpy(str, partStart, strLength);
		str[strLength] = 0;
		mnemonicParts[mnemonicPartsCount].kind = MNEMONIC_PART_STRING;
		mnemonicParts[mnemonicPartsCount].string = str;
		mnemonicPartsCount++;
	}

	if (operandsCount > 0)
	{
		va_list ptrSpec;
		va_start(ptrSpec, mnemonicFormat);
		for (int i = 0; i < operandsCount; i++)
		{
			OperandKind kind = (OperandKind)va_arg(ptrSpec, int);
			operands[i].index = i;
			operands[i].kind = kind;
		}
		va_end(ptrSpec);
	}

	InstructionMnemonicPart* insnMnemonicParts = allocArray(InstructionMnemonicPart, mnemonicPartsCount + 1);
	copyArray(mnemonicParts, insnMnemonicParts, mnemonicPartsCount);
	insnMnemonicParts[mnemonicPartsCount] = (InstructionMnemonicPart){ .kind = MNEMONIC_PART_UNKNOWN, .string = NULL };

	InstructionOperandDescription* insnOperands = allocArray(InstructionOperandDescription, operandsCount + 1);
	copyArray(operands, insnOperands, operandsCount);
	insnOperands[operandsCount] = (InstructionOperandDescription){ .kind = OPND_UNKNOWN, .index = -1 };

	_knownInstructions[insn] = (InstructionDescription){
		.kind = insn,
		.operands = insnOperands,
		.operandsCount = operandsCount,
		.mnemonicName = mnemonicName,
		.mnemonicFormat = mnemonicFormat,
		.mnemonicParts = insnMnemonicParts,
		.mnemonicPartsCount = mnemonicPartsCount
	};
}

static bool isCalleeSavedReg(RegisterId reg)
{
	return (reg >= REG_INT_S2 && reg <= REG_INT_S11) || (reg >= REG_FP_S2 && reg <= REG_FP_S11);
}

static bool isIntReg(RegisterId reg)
{
	return reg >= REG_INT_ZERO && reg <= REG_INT_PC;
}

static bool isFpReg(RegisterId reg)
{
	return reg >= REG_FP_T0 && reg <= REG_FP_T11;
}

static bool _opsInitialized = false;

static void initOps(void)
{
	if (_opsInitialized)
		return;

	_opsInitialized = true;

	memset(_knownInstructions, 0, sizeof(_knownInstructions));

	registerInstruction(INSN_NOP, "nop");
	registerInstruction(INSN_LOAD_IMM, "li $dst, $imm", OPND_INT_REG, OPND_IMMEDIATE); //  LUI rd, imm	#	Load Upper Immediate : rd ← imm
	registerInstruction(INSN_LOAD_IMM_UPPER, "lui $dst, $imm", OPND_INT_REG, OPND_IMMEDIATE); //  LUI rd, imm	#	Load Upper Immediate : rd ← imm
	registerInstruction(INSN_LOAD_ADDRESS, "la $dst, $imm", OPND_INT_REG, OPND_IMMEDIATE); //  LUI rd, imm	#	Load Upper Immediate : rd ← imm
	registerInstruction(INSN_LOAD_ADDRESS_OF, "la $dst, $imm", OPND_INT_REG, OPND_DATA_LABEL); //  LUI rd, imm	#	Load Upper Immediate : rd ← imm
	registerInstruction(INSN_MOVE, "mv $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_NOT, "not $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_NEG, "neg $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_NEG_WORD, "negw $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_SIGN_EXTEND_BYTE, "sext.b $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_SIGN_EXTEND_HALF_WORD, "sext.h $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_SIGN_EXTEND_WORD, "sext.w $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_ZERO_EXTEND_BYTE, "sext.b $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_ZERO_EXTEND_HALF_WORD, "sext.h $dst, $src", OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_ZERO_EXTEND_WORD, "sext.w $dst, $src", OPND_INT_REG, OPND_INT_REG);

	registerInstruction(INSN_BRANCH_IF_NOT_ZERO, "bnez $value, $tgt", OPND_INT_REG, OPND_CODE_LABEL);
	registerInstruction(INSN_JUMP, "j $tgt", OPND_CODE_LABEL);
	registerInstruction(INSN_JUMP_AND_LINK, "jal $tgt", OPND_CODE_LABEL);
	registerInstruction(INSN_JUMP_REG, "jr $tgt", OPND_INT_REG);
	registerInstruction(INSN_JUMP_REG_AND_LINK, "jalr $tgt", OPND_INT_REG);
	registerInstruction(INSN_CALL, "call $tgt", OPND_CODE_LABEL);
	registerInstruction(INSN_RET, "ret");

	//registerInstruction(INSN_AUIPC, "AUIPC $rd, offset"); //	AUIPC rd, offset	#	Add Upper Immediate to PC	:	rd ← pc + offset
	//registerInstruction(INSN_JAL, "JAL $rd, offset"); //	JAL rd, offset	#	Jump and Link	:	rd ← pc + length(inst),  pc ← pc + offset
	//registerInstruction(INSN_JALR, "JALR $rd, rs1, offset"); //	JALR rd, rs1, offset	#	Jump and Link Register	:	rd ← pc + length(inst), pc ←(rs1 + offset) ∧ - 2

	registerInstruction(INSN_SET_LESS_SIGNED, "slt $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	SLT rd, rs1, rs2	#	Set Less Than	:	rd ← sx(rs1) < sx(rs2)
	registerInstruction(INSN_SET_LESS_UNSIGNED, "sltu  $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	SLTU rd, rs1, rs2	#	Set Less Than Unsigned	:	rd ← ux(rs1) < ux(rs2)

	registerInstruction(INSN_BRANCH_EQUAL, "beq $rs1, $rs2, $tgt", OPND_INT_REG, OPND_INT_REG, OPND_CODE_LABEL); //	BEQ rs1, rs2, offset	#	Branch Equal	:	if rs1 = rs2 then pc ← pc + offset
	registerInstruction(INSN_BRANCH_NOT_EQUAL, "bne $rs1, $rs2, $tgt", OPND_INT_REG, OPND_INT_REG, OPND_CODE_LABEL); //	BNE rs1, rs2, offset	#	Branch Not Equal	:	if rs1 ≠ rs2 then pc ← pc + offset
	registerInstruction(INSN_BRANCH_LESS_SIGNED, "blt $rs1, $rs2, $tgt", OPND_INT_REG, OPND_INT_REG, OPND_CODE_LABEL); //	BLT rs1, rs2, offset	#	Branch Less Than	:	if rs1 < rs2 then pc ← pc + offset
	registerInstruction(INSN_BRANCH_GREATER_EQUAL, "bge $rs1, $rs2, $tgt", OPND_INT_REG, OPND_INT_REG, OPND_CODE_LABEL); //	BGE rs1, rs2, offset	#	Branch Greater than Equal	:	if rs1 ≥ rs2 then pc ← pc + offset
	registerInstruction(INSN_BRANCH_LESS_UNSIGNED, "bltu $rs1, $rs2, $tgt", OPND_INT_REG, OPND_INT_REG, OPND_CODE_LABEL); //	BLTU rs1, rs2, offset	#	Branch Less Than Unsigned	:	if rs1 < rs2 then pc ← pc + offset
	registerInstruction(INSN_BRANCH_GREATER_EQUAL_UNSIGNED, "bgeu $rs1, $rs2, $tgt", OPND_INT_REG, OPND_INT_REG, OPND_CODE_LABEL); //	BGEU rs1, rs2, offset	#	Branch Greater than Equal Unsigned	:	if rs1 ≥ rs2 then pc ← pc + offset

	registerInstruction(INSN_STORE_8, "sb $src, $offset($dstAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG);  //	SB rs2, offset(rs1)	#	Store Byte	:	u8[rs1 + offset] ← rs2
	registerInstruction(INSN_STORE_16, "sh $src, $offset($dstAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	SH rs2, offset(rs1)	#	Store Half	:	u16[rs1 + offset] ← rs2
	registerInstruction(INSN_STORE_32, "sw $src, $offset($dstAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	SW rs2, offset(rs1)	#	Store Word	:	u32[rs1 + offset] ← rs2
	registerInstruction(INSN_STORE_64, "sd $src, $offset($dstAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	SD rs2, offset(rs1)	#	Store DWord	:	u64[rs1 + offset] ← rs2

	registerInstruction(INSN_LOAD_8_SE, "lu $dst, $offset($srcAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	LB rd, offset(rs1)	#	Load Byte   :	rd ← u8[rs1 + offset]
	registerInstruction(INSN_LOAD_16_SE, "lh $dst, $offset($srcAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	LH rd, offset(rs1)	#	Load Half	:	rd ← s16[rs1 + offset]
	registerInstruction(INSN_LOAD_32_SE, "lw $dst, $offset($srcAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	LW rd, offset(rs1)	#	Load Word	:	rd ← s32[rs1 + offset]
	registerInstruction(INSN_LOAD_8_ZE, "lbu $dst, $offset($srcAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	LBU rd, offset(rs1)	#	Load Byte Unsigned	:	rd ← u8[rs1 + offset]
	registerInstruction(INSN_LOAD_16_ZE, "lhu $dst, $offset($srcAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	LHU rd, offset(rs1)	#	Load Half Unsigned	:	rd ← u16[rs1 + offset]
	registerInstruction(INSN_LOAD_64, "ld $src, $offset($dstAddr)", OPND_INT_REG, OPND_IMMEDIATE, OPND_INT_REG); //	SW rs2, offset(rs1)	#	Load DWord	:	rd ← u64[rs1 + offset]

	registerInstruction(INSN_ADD_IMM, "addi $dst, $rs1, $imm", OPND_INT_REG, OPND_INT_REG, OPND_IMMEDIATE); //	ADDI rd, rs1, imm	#	Add Immediate	:	rd ← rs1 + sx(imm)
	//registerInstruction(INSN_SLTI, "SLTI $rd, rs1, imm"); //	SLTI rd, rs1, imm	#	Set Less Than Immediate	:	rd ← sx(rs1) < sx(imm)
	//registerInstruction(INSN_SLTIU, "SLTIU $rd, rs1, imm"); //	SLTIU rd, rs1, imm	#	Set Less Than Immediate Unsigned	:	rd ← ux(rs1) < ux(imm)
	registerInstruction(INSN_XOR_IMM, "xori $dst, $rs1, $imm", OPND_INT_REG, OPND_INT_REG, OPND_IMMEDIATE); //	XORI rd, rs1, imm	#	Xor Immediate	:	rd ← ux(rs1) ⊕ ux(imm)
	registerInstruction(INSN_OR_IMM, "ari $dst, $rs1, $imm", OPND_INT_REG, OPND_INT_REG, OPND_IMMEDIATE); //	ORI rd, rs1, imm	#	Or Immediate	:	rd ← ux(rs1) ∨ ux(imm)
	registerInstruction(INSN_AND_IMM, "andi $dst, $rs1, $imm", OPND_INT_REG, OPND_INT_REG, OPND_IMMEDIATE); //	ANDI rd, rs1, imm	#	And Immediate	:	rd ← ux(rs1) ∧ ux(imm)
	//registerInstruction(INSN_SLLI, "SLLI $rd, rs1, imm"); //	SLLI rd, rs1, imm	#	Shift Left Logical Immediate	:	rd ← ux(rs1) « ux(imm)
	//registerInstruction(INSN_SRLI, "SRLI $rd, rs1, imm"); //	SRLI rd, rs1, imm	#	Shift Right Logical Immediate	:	rd ← ux(rs1) » ux(imm)
	//registerInstruction(INSN_SRAI, "SRAI $rd, rs1, imm"); //	SRAI rd, rs1, imm	#	Shift Right Arithmetic Immediate	:	rd ← sx(rs1) » ux(imm)
	registerInstruction(INSN_ADD, "add $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	ADD rd, rs1, rs2	#	Add	:	rd ← sx(rs1) + sx(rs2)
	registerInstruction(INSN_SUB, "sub $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	SUB rd, rs1, rs2	#	Subtract	:	rd ← sx(rs1) - sx(rs2)
	registerInstruction(INSN_SHIFT_LEFT_LOGICAL, "sll $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	SLL rd, rs1, rs2	#	Shift Left Logical	:	rd ← ux(rs1) « rs2
	registerInstruction(INSN_XOR, "xor $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	XOR rd, rs1, rs2	#	Xor	:	rd ← ux(rs1) ⊕ ux(rs2)
	registerInstruction(INSN_SHIFT_RIGHT_LOGICAL, "srl $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	SRL rd, rs1, rs2	#	Shift Right Logical	:	rd ← ux(rs1) » rs2
	registerInstruction(INSN_SHIFT_RIGHT_ARITHMETIC, "sra $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	SRA rd, rs1, rs2	#	Shift Right Arithmetic	:	rd ← sx(rs1) » rs2
	registerInstruction(INSN_OR, "or $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	OR rd, rs1, rs2	#	Or	:	rd ← ux(rs1) ∨ ux(rs2)
	registerInstruction(INSN_AND, "and $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG); //	AND rd, rs1, rs2	#	And	:	rd ← ux(rs1) ∧ ux(rs2)
	//registerInstruction(INSN_FENCE, "FENCE $pred, succ"); //	FENCE pred, succ	#	Fence	:	

	registerInstruction(INSN_MUL, "mul $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_DIV, "div $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG);
	registerInstruction(INSN_REM, "rem $dst, $rs1, $rs2", OPND_INT_REG, OPND_INT_REG, OPND_INT_REG);
}

typedef struct {
	ValuePlaceInfo* info;
	bool isAllocated;
	bool wasSaved;
	int stackOffset;
} RegisterState;

typedef struct {
	TypeInfo* type;
	char* tag;
} StackItem;

typedef struct {
	ValuePlaceInfo* place;
	int inFrameOffset;
} LocalVarInfo;

typedef struct {
	FunctionSignature* signature;
	RegisterState regs[KNOWN_REGS_COUNT_END];
	RegisterId* intRegsAllocStack;
	int intRegsUnusedCount;
	StackItem** stack;
	int stackDepth;
	int evalStackOffset;
	LocalVarInfo* locals;
} MachineState;

typedef struct {
	ProgramUnit* model;
	Module* unit;
	Routine* routine;
	LabelInfo* exitRoutineLabel;
	MachineState* state;
	RegisterId expectedLocation;
	RegisterId resultLocation;
} CodeGenerationContext;

static bool makeLabel(Module* unit, char* name, LabelInfo** result)
{
	if (name == NULL)
	{
		size_t nameLen = snprintf(NULL, 0, "L%d", unit->labelsByName->count);
		name = allocArray(char, nameLen + 1);
		snprintf(name, nameLen + 1, "L%d", unit->labelsByName->count);
		name[nameLen] = 0;
	}

	LabelInfo* label = findRbTreeItem(unit->labelsByName, name);
	bool created;
	if (label == NULL)
	{
		label = allocStruct(LabelInfo);
		label->id = unit->labelsByName->count;
		label->name = name;
		label->isExternal = false;
		created = true;
		tryAddRbTreeItem(unit->labelsByName, name, label);
	}
	else
	{
		created = false;
	}
	// printTrace(NULL, "Label %s", label->name);
	*result = label;
	return created;
}

static SymbolInfo* createSymbol(Module* unit, SymbolKind kind, char* name, int size, int alignment, Routine* routine)
{
	SymbolInfo* symbol = allocStruct(SymbolInfo);
	clearStructure(symbol);
	symbol->id = unit->symbols->count;
	symbol->kind = kind;
	symbol->alignment = alignment;
	makeLabel(unit, name, &symbol->label);

	if (size > 0)
		symbol->size = size;

	if (routine != NULL)
		symbol->routine = routine;

	addLastLinkedListItem(unit->symbols, symbol);
	tryAddRbTreeItem(unit->symbolsByName, symbol->label->name, symbol);
	return symbol;
}

static void generateGlobalVar(ValuePlaceInfo* place, CodeGenerationContext* ctx)
{
	if (place->flags.isExported)
	{
		createSymbol(ctx->unit, SYMBOL_PUBLIC_VARIABLE, place->name, place->type->instanceSize, place->type->instanceSize, NULL);
	}
	else if (place->flags.isImplemented)
	{
		createSymbol(ctx->unit, SYMBOL_PRIVATE_VARIABLE, place->name, place->type->instanceSize, place->type->instanceSize, NULL);
	}
}

static InstructionInfo* prepareInstruction(LinkedList* flow, InstructionKind kind, OperandKind* opndKinds)
{
	initOps();
	InsnFlowItem* item = allocStruct(InsnFlowItem);
	item->kind = FLOW_EMPTY;
	item->comment = NULL;
	
	InstructionDescription* descr = &_knownInstructions[kind];
	if (descr->kind != kind)
	{
		printError(NULL, "Emitting unregistered instruction %s", getStringInstructionKind(kind));
		item->comment = "Unregistered instruction %s";
	}
	else
	{
		OperandKind* opndKind = opndKinds;
		int i;
		for (i = 0; i < descr->operandsCount && *opndKind != OPND_UNKNOWN; i++, opndKind++)
		{
			if (descr->operands[i].kind != opndKinds[i])
			{
				printError(NULL, "Inconsistent instruction %s operands: %s given while %s required", getStringInstructionKind(kind), getStringOperandKind(opndKinds[i]), getStringOperandKind(descr->operands[i].kind));
				item->comment = "Inconsistent instruction %s operands: %s given while %s required";
			}
		}

		if (i != descr->operandsCount || *opndKind != OPND_UNKNOWN)
		{
			printError(NULL, "Invalid amount of operands while emitting instruction %s", getStringInstructionKind(kind));
			item->comment = "Invalid amount of operands while emitting instruction %s";
		}
	}

	if (item->comment == NULL)
	{
		InstructionInfo* insn = allocStruct(InstructionInfo);
		insn->descr = descr;
		insn->operands = allocArray(InstructionOperand, descr->operandsCount);
		item->kind = FLOW_INSTRUCTION;
		item->instruction = insn;
		addLastLinkedListItem(flow, item);
		return insn;
	}
	else
	{
		return NULL;
	}
}

static void validateInstructionOperands(InstructionInfo* insn)
{
	for (int i = 0; i < insn->descr->operandsCount; i++)
	{
		switch (insn->descr->operands[i].kind)
		{
		case OPND_INT_REG: {
			if (!isIntReg(insn->operands[i].reg))
			{
				printError(NULL, "Expected Integer register while given %s for %d operand of %s instruction", getStringRegisterId(insn->operands[i].reg), i, getStringInstructionKind(insn->descr->kind));
			}
		} break;
		case OPND_FP_REG: {
			if (!isFpReg(insn->operands[i].reg))
			{
				printError(NULL, "Expected Floating point register while given %s for %d operand of %s instruction", getStringRegisterId(insn->operands[i].reg), i, getStringInstructionKind(insn->descr->kind));
			}
		} break;
		case OPND_IMMEDIATE:
		case OPND_DATA_LABEL:
		case OPND_CODE_LABEL:
			break;
		default:
			printError(NULL, "Unexpected instruction operand kind kind %s", getStringOperandKind(insn->descr->operands[i].kind));
			break;
		}
	}
}

INSN_SIGNATURE(emitInstructionCondJump,
	INSN_OPERAND(OPND_INT_REG, a),
	INSN_OPERAND(OPND_INT_REG, b),
	INSN_OPERAND(OPND_CODE_LABEL, tgt)
)
INSN_SIGNATURE(emitInstructionDirectJump,
	INSN_OPERAND(OPND_INT_REG, tgt)
)
INSN_SIGNATURE(emitInstructionImmJump,
	INSN_OPERAND(OPND_CODE_LABEL, tgt)
)
INSN_SIGNATURE(emitInstructionStoreLoad,
	INSN_OPERAND(OPND_INT_REG, value),
	INSN_OPERAND(OPND_IMMEDIATE, offset),
	INSN_OPERAND(OPND_INT_REG, address)
)
INSN_SIGNATURE(emitInstructionAddressToIReg,
	INSN_OPERAND(OPND_INT_REG, dst),
	INSN_OPERAND(OPND_DATA_LABEL, value)
)
INSN_SIGNATURE(emitInstructionImmToIReg,
	INSN_OPERAND(OPND_INT_REG, dst),
	INSN_OPERAND(OPND_IMMEDIATE,value)
)
INSN_SIGNATURE(emitInstructionIRegIRegToIReg,
	INSN_OPERAND(OPND_INT_REG, dst),
	INSN_OPERAND(OPND_INT_REG, a),
	INSN_OPERAND(OPND_INT_REG, b)
)
INSN_SIGNATURE(emitInstructionImmIRegToIReg,
	INSN_OPERAND(OPND_INT_REG, dst),
	INSN_OPERAND(OPND_INT_REG, a),
	INSN_OPERAND(OPND_IMMEDIATE, b)
)
INSN_SIGNATURE(emitInstructionIRegToIReg,
	INSN_OPERAND(OPND_INT_REG, dst),
	INSN_OPERAND(OPND_INT_REG, src)
)

static void emitInstructionNoOperands(CodeGenerationContext* ctx, InstructionKind insnKind)
{																															
	OperandKind opndKinds[] = { OPND_UNKNOWN };
	prepareInstruction(ctx->routine->flow, insnKind, opndKinds);
}

static void setLastFlowItemComment(CodeGenerationContext* ctx, const char* comment)
{
	InsnFlowItem* item = (InsnFlowItem*)ctx->routine->flow->last->data;

	if (item != NULL)
	{
		if (item->comment == NULL)
		{
			item->comment = comment;
		}
	}
}

static void emitSourceRef(CodeGenerationContext* ctx, AstNode* ast)
{
	InsnFlowItem* item = allocStruct(InsnFlowItem);
	item->kind = FLOW_SOURCE_REF;
	item->source = ast;
	item->comment = NULL;
	addLastLinkedListItem(ctx->routine->flow, item);
}

static LabelInfo* makeBlockLabel(CodeGenerationContext* ctx, int blockId)
{
	const char* nameFormat = "%s_block_%d";
	size_t nameLen = snprintf(NULL, 0, nameFormat, ctx->routine->symbol->label->name, blockId);
	char* name = allocArray(char, nameLen + 1);
	sprintf(name, nameFormat, ctx->routine->symbol->label->name, blockId);
	name[nameLen] = 0;

	LabelInfo* label;
	if (!makeLabel(ctx->unit, name, &label))
		free(name);

	return label;
}

static void emitLabelImpl(CodeGenerationContext* ctx, LabelInfo* label)
{
	InsnFlowItem* item = allocStruct(InsnFlowItem);
	item->kind = FLOW_LABEL;
	item->label = label;
	item->comment = NULL;
	addLastLinkedListItem(ctx->routine->flow, item);
}

static LabelInfo* emitLabel(CodeGenerationContext* ctx, int blockId)
{
	LabelInfo* label = makeBlockLabel(ctx, blockId);
	emitLabelImpl(ctx, label);
	return label;
}

static RegisterId _intArgumentsMap[] = {
	REG_INT_A0,
	REG_INT_A1,
	REG_INT_A2,
	REG_INT_A3,
	REG_INT_A4,
	REG_INT_A5,
	REG_INT_A6,
	REG_INT_A7,
};
const int _intArgumentsMapSize = sizeof(_intArgumentsMap) / sizeof(RegisterId);

static RegisterId allocateRegister(CodeGenerationContext* ctx, RegisterId desired)
{
	UNUSED(desired); // TODO

	if (ctx->state->intRegsUnusedCount > 0)
	{
		RegisterId reg = ctx->state->intRegsAllocStack[--ctx->state->intRegsUnusedCount];
		ctx->state->regs[reg].isAllocated = true;
		if (isCalleeSavedReg(reg) && !ctx->state->regs[reg].wasSaved)
		{
			//ctx->state->regs[reg].wasSaved = true;
			//ctx->state->evalStackOffset-= 
			//emitInstructionStoreLoad(ctx, INSN_STORE_64, reg, stackOffset, REG_INT_S0FP);
			printError(NULL, "Spilling not implemented for callee-saved regs");
		}
		//printTrace(NULL, "register %s allocated", getStringRegisterId(reg));
		return reg;
	}
	else 
	{
		printError(NULL, "Spilling not implemented, no regs to use");
		return REG_UNKNOWN;
	}
}

static void releaseRegister(CodeGenerationContext* ctx, RegisterId reg)
{
	//printTrace(NULL, "register %s released", getStringRegisterId(reg));
	ctx->state->intRegsAllocStack[ctx->state->intRegsUnusedCount++] = reg;
	ctx->state->regs[reg].isAllocated = false;
}

static void preserveState(CodeGenerationContext* ctx)
{
	RegisterState* regs = ctx->state->regs;
	for (int i = 0; i < KNOWN_REGS_COUNT_END; i++)
	{
		if (regs->isAllocated)
		{
			emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, REG_INT_SP, REG_INT_SP, -16);	// addi    sp, sp, -16
			emitInstructionStoreLoad(ctx, INSN_STORE_64, (RegisterId)i, 0, REG_INT_SP);		// sd      ra,8(sp)        #,
		}
	}
}

static void restoreState(CodeGenerationContext* ctx)
{
	RegisterState* regs = ctx->state->regs;
	for (int i = 0; i < KNOWN_REGS_COUNT_END; i++)
	{
		if (regs->isAllocated)
		{
			emitInstructionStoreLoad(ctx, INSN_LOAD_64, (RegisterId)i, 0, REG_INT_SP);		// sd      ra,8(sp)        #,
			emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, REG_INT_SP, REG_INT_SP, 16);	// addi    sp, sp, -16
		}
	}
}

static void pushStack(CodeGenerationContext* ctx, StackItem* item)
{
	ctx->state->stack[ctx->state->stackDepth++] = item;
}

static StackItem* popStack(CodeGenerationContext* ctx)
{
	StackItem** itemPtr = &ctx->state->stack[--ctx->state->stackDepth];
	StackItem* result = *itemPtr;
	*itemPtr = NULL;
	return result;
}

static void allocateLocalVarAction(ValuePlaceInfo* var, MachineState* state)
{
	int size = alignSize(var->type->instanceSize, 8);
	state->evalStackOffset -= size;
	state->locals[var->id].place = var;
	state->locals[var->id].inFrameOffset = state->evalStackOffset;
}

static RegisterId allocQueueInitState[] = {
	REG_INT_S11,
	REG_INT_S10,
	REG_INT_S9,
	REG_INT_S8,
	REG_INT_S7,
	REG_INT_S6,
	REG_INT_S5,
	REG_INT_S4,
	REG_INT_S3,
	REG_INT_S2,
	REG_INT_T6,
	REG_INT_T5,
	REG_INT_T4,
	REG_INT_T3,
	REG_INT_T2,
	REG_INT_T1,
	REG_INT_T0,
};

static const int allocQueueInitLength = sizeof(allocQueueInitState) / sizeof(RegisterId);

static void resetMachineState(MachineState* state)
{
	state->intRegsUnusedCount = allocQueueInitLength;
	memcpy(state->intRegsAllocStack, allocQueueInitState, sizeof(allocQueueInitState));
	state->intRegsAllocStack[allocQueueInitLength] = REG_UNKNOWN;
	state->stackDepth = 0;

	RegisterState* regs = state->regs;
	for (int i = 0; i < KNOWN_REGS_COUNT_END; i++)
	{
		if (regs->isAllocated)
		{
			regs->isAllocated = false;
		}
	}
}

static MachineState* prepareMachineState(Function* func)
{
	MachineState* state = allocStruct(MachineState);
	memset(state, 0, sizeof(MachineState));
	state->signature = func->signature;
	state->stack = allocArray(StackItem*, func->maxStackDepth);
	state->stackDepth = 0;
	state->evalStackOffset = -16;
	
	state->intRegsAllocStack = allocArray(RegisterId, allocQueueInitLength + 1);
	resetMachineState(state);

	state->locals = allocArray(LocalVarInfo, func->body->vars->places->count);
	traverseLinkedList(func->body->vars->places, (action2)allocateLocalVarAction, state);
	state->evalStackOffset = alignSize(state->evalStackOffset, 16);

	return state;
}

static void releaseMachineState(MachineState* state)
{
	free(state->stack);
	free(state->intRegsAllocStack);
	free(state->locals);
	free(state);
}

static void generateCfgExpr(CfgExprNode* expr, CodeGenerationContext* ctx);

static void generateBinaryExpression(CfgExprNode* expr, CodeGenerationContext* ctx)
{
	generateCfgExpr(expr->args[1], ctx);
	RegisterId b = ctx->resultLocation;
	generateCfgExpr(expr->args[0], ctx);
	RegisterId a = ctx->resultLocation;
	releaseRegister(ctx, b);

	switch (expr->kind)
	{
	case CFG_EXPR_ADD: emitInstructionIRegIRegToIReg(ctx, INSN_ADD, a, a, b); break;
	case CFG_EXPR_SUB: emitInstructionIRegIRegToIReg(ctx, INSN_SUB, a, a, b); break;
	case CFG_EXPR_MUL: emitInstructionIRegIRegToIReg(ctx, INSN_MUL, a, a, b); break;
	case CFG_EXPR_DIV: emitInstructionIRegIRegToIReg(ctx, INSN_DIV, a, a, b); break;
	case CFG_EXPR_REM: emitInstructionIRegIRegToIReg(ctx, INSN_REM, a, a, b); break;
	case CFG_EXPR_CMP_EQ:
	case CFG_EXPR_CMP_NEQ:
	case CFG_EXPR_CMP_LT:
	case CFG_EXPR_CMP_GT:
	case CFG_EXPR_CMP_LTEQ: emitInstructionIRegIRegToIReg(ctx, INSN_SET_LESS_SIGNED, a, a, b); break;
	case CFG_EXPR_CMP_GTEQ: emitInstructionIRegIRegToIReg(ctx, INSN_SET_LESS_SIGNED, a, b, a); break;
	case CFG_EXPR_BOOL_AND: 
		emitInstructionIRegIRegToIReg(ctx, INSN_AND, a, a, b);
		emitInstructionImmIRegToIReg(ctx, INSN_AND_IMM, a, a, 1);
		break;
	case CFG_EXPR_BOOL_OR: 
		emitInstructionIRegIRegToIReg(ctx, INSN_OR, a, a, b);
		emitInstructionImmIRegToIReg(ctx, INSN_AND_IMM, a, a, 1);
		break;
	case CFG_EXPR_BITS_XOR: emitInstructionIRegIRegToIReg(ctx, INSN_XOR, a, a, b); break;
	case CFG_EXPR_BITS_AND: emitInstructionIRegIRegToIReg(ctx, INSN_AND, a, a, b); break;
	case CFG_EXPR_BITS_OR: emitInstructionIRegIRegToIReg(ctx, INSN_OR, a, a, b); break;
	case CFG_EXPR_BITS_SHL: emitInstructionIRegIRegToIReg(ctx, INSN_SHIFT_LEFT_LOGICAL, a, a, b); break;
	case CFG_EXPR_BITS_SHR: emitInstructionIRegIRegToIReg(ctx, INSN_SHIFT_RIGHT_LOGICAL, a, a, b); break;
	default:
		printError(expr->ast, "Unexpected control-flow expression %s", getStringCfgExprKind(expr->kind));
		break;
	}

	setLastFlowItemComment(ctx, getStringCfgExprKind(expr->kind));
}

static void generateUnaryExpression(CfgExprNode* expr, CodeGenerationContext* ctx)
{
	generateCfgExpr(expr->args[0], ctx);
	RegisterId reg = ctx->resultLocation;

	switch (expr->kind)
	{
	case CFG_EXPR_BOOL_NOT: 
		emitInstructionIRegToIReg(ctx, INSN_NOT, reg, reg); 
		emitInstructionImmIRegToIReg(ctx, INSN_AND_IMM, reg, reg, 1); break;
		break;
	case CFG_EXPR_BITS_INV: emitInstructionIRegToIReg(ctx, INSN_NOT, reg, reg); break;
	case CFG_EXPR_UNARY_PLUS: /* do nothing */ break;
	case CFG_EXPR_UNARY_MINUS: emitInstructionIRegToIReg(ctx, INSN_NEG, reg, reg); break;
	case CFG_EXPR_UNARY_REF:
	case CFG_EXPR_UNARY_UNREF:
	default:
		printError(expr->ast, "Unexpected control-flow expression %s", getStringCfgExprKind(expr->kind));
		break;
	}

	setLastFlowItemComment(ctx, getStringCfgExprKind(expr->kind));
}

static void generateAddressOfIndexedPlace(CfgExprNode* indexExpr, CodeGenerationContext* ctx)
{
	CfgExprNode* indexBase = indexExpr->args[0];
	ValuePlaceInfo* place;
	bool isGlobal;
	int itemSize;
	if (indexBase->kind == CFG_EXPR_ENTITY_ID)
	{
		place = indexBase->payload.valuePlace;
		isGlobal = findRbTreeItem(ctx->model->globalVars->placeByName, place->name) == place;

		if (indexBase->type->kind == TYPE_ARRAY)
		{
			itemSize = indexBase->type->details.arrays.elementType->instanceSize;
		}
		else if (indexBase->type->kind == TYPE_POINTER)
		{
			itemSize = indexBase->type->details.pointers.targetType->instanceSize;
		}
		else
		{
			printError(indexExpr->ast, "Unsupported indexing base type %s", indexBase->type->name);
			return;
		}
	}
	else
	{
		printError(indexExpr->ast, "Unsupported indexing base %s", indexBase->type->name);
		return;
	}

	generateCfgExpr(indexExpr->args[1], ctx);
	RegisterId indexLocation = ctx->resultLocation;

	if (indexBase->type->kind == TYPE_ARRAY)
	{
		for (int i = 2; i < indexExpr->argsCount; i++)
		{
			RegisterId t = allocateRegister(ctx, REG_UNKNOWN);
			emitInstructionImmToIReg(ctx, INSN_LOAD_IMM, t, indexBase->type->details.arrays.dimSize[i - 2]);
			emitInstructionIRegIRegToIReg(ctx, INSN_MUL, indexLocation, indexLocation, t);
			releaseRegister(ctx, t);
			generateCfgExpr(indexExpr->args[i], ctx);
			emitInstructionIRegIRegToIReg(ctx, INSN_ADD, indexLocation, indexLocation, ctx->resultLocation);
			releaseRegister(ctx, ctx->resultLocation);
		}
	}

	RegisterId t = allocateRegister(ctx, REG_UNKNOWN);
	emitInstructionImmToIReg(ctx, INSN_LOAD_IMM, t, itemSize);
	emitInstructionIRegIRegToIReg(ctx, INSN_MUL, indexLocation, indexLocation, t);

	if (isGlobal)
	{
		LabelInfo* label;
		makeLabel(ctx->unit, place->name, &label);
		emitInstructionAddressToIReg(ctx, INSN_LOAD_ADDRESS_OF, t, label);
	}
	else
	{
		emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, t, REG_INT_S0FP, ctx->state->locals[place->id].inFrameOffset);
	}

	setLastFlowItemComment(ctx, place->name);

	if (indexBase->type->kind == TYPE_POINTER)
		emitInstructionStoreLoad(ctx, INSN_LOAD_64, t, 0, t);

	emitInstructionIRegIRegToIReg(ctx, INSN_ADD, indexLocation, indexLocation, t);

	releaseRegister(ctx, t);
	ctx->resultLocation = indexLocation;

	setLastFlowItemComment(ctx, "indexed item ref");
}

static void generateCfgExpr(CfgExprNode* expr, CodeGenerationContext* ctx)
{
	ctx->resultLocation = REG_UNKNOWN;

	switch (expr->kind)
	{
	case CFG_EXPR_LITERAL_INT: {
		RegisterId reg = allocateRegister(ctx, ctx->expectedLocation);
		emitInstructionImmToIReg(ctx, INSN_LOAD_IMM, reg, expr->payload.integer);
		ctx->resultLocation = reg;
		setLastFlowItemComment(ctx, getStringCfgExprKind(expr->kind));
	} break;
	case CFG_EXPR_LITERAL_CHAR: {
		RegisterId reg = allocateRegister(ctx, ctx->expectedLocation);
		emitInstructionImmToIReg(ctx, INSN_LOAD_IMM, reg, expr->payload.character);
		ctx->resultLocation = reg;
		setLastFlowItemComment(ctx, getStringCfgExprKind(expr->kind));
	} break;
	//case CFG_EXPR_LITERAL_FLOAT: {
	//} break;
	case CFG_EXPR_LITERAL_STRING: {
		char* data = expr->payload.string;
		int dataLength = strlen(expr->payload.string) + 1;
		SymbolInfo* symbol = createSymbol(ctx->unit, SYMBOL_PRIVATE_CONSTANT, NULL, dataLength, 4, NULL);
		symbol->rawData = data + 1;
		
		RegisterId reg = allocateRegister(ctx, ctx->expectedLocation);
		emitInstructionAddressToIReg(ctx, INSN_LOAD_ADDRESS_OF, reg, symbol->label);
		ctx->resultLocation = reg;
		setLastFlowItemComment(ctx, expr->payload.string);
	} break;
	case CFG_EXPR_ASSIGN: {
		CfgExprNode* target = expr->args[0];
		TypeInfo* targetType = target->type;

		generateCfgExpr(expr->args[1], ctx);
		RegisterId reg = ctx->resultLocation;

		InstructionKind insn;
		switch (expr->type->instanceSize)
		{
		case 1: insn = INSN_STORE_8; break;
		case 2: insn = INSN_STORE_16; break;
		case 4: insn = INSN_STORE_32; break;
		case 8: insn = INSN_STORE_64; break;
		default:
			printError(NULL, "unsupported store operand size %d of type %s", expr->type->instanceSize, expr->type->name);
			break;
		}

		if (target->kind == CFG_EXPR_ENTITY_ID) 
		{
			if (targetType->kind != TYPE_FUNC)
			{
				ValuePlaceInfo* place = expr->payload.valuePlace;
				if (findRbTreeItem(ctx->model->globalVars->placeByName, place->name) == place)
				{
					LabelInfo* label;
					makeLabel(ctx->unit, place->name, &label);
					RegisterId t = allocateRegister(ctx, REG_UNKNOWN);
					emitInstructionAddressToIReg(ctx, INSN_LOAD_ADDRESS_OF, t, label);
					emitInstructionStoreLoad(ctx, insn, reg, 0, t);
					releaseRegister(ctx, t);
					ctx->resultLocation = reg;
				}
				else if (findRbTreeItem(ctx->state->signature->parameters->placeByName, place->name) == place)
				{
					if (place->id >= _intArgumentsMapSize)
					{
						printError(expr->ast, "Functions having more than %d arguments are not supported for now", _intArgumentsMapSize);
					}
					else
					{
						emitInstructionIRegToIReg(ctx, INSN_MOVE, ctx->resultLocation = _intArgumentsMap[place->id], reg);
						ctx->resultLocation = reg;
					}
				}
				else
				{
					emitInstructionStoreLoad(ctx, insn, reg, ctx->state->locals[place->id].inFrameOffset, REG_INT_S0FP);
					ctx->resultLocation = reg;
				}
				setLastFlowItemComment(ctx, place->name);
			}
			else
			{
				printError(expr->ast, "Cannot assign to a function %s", target->payload.function->name);
			}
		}
		else if (target->kind == CFG_EXPR_INDEX)
		{
			generateAddressOfIndexedPlace(target, ctx);
			emitInstructionStoreLoad(ctx, insn, reg, 0, ctx->resultLocation);
			setLastFlowItemComment(ctx, "set");
			ctx->resultLocation = reg;
		}
		else if (target->kind == CFG_EXPR_UNARY_UNREF)
		{
			generateCfgExpr(expr->args[0], ctx);
			RegisterId addressLocation = ctx->resultLocation;
			emitInstructionStoreLoad(ctx, insn, reg, 0, addressLocation);
			setLastFlowItemComment(ctx, "set");
			releaseRegister(ctx, addressLocation);
			ctx->resultLocation = reg;
		}
		else if (target->kind == CFG_EXPR_ACCESS_PTR)
		{
			printError(expr->ast, "Unsupported assignment target"); // TODO structs and unions
		}
		else if (target->kind == CFG_EXPR_ACCESS_DIRECT)
		{
			printError(expr->ast, "Unsupported assignment target"); // TODO structs and unions
		}
		else
		{
			printError(expr->ast, "Invalid assignment target");
		}
	} break;
	case CFG_EXPR_ADD:
	case CFG_EXPR_SUB:
	case CFG_EXPR_MUL:
	case CFG_EXPR_DIV:
	case CFG_EXPR_REM: generateBinaryExpression(expr, ctx); break;
	case CFG_EXPR_CMP_EQ:
	case CFG_EXPR_CMP_NEQ:
	case CFG_EXPR_CMP_LT:
	case CFG_EXPR_CMP_GT:
	case CFG_EXPR_CMP_LTEQ:
	case CFG_EXPR_CMP_GTEQ: generateBinaryExpression(expr, ctx); break;
	case CFG_EXPR_BOOL_NOT: generateUnaryExpression(expr, ctx); break;
	case CFG_EXPR_BOOL_AND:
	case CFG_EXPR_BOOL_OR: generateBinaryExpression(expr, ctx); break;
	case CFG_EXPR_BITS_INV: generateUnaryExpression(expr, ctx); break;
	case CFG_EXPR_BITS_XOR:
	case CFG_EXPR_BITS_AND:
	case CFG_EXPR_BITS_OR: 
	case CFG_EXPR_BITS_SHL:
	case CFG_EXPR_BITS_SHR: generateBinaryExpression(expr, ctx); break;
	case CFG_EXPR_UNARY_PLUS:
	case CFG_EXPR_UNARY_MINUS: generateUnaryExpression(expr, ctx); break;
	case CFG_EXPR_ENTITY_ID: {
		InstructionKind insn;
		switch (expr->type->instanceSize)
		{
		case 1: insn = INSN_LOAD_8_SE; break;
		case 2: insn = INSN_LOAD_16_SE; break;
		case 4: insn = INSN_LOAD_32_SE; break;
		case 8: insn = INSN_LOAD_64; break;
		default:
			printError(expr->ast, "unsupported load operand size %d of type %s", expr->type->instanceSize, expr->type->name);
			break;
		}

		if (expr->type->kind != TYPE_FUNC)
		{
			RegisterId reg = allocateRegister(ctx, ctx->expectedLocation);

			ValuePlaceInfo* place = expr->payload.valuePlace;
			if (findRbTreeItem(ctx->model->globalVars->placeByName, place->name) == place)
			{
				LabelInfo* label;
				makeLabel(ctx->unit, place->name, &label);
				RegisterId t = allocateRegister(ctx, REG_UNKNOWN);
				emitInstructionAddressToIReg(ctx, INSN_LOAD_ADDRESS_OF, t, label);
				emitInstructionStoreLoad(ctx, insn, reg, 0, t);
				releaseRegister(ctx, t);
				ctx->resultLocation = reg;
			}
			else if (findRbTreeItem(ctx->state->signature->parameters->placeByName, place->name) == place)
			{
				if (place->id >= _intArgumentsMapSize)
				{
					printError(expr->ast, "Functions having more than %d arguments are not supported for now", _intArgumentsMapSize);
				}
				else
				{
					RegisterId t = allocateRegister(ctx, ctx->expectedLocation);
					emitInstructionIRegToIReg(ctx, INSN_MOVE, t, ctx->resultLocation = _intArgumentsMap[place->id]);
					ctx->resultLocation = t;
				}
			}
			else
			{
				
				emitInstructionStoreLoad(ctx, insn, reg, ctx->state->locals[place->id].inFrameOffset, REG_INT_S0FP);
				ctx->resultLocation = reg;
			}
		
			setLastFlowItemComment(ctx, place->name);
		}
		else
		{
			printError(expr->ast, "Cannot read from a function %s", expr->payload.function->name);
		}
	} break;
	case CFG_EXPR_INDEX: {
		InstructionKind insn;
		switch (expr->type->instanceSize)
		{
		case 1: insn = INSN_LOAD_8_SE; break;
		case 2: insn = INSN_LOAD_16_SE; break;
		case 4: insn = INSN_LOAD_32_SE; break;
		case 8: insn = INSN_LOAD_64; break;
		default:
			printError(expr->ast, "unsupported indexed load operand size %d of type %s", expr->type->instanceSize, expr->type->name);
			break;
		}
		RegisterId reg = ctx->expectedLocation;
		ctx->expectedLocation = REG_UNKNOWN;
		generateAddressOfIndexedPlace(expr, ctx);
		RegisterId addrReg = ctx->resultLocation;
		if (addrReg != reg)
		{
			releaseRegister(ctx, addrReg);
			reg = allocateRegister(ctx, reg);
		}
		emitInstructionStoreLoad(ctx, insn, reg, 0, addrReg);
		ctx->resultLocation = reg;
	} break;
	case CFG_EXPR_CALL: {
		TypeInfo* targetType = expr->args[0]->type;
		if (targetType->kind == TYPE_FUNC && expr->args[0]->kind == CFG_EXPR_ENTITY_ID)
		{
			RegisterId reg = ctx->expectedLocation;
			//FunctionSignature* signature = targetType->details.functions.signature;
			expr->payload.function = expr->args[0]->payload.function;

			// preschedule register for args
			for (int i = expr->argsCount - 1; i >= 1; i--)
			{
				if (i >= _intArgumentsMapSize)
				{
					printError(expr->ast, "Functions having more than %d arguments are not supported for now", _intArgumentsMapSize);
				}
				else 
				{
					ctx->expectedLocation = _intArgumentsMap[i - 1];
					generateCfgExpr(expr->args[i], ctx);
					if (ctx->resultLocation != _intArgumentsMap[i - 1])
					{
						emitInstructionIRegToIReg(ctx, INSN_MOVE, _intArgumentsMap[i - 1], ctx->resultLocation);
						releaseRegister(ctx, ctx->resultLocation);
					}
				}
			}

			preserveState(ctx);
			LabelInfo* target;
			makeLabel(ctx->unit, expr->payload.function->name, &target);
			emitInstructionImmJump(ctx, INSN_CALL, target);
			setLastFlowItemComment(ctx, expr->payload.function->name);
			restoreState(ctx);

			//for (int i = 0; i < _intArgumentsMapSize; i++)
			//	releaseRegister(ctx, _intArgumentsMap[i]);

			reg = allocateRegister(ctx, reg);
			if (reg != REG_INT_A0)
			{
				emitInstructionIRegToIReg(ctx, INSN_MOVE, reg, REG_INT_A0);
			}
			ctx->resultLocation = reg;
		}
		else
		{
			printError(expr->ast, "Indirect call not supported");
		}
	} break;
	case CFG_EXPR_RET: {
		if (expr->argsCount > 0)
		{
			ctx->expectedLocation = REG_INT_A0;
			generateCfgExpr(expr->args[0], ctx);

			if (ctx->resultLocation != REG_INT_A0)
			{
				emitInstructionIRegToIReg(ctx, INSN_MOVE, REG_INT_A0, ctx->resultLocation);
			}
			emitInstructionImmJump(ctx, INSN_JUMP, ctx->exitRoutineLabel);
		
			setLastFlowItemComment(ctx, "return");
		}
	} break;
	//case CFG_EXPR_COALESCE: /* TODO */
	//case CFG_EXPR_PRESERVE: /* TODO */
	//case CFG_EXPR_LOAD_LOCAL: {
	//} break;
	//case CFG_EXPR_LOAD_PARAM: {
	//} break;
	//case CFG_EXPR_LOAD_GLOBAL: {
	//} break;
	//case CFG_EXPR_STORE_LOCAL: {
	//} break;
	//case CFG_EXPR_STORE_PARAM: {
	//} break;
	//case CFG_EXPR_STORE_GLOBAL: {
	//} break;
	case CFG_EXPR_CAST: {
		generateCfgExpr(expr->args[0], ctx);
	} break;
	case CFG_EXPR_SIZEOF:
	case CFG_EXPR_ALIGNOF:
	case CFG_EXPR_ERROR:
	case CFG_EXPR_ACCESS_DIRECT:
	case CFG_EXPR_ACCESS_PTR:
	default: {
		printError(expr->ast, "Unexpected control-flow expression %s", getStringCfgExprKind(expr->kind));
	} break;
	}

	ctx->expectedLocation = REG_UNKNOWN;
}

static void generateCfgBlockExpr(CfgExprNode* expr, CodeGenerationContext* ctx)
{
	emitSourceRef(ctx, expr->ast);
	
	resetMachineState(ctx->state);
	generateCfgExpr(expr, ctx);
}

static void generateCfgBlock(CfgNode* node, CodeGenerationContext* ctx)
{
	emitLabel(ctx, node->id);

	traverseLinkedList(node->exprs, (action2)generateCfgBlockExpr, ctx);

	if (node->conditionalBranch != NULL)
	{
		LabelInfo* label = makeBlockLabel(ctx, node->conditionalBranch->id);
		emitInstructionCondJump(ctx, INSN_BRANCH_NOT_EQUAL, ctx->resultLocation, REG_INT_ZERO, label);
	}

	if (node->defaultBranch != NULL)
	{
		LabelInfo* label = makeBlockLabel(ctx, node->defaultBranch->id);
		emitInstructionImmJump(ctx, INSN_JUMP, label);
	}
}

static void generateFunction(Function* func, CodeGenerationContext* ctx)
{
	if (func->isExternal)
	{
		LabelInfo* label;
		makeLabel(ctx->unit, func->name, &label);
		label->isExternal = true;
		return;
	}

	Routine* routine = allocStruct(Routine);
	routine->id = ctx->unit->routines->count;
	routine->flow = createLinkedList();
	routine->symbol = createSymbol(ctx->unit, func->isPublic ? SYMBOL_PUBLIC_FUNCTION : SYMBOL_PRIVATE_FUNCTION, func->name, -1, 1, routine);
	routine->symbol->routine = routine;
	addLastLinkedListItem(ctx->unit->routines, routine);
	ctx->routine = routine;
	makeLabel(ctx->unit, NULL, &ctx->exitRoutineLabel);

	if (func->body != NULL)
	{
		// the default stack frame
		emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, REG_INT_SP, REG_INT_SP, -16);	// addi    sp, sp, -16
		emitInstructionStoreLoad(ctx, INSN_STORE_64, REG_INT_RA, 8, REG_INT_SP);		// sd      ra,8(sp)        #,
		emitInstructionStoreLoad(ctx, INSN_STORE_64, REG_INT_S0FP, 0, REG_INT_SP);		// sd      s0, 0(sp)        #,
		emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, REG_INT_S0FP, REG_INT_SP, 16);  // addi    s0, sp, 16        #, ,
		emitInstructionNoOperands(ctx, INSN_NOP);

		ctx->state = prepareMachineState(func);
		
		if (func->body->vars->places->count > 0)
		{
			// introduce locals
			emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, REG_INT_SP, REG_INT_SP, ctx->state->evalStackOffset);
			emitInstructionNoOperands(ctx, INSN_NOP);
		}

		traverseLinkedList(func->body->nodes, (action2)generateCfgBlock, ctx);

		emitLabelImpl(ctx, ctx->exitRoutineLabel);

		if (func->body->vars->places->count > 0)
		{
			// cleanup locals
			emitInstructionNoOperands(ctx, INSN_NOP);
			emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, REG_INT_SP, REG_INT_SP, -ctx->state->evalStackOffset);
		}

		releaseMachineState(ctx->state);
		ctx->state = NULL;
		
		emitInstructionNoOperands(ctx, INSN_NOP);
		// emitInstructionIRegToIReg(ctx, INSN_MOVE, REG_INT_A0, REG_INT_A5);			// mv      a0, a5   #, <retval>
		emitInstructionStoreLoad(ctx, INSN_LOAD_64, REG_INT_RA, 8, REG_INT_SP);			// ld      ra, 8(sp)                #,
		emitInstructionStoreLoad(ctx, INSN_LOAD_64, REG_INT_S0FP, 0, REG_INT_SP);		// ld      s0, 0(sp)                #,
		emitInstructionImmIRegToIReg(ctx, INSN_ADD_IMM, REG_INT_SP, REG_INT_SP, 16);	// addi    sp, sp, 16        #, ,
		emitInstructionDirectJump(ctx, INSN_JUMP_REG, REG_INT_RA);						// jr      ra              #
	}

	ctx->routine = NULL;
	ctx->exitRoutineLabel = NULL;
}

Module* generate(ProgramUnit* model)
{
	Module* result = allocStruct(Module);
	result->sourceName = model->sourceFileName;
	result->labelsByName = createRbTreeByString();
	result->routines = createLinkedList();
	result->symbols = createLinkedList();
	result->symbolsByName = createRbTreeByString();
	
	CodeGenerationContext context = {
		.model = model,
		.unit = result,
		.routine = NULL,
		.state = NULL
	};

	traverseLinkedList(model->globalVars->places, (action2)generateGlobalVar, &context);

	traverseLinkedList(model->functionDefinitions, (action2)generateFunction, &context);

	return result;
}

static void serializeFlowItem(InsnFlowItem* item, FILE* out)
{
	switch (item->kind)
	{
	case FLOW_EMPTY: /* do nothing */ break;
	case FLOW_LABEL: {
		fprintf(out, "%s:", item->label->name);
	} break;
	case FLOW_SOURCE_REF: {
		fprintf(out, ".line %d", item->source->fromLoc.line);
	} break;
	case FLOW_INSTRUCTION: {
		fprintf(out, "\t\t");

		InstructionDescription* descr = item->instruction->descr;
		for (int i = 0; i < descr->mnemonicPartsCount; i++)
		{
			switch (descr->mnemonicParts[i].kind)
			{
			case MNEMONIC_PART_STRING: fprintf(out, "%s", descr->mnemonicParts[i].string); break;
			case MNEMONIC_PART_OPERAND: {
				int opndIndex = descr->mnemonicParts[i].operandIndex;
				switch (descr->operands[opndIndex].kind)
				{
				case OPND_INT_REG:
				case OPND_FP_REG: {
					fprintf(out, "%s", getStringRegisterId(item->instruction->operands[opndIndex].reg));
				} break;
				case OPND_IMMEDIATE: {
					fprintf(out, "%d", item->instruction->operands[opndIndex].immediate);
				} break;
				case OPND_DATA_LABEL:
				case OPND_CODE_LABEL: {
					fprintf(out, "%s", item->instruction->operands[opndIndex].label->name);
					if (item->instruction->operands[opndIndex].label->isExternal)
						fprintf(out, "@plt");
				} break;
				default: printError(NULL, "Unexpected instruction operand kind kind %s", getStringOperandKind(descr->operands[opndIndex].kind)); break;
				}
			} break;
			default: printError(NULL, "Unexpected mnemonic format part kind %s", getStringInstructionMnemonicPartKind(descr->mnemonicParts[i].kind)); break;
			}
		}
	} break;
	default: printError(NULL, "Unexpected instructions flow item kind %s", getStringInstructionFlowItemKind(item->kind)); break;
	}

	if (item->comment != NULL)
	{
		if (item->kind != FLOW_EMPTY)
			fprintf(out, "\t\t");

		fprintf(out, "# %s", item->comment);
	}
	fprintf(out, "\n");
}

static void serializeModuleItem(SymbolInfo* symbol, FILE* out)
{
	fprintf(out, "\n");
	switch (symbol->kind)
	{
	case SYMBOL_PRIVATE_FUNCTION: {
		fprintf(out, "\t\t.text\n");
		fprintf(out, "\t\t.align\t%d\n", symbol->alignment);
		fprintf(out, "\t\t.type\t%s, @function\n", symbol->label->name);
		fprintf(out, "%s:\n", symbol->label->name);
		traverseLinkedList(symbol->routine->flow, (action2)serializeFlowItem, out);
		fprintf(out, "\t\t.size\t%s, . - %s\n", symbol->label->name, symbol->label->name);
	} break;
	case SYMBOL_PUBLIC_FUNCTION: {
		fprintf(out, "\t\t.text\n");
		fprintf(out, "\t\t.align\t%d\n", symbol->alignment);
		fprintf(out, "\t\t.global\t%s\n", symbol->label->name);
		fprintf(out, "\t\t.type\t%s, @function\n", symbol->label->name);
		fprintf(out, "%s:\n", symbol->label->name);
		traverseLinkedList(symbol->routine->flow, (action2)serializeFlowItem, out);
		fprintf(out, "\t\t.size\t%s, . - %s\n", symbol->label->name, symbol->label->name);
	} break;
	case SYMBOL_PRIVATE_VARIABLE: {
		fprintf(out, "\t\t.bss\n");
		fprintf(out, "\t\t.align\t%d\n", symbol->alignment);
		fprintf(out, "\t\t.local\t%s\n", symbol->label->name);
		fprintf(out, "\t\t.comm\t%s, %d, %d\n", symbol->label->name, symbol->size, symbol->alignment);
		fprintf(out, "\t\t.align\t%d\n", symbol->alignment);
		fprintf(out, "\n");
	} break;
	case SYMBOL_PUBLIC_VARIABLE: {
		fprintf(out, "\t\t.global %s\n", symbol->label->name);
		fprintf(out, "\t\t.bss\n");
		fprintf(out, "\t\t.align\t%d\n", symbol->alignment);
		fprintf(out, "\t\t.type\t%s, @object\n", symbol->label->name);
		fprintf(out, "\t\t.size\t%s, %d\n", symbol->label->name, symbol->size);
		fprintf(out, "%s:\n", symbol->label->name);
		fprintf(out, "\t\t.zero\t%d\n", symbol->size);
		fprintf(out, "\n");
	} break;
	case SYMBOL_PRIVATE_CONSTANT: {
		fprintf(out, "\t\t.section\t.rodata\n");
		fprintf(out, "\t\t.align\t%d\n", symbol->alignment);
		fprintf(out, "%s:\n", symbol->label->name);
		fprintf(out, "\t\t.byte ");
		for (int i = 0; i < symbol->size; i++)
		{
			fprintf(out, "%d, ", symbol->rawData[i]);
		}
		fprintf(out, "0\n\n");
	} break;
	default: printError(NULL, "Unexpected symbol kind %s", getStringSymbolKind(symbol->kind)); break;
	}
	fprintf(out, "\n");
}

void serialize(Module* unit, FILE* out)
{
	fprintf(out, "\t\t.file \"%s\"\n", unit->sourceName);
	fprintf(out, "\t\t.option pic\n");
	traverseLinkedList(unit->symbols, (action2)serializeModuleItem, out);
}
