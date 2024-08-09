#include <stdio.h>
#include <stdint.h>

#define NUM_REGS 32

uint32_t registers[NUM_REGS];
uint8_t memory[4096];

uint32_t fetch_instruction(uint32_t pc) {
    return *(uint32_t *)&memory[pc];
}

void decode(uint32_t instruction, uint8_t *opcode, uint8_t *rd, uint8_t *funct3,
            uint8_t *rs1, uint8_t *rs2, uint8_t *funct7, int32_t *imm, char *type) {
    *opcode = instruction & 0x7F;
    
   
    switch (*opcode) {
        case 0x33: // R-type
            *type = 'R';
            *rd = (instruction >> 7) & 0x1F;
            *funct3 = (instruction >> 12) & 0x7;
            *rs1 = (instruction >> 15) & 0x1F;
            *rs2 = (instruction >> 20) & 0x1F;
            *funct7 = (instruction >> 25) & 0x7F;
            break;
        
        case 0x13: // I-type
        case 0x03:
        case 0x67:
            *type = 'I';
            *rd = (instruction >> 7) & 0x1F;
            *funct3 = (instruction >> 12) & 0x7;
            *rs1 = (instruction >> 15) & 0x1F;
            *imm = (int32_t)(instruction >> 20); 
            break;
        
        case 0x23: // S-type
            *type = 'S';
            *funct3 = (instruction >> 12) & 0x7;
            *rs1 = (instruction >> 15) & 0x1F;
            *rs2 = (instruction >> 20) & 0x1F;
            *imm = ((instruction >> 7) & 0x1F) | ((instruction >> 20) & 0xFE0);
            if (*imm & 0x800) *imm |= 0xFFFFF000; 
            break;
        
        case 0x63: // B-type
            *type = 'B';
            *funct3 = (instruction >> 12) & 0x7;
            *rs1 = (instruction >> 15) & 0x1F;
            *rs2 = (instruction >> 20) & 0x1F;
            *imm = ((instruction >> 7) & 0x1E) | ((instruction >> 20) & 0x7E0) |
                   ((instruction >> 7) & 0x800) | ((instruction >> 20) & 0x8000);
            if (*imm & 0x1000) *imm |= 0xFFFFE000; 
            break;
        
        case 0x37: // U-type
        case 0x17:
            *type = 'U';
            *rd = (instruction >> 7) & 0x1F;
            *imm = (instruction & 0xFFFFF000);
            break;
        
        case 0x6F: // J-type
            *type = 'J';
            *rd = (instruction >> 7) & 0x1F;
            *imm = ((instruction >> 21) & 0x3FF) | ((instruction >> 20) & 0x400) |
                   ((instruction >> 12) & 0x80000) | (instruction & 0xFF000);
            if (*imm & 0x100000) *imm |= 0xFFE00000; 
            break;
        
        default:
            *type = 'U';
            break;
    }
}

int main() {
    uint32_t pc = 0;
    uint8_t opcode, rd, funct3, rs1, rs2, funct7;
    int32_t imm;
    char type;

    memory[0] = 0x93; memory[1] = 0x00; memory[2] = 0x10; memory[3] = 0x00;

    while (pc < sizeof(memory)) {
        uint32_t instruction = fetch_instruction(pc);
        decode(instruction, &opcode, &rd, &funct3, &rs1, &rs2, &funct7, &imm, &type);
        pc += 4;
    }

    return 0;
}
