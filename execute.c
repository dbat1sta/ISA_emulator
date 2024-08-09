#include "execute.h"

int perform_alu_operation(ALUOp aluop, int operand1, int operand2) {
    switch (aluop) {
        case ALU_ADD:
            return operand1 + operand2;
        case ALU_SUB:
            return operand1 - operand2;
        case ALU_AND:
            return operand1 & operand2;
        case ALU_OR:
            return operand1 | operand2;
        case ALU_XOR:
            return operand1 ^ operand2;
        case ALU_SLT:
            return (operand1 < operand2) ? 1 : 0;
        case ALU_SLTU:
            return ((unsigned int)operand1 < (unsigned int)operand2) ? 1 : 0;
        default:
            return 0;
    }
}

int calculate_memory_address(int base_address, int offset) {
    return base_address + offset;
}

void execute_instruction(Instruction* inst) {
    if (inst->type == LOAD || inst->type == STORE) {
        inst->result = calculate_memory_address(inst->base_address, inst->offset);
    } else {
        inst->result = perform_alu_operation(inst->aluop, inst->operand1, inst->operand2);
    }
}
