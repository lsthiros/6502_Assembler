#ifndef EMITTER_H
#define EMITTER_H

#include "OpCodeDefs.h"
#include "ParseTree.h"
#include "LinkedList.h"

#include <stdint.h>

typedef struct ByteCode {
    unsigned int location;
    OpCodeType type;
    unsigned int jumpLocation;
    char *jumpLabel;
    unsigned int length;
    uint8_t code[3];
} ByteCode;

int emitProgram(OpList *list, LinkedList *program);
void printByteCode(ByteCode *code);

#endif