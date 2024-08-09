#ifndef EXECUTE_H
#define EXECUTE_H

typedef enum {
    ALU_ADD,
    ALU_SUB,
    ALU_AND,
    ALU_OR,
    ALU_XOR,
    ALU_SLT,
    ALU_SLTU,
    ALU_CMP,
    ALU_LSHIFT,
    ALU_RSHIFT,
    ALU_ARSHIFT
} ALUOp;

typedef struct {
    ALUOp aluop;
    int left;
    int right;
    int result;
} Instruction;

int perform_alu_operation(ALUOp aluop, int left, int right);
void execute_instruction(Instruction* inst);

#endif // EXECUTE_H
