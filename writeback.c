#include "writeback.h"
#include "instruction.h"
#include <stdio.h>
#include <stdlib.h>

extern int32_t registers[32];
extern int32_t program_counter;

void handle_syscall() {
    int syscall_number = registers[17];
    switch (syscall_number) {
        case 0:
            exit(registers[10]);
        case 1:
            putchar(registers[10]);
            break;
        case 2:
            registers[10] = getchar();
            break;
        case 3:
            printf("Debug: a0 = %d\n", registers[10]);
            break;
        default:
            printf("Unknown system call: %d\n", syscall_number);
            break;
    }
}

void execute_writeback(Instruction *inst) {
    if (inst->opcode == ECALL) {
        handle_syscall();
    } else {
        if (inst->rd != 0) {
            registers[inst->rd] = inst->result;
        }
    }

    switch (inst->opcode) {
        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU:
            if (inst->branch_taken) {
                program_counter += inst->imm;
            } else {
                program_counter += 4;
            }
            break;
        case JAL:
            program_counter += inst->imm;
            break;
        default:
            program_counter += 4;
            break;
    }

    registers[0] = 0;
}
