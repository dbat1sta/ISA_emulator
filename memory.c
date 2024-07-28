#include "memory.h"

void memory_access(Instruction* inst, int* memory) {
    if (inst->memop == MEMOP_STORE) {
        switch (inst->load_type) {
            case STORE_BYTE:
                memory[inst->result] = (uint8_t)inst->strval;
                break;
            case STORE_HALF:
                memory[inst->result] = (uint16_t)inst->strval;
                break;
            case STORE_WORD:
                memory[inst->result] = inst->strval;
                break;
            default:
                break;
        }
    } else if (inst->memop == MEMOP_LOAD) {
        int loaded_value = memory[inst->result];
        switch (inst->load_type) {
            case LOAD_BYTE:
                loaded_value = (int8_t)loaded_value; // sign extends 8-bit 
                break;
            case LOAD_HALF:
                loaded_value = (int16_t)loaded_value; // sign extends 16-bit 
                break;
            case LOAD_BYTE_U:
                loaded_value = (uint8_t)loaded_value; // zero extends 8-bit 
                break;
            case LOAD_HALF_U:
                loaded_value = (uint16_t)loaded_value; // zero extends 16-bit 
                break;
            case LOAD_WORD:
                break;
            default:
                break;
        }
        inst->result = loaded_value;
    }
}
