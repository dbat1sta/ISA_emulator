#include <stdio.h>
#include <stdint.h>


#define NUM_REGS 32
uint32_t registers[NUM_REGS];
uint8_t memory[4096]; 


uint32_t fetch_instruction(uint32_t pc) {
    return *(uint32_t *)&memory[pc];
}


void decode(uint32_t instruction, uint8_t *opcode, uint8_t *rd, uint8_t *funct3, uint8_t *rs1, uint8_t *rs2, uint8_t *funct7, int32_t *imm, char *type) {
    *opcode = instruction & 0x7F;
    *rd = (instruction >> 7) & 0x1F;
    *funct3 = (instruction >> 12) & 0x7;
    *rs1 = (instruction >> 15) & 0x1F;
    *rs2 = (instruction >> 20) & 0x1F;
    *funct7 = (instruction >> 25) & 0x7F;

    if (*opcode == 0x33) { 
    } else if (*opcode == 0x13 || *opcode == 0x03 || *opcode == 0x67) { // I-type
        *type = 'I';
        *imm = (int32_t)(instruction >> 20);
    } else if (*opcode == 0x23) { 
        *type = 'S';
        *imm = ((instruction >> 7) & 0x1F) | ((instruction >> 20) & 0xFE0);
    } else if (*opcode == 0x63) { 
        *type = 'B';
        *imm = ((instruction >> 7) & 0x1E) | ((instruction >> 20) & 0x7E0) | ((instruction >> 7) & 0x800) | ((instruction >> 20) & 0x8000);
    } else if (*opcode == 0x37 || *opcode == 0x17) { 
        *type = 'U';
        *imm = (instruction & 0xFFFFF000);
    } else if (*opcode == 0x6F) { 
        *type = 'J';
        *imm = ((instruction >> 21) & 0x3FF) | ((instruction >> 20) & 0x400) | ((instruction >> 12) & 0x80000) | ((instruction & 0xFF000));
    } else {
        *type = 'U'; 
    }
}


void execute(uint8_t opcode, uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7, int32_t imm, char type) {
    switch (type) {
        case 'R':
            // 
            if (funct3 == 0x0 && funct7 == 0x00) { 
                registers[rd] = registers[rs1] + registers[rs2];
            } else if (funct3 == 0x0 && funct7 == 0x20) { 
                registers[rd] = registers[rs1] - registers[rs2];
            }
            break;
        case 'I':
        
            if (opcode == 0x13 && funct3 == 0x0) {
                registers[rd] = registers[rs1] + imm;
            }
            break;
        case 'S':
         
            if (opcode == 0x23 && funct3 == 0x0) { 
                *(uint32_t *)&memory[registers[rs1] + imm] = registers[rs2];
            }
            break;
        case 'B':
          
            if (opcode == 0x63 && funct3 == 0x0) { 
                if (registers[rs1] == registers[rs2]) {
           
                }
            }
            break;
        case 'U':
       
            if (opcode == 0x37) { // LUI
                registers[rd] = imm;
            }
            break;
        case 'J':

            if (opcode == 0x6F) { // JAL
                registers[rd] = pc + 4;
                pc += imm;
            }
            break;
        default:
            printf("Unknown instruction type\n");
            break;
    }
}

int main() {
  
    uint32_t pc = 0;

    // initialize memory with some instructions (little-endian)
    memory[0] = 0x93; memory[1] = 0x00; memory[2] = 0x10; memory[3] = 0x00; 

    while (pc < sizeof(memory)) {
        uint32_t instruction = fetch_instruction(pc);
        uint8_t opcode, rd, funct3, rs1, rs2, funct7;
        int32_t imm;
        char type;

        decode(instruction, &opcode, &rd, &funct3, &rs1, &rs2, &funct7, &imm, &type);
        execute(opcode, rd, funct3, rs1, rs2, funct7, imm, type);

        pc += 4;
    }

    return 0;
}
