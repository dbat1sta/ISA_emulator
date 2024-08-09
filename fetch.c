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

uint8_t memory[1024];  // Example memory size, adjust as needed

void fetch_instruction(uint32_t pc, Instruction *instruction) {
    if (pc + 4 <= sizeof(memory)) {
        memcpy(&(instruction->inst), &memory[pc], 4);
    } else {
        fprintf(stderr, "Program counter out of bounds\n");
    }
}

int main() {
    // Set up an example program counter
    uint32_t pc = 0;
    // Initialize instruction structure
    Instruction instruction;

    // Example code to initialize memory and set the stack pointer
    // Adjust according to your actual initialization requirements
    uint32_t stack_pointer = sizeof(memory);

    // Example of how to call the fetch_instruction function
    fetch_instruction(pc, &instruction);

    printf("Fetched instruction: 0x%08x\n", instruction.inst);

    return 0;
}

