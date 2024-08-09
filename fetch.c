#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t inst;
    int32_t left;
    int32_t right;
    int32_t disp_strval;
    uint8_t rd;
    uint8_t memop;
    uint8_t aluop;
} Instruction;

uint8_t memory[1024];  
void fetch_instruction(uint32_t pc, Instruction *instruction) {
    if (pc + 4 <= sizeof(memory)) {
        memcpy(&(instruction->inst), &memory[pc], 4);
    } else {
        fprintf(stderr, "Program counter out of bounds\n");
    }
}

int main() {

    uint32_t pc = 0;

    Instruction instruction;

    
    uint32_t stack_pointer = sizeof(memory);


    fetch_instruction(pc, &instruction);

    printf("Fetched instruction: 0x%08x\n", instruction.inst);

    return 0;
}

