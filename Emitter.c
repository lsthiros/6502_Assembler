#include "Emitter.h"

typedef struct ByteCodeNode {
    ByteCode *code;
    struct ByteCodeNode *next;
} ByteCodeNode;

typedef struct Program {
    ByteCodeNode *head;
    ByteCodeNode *tail;
} Program;

int emitProgram(OpList *list, Program **ret) {
    Operation *op;

    beginIteration(list);
}

static const OpCodeType relTypes[] = {
    BCC, BCS, BEQ, BMI, BNE, BPL, BVC, BVS
};

static int isRelative(OpCodeType type) {
    int idx = 0;

    while(idx < 8 && type != relTypes[idx])
        idx++;

    return type == relTypes[idx];
}