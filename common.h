#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

// memory operations
typedef enum {
    MEMOP_NONE,
    MEMOP_LOAD,
    MEMOP_STORE
} MemOp;

//  load and store types for mem operations
typedef enum {
    LOAD_BYTE,
    LOAD_HALF,
    LOAD_BYTE_U,
    LOAD_HALF_U,
    LOAD_WORD,
    STORE_BYTE,
    STORE_HALF,
    STORE_WORD
} MemLoadStoreType;

typedef enum {
    ALU_ADD,
    ALU_SUB,
    ALU_MUL,
    ALU_DIV,
    ALU_CMP,
    ALU_AND,
    ALU_OR,
    ALU_XOR,
    ALU_LEFTSHIFT,
    ALU_RIGHTSHIFT_LOGICAL,
    ALU_RIGHTSHIFT_ARITHMETIC
} AluOp;

typedef struct {
    uint32_t pc;         // Program counter
    uint32_t instr;      // Instruction
    int aluop;           // ALU operation
    int memop;           // Memory operation
    int load_type;       // Load or store type for memory operations
    int result;          // Result of the operation
    int strval;          // Value to store in memory
    int left;            // Left operand
    int right;           // Right operand
} Instruction;

#endif // COMMON_H
