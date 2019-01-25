#ifndef EMITTER_H
#define EMITTER_H

#include "OpCodeDefs.h"
#include <stdint.h>

typedef struct Program Program;

typedef struct ByteCode {
    unsigned int location;
    OpCodeType type;
    unsigned int jumpLocation;
    unsigned int length;
    uint8_t code[3];
} ByteCode;


#endif