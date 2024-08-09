#include "memory.h"

void memory_access(Instruction* inst, uint8_t* memory) {
    if (inst->memop == MEMOP_STORE) {
        switch (inst->load_type) {
            case STORE_BYTE:
                *((uint8_t*)(memory + inst->result)) = (uint8_t)inst->strval;
                break;
            case STORE_HALF:
                *((uint16_t*)(memory + inst->result)) = (uint16_t)inst->strval;
                break;
            case STORE_WORD:
                *((uint32_t*)(memory + inst->result)) = inst->strval;
                break;
            default:
                break;
        }
    } else if (inst->memop == MEMOP_LOAD) {
        switch (inst->load_type) {
            case LOAD_BYTE:
                inst->result = (int8_t)(*(int8_t*)(memory + inst->result)); 
                break;
            case LOAD_HALF:
                inst->result = (int16_t)(*(int16_t*)(memory + inst->result)); 
                break;
            case LOAD_BYTE_U:
                inst->result = *(uint8_t*)(memory + inst->result); 
                break;
            case LOAD_HALF_U:
                inst->result = *(uint16_t*)(memory + inst->result); 
                break;
            case LOAD_WORD:
                inst->result = *(uint32_t*)(memory + inst->result); 
                break;
            default:
                break;
        }
    }
}
