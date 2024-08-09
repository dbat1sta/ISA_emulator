#include "execute.h"

int perform_alu_operation(ALUOp aluop, int left, int right) {
    switch (aluop) {
        case ALU_ADD:
            return left + right;
        case ALU_SUB:
            return left - right;
        case ALU_AND:
            return left & right;
        case ALU_OR:
            return left | right;
        case ALU_XOR:
            return left ^ right;
        case ALU_SLT:
            return (left < right) ? 1 : 0;
        case ALU_SLTU:
            return ((unsigned int)left < (unsigned int)right) ? 1 : 0;
        case ALU_CMP:
            return (left == right) ? 0 : (left < right) ? -1 : 1;
        case ALU_LSHIFT:
            return left << right;
        case ALU_RSHIFT:
            return (unsigned int)left >> right;
        case ALU_ARSHIFT:
            return left >> right;
        default:
            return 0;
    }
}

void execute_instruction(Instruction* inst) {
    inst->result = perform_alu_operation(inst->aluop, inst->left, inst->right);
}
