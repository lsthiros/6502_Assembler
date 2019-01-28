#include "Emitter.h"
#include "utils/OpCodeTable.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct ByteCodeNode {
    ByteCode *code;
    struct ByteCodeNode *next;
} ByteCodeNode;

typedef struct Program {
    ByteCodeNode *head;
    ByteCodeNode *tail;
} Program;

static int generateInstruction(Operation *op, OpList *list, ByteCode **ret);
static int getCode(OpCodeType type, AddressMode mode, uint8_t *ret);
static int isRelative(OpCodeType type);

void printByteCode(ByteCode *code) {
    int idx;

    printf("ByteCode\n");
    printf("location: %4.4X\n", code->location);
    printf("type: %s\n", opName(code->type));
    printf("jumpLocation: %4.4X\n", code->jumpLocation);
    printf("jumpLabel: %s\n", code->jumpLabel ? code->jumpLabel : "N/A");
    printf("length: %u\n", code->length);
    printf("code:");

    for (idx = 0; idx < code->length; idx++) {
        printf(" %2.2X", code->code[idx]);
    }
    printf("\n");
}

int emitProgram(OpList *list, Program **ret) {
    Operation *op;
    ByteCode *codeToEmit;
    int error = 0;

    beginIteration(list);
    op = iterateOpList(list);

    fprintf(stderr, "Iterating through oplist\n");
    while (op && !error) {
        fprintf(stderr, "Iterating through oplist\n");
        if (!(error = generateInstruction(op, list, &codeToEmit))) {
            printByteCode(codeToEmit);
            op = iterateOpList(list);
        }
    }
}

static int generateInstruction(Operation *op, OpList *list, ByteCode **ret) {
    ByteCode *codeToEmit;
    AddressMode addressMode;
    uint8_t opByte, status;
    int8_t offset;
    unsigned int fullAddress;

    codeToEmit = malloc(sizeof(ByteCode));
    codeToEmit->type = op->type;
    addressMode = op->code->mode;

    if (!getCode(op->type, op->code->mode, &(codeToEmit->code[0]))) {
        fprintf(stderr, "Failed to construct instruction\n");
        printOperation(op);
        free(codeToEmit);
        return 1;
    }
    /* Abs X and Abs Y: put the full address at the end */
    /* Absolute: put the address at the end */
    /* Indirect absolute: Only used by JMP */
    if (addressMode == ABS_X
    || addressMode == ABS_Y
    || addressMode == ABSOLUTE
    || addressMode == INDIRECT_ABS) {
        if (op->code->location->isLabel) {
            status = searchLabels(list, op->code->location->val.label, &fullAddress);
            assert(status);
        } else {
            fullAddress = op->code->location->val.literal->literal;
        }
        codeToEmit->code[1] = (uint8_t)((fullAddress & 0xFF00) >> 8);
        codeToEmit->code[2] = (uint8_t)(fullAddress & 0xFF);
    }
    /* Relative: REL_ZP && isRelative. if its a label, calculate that, otherwise use the value */
    else if (addressMode == REL_ZP && isRelative(op->type)) {
        /* TODO remove assert. Error needs to be handled */
        if (op->code->location->isLabel) {
            status = searchLabels(list, op->code->location->val.label, &fullAddress);
            offset = (int8_t)(fullAddress - op->position);
        }
        else {
            offset = op->code->location->val.literal->literal;
        }

        codeToEmit->code[1] = (uint8_t)offset;
    }
    /* Immediate: Add one byte immediate */
    /* Index Indirect, Indirect Index: Just the offset byte */
    /* Zero Page X, Zero Page Y: Just the byte at the end */
    /* Zero page: REL_ZP && !isRelative */
    else if (addressMode == IMMEDIATE
    || addressMode == IND_INDEX
    || addressMode == INDEX_IND
    || addressMode == ZP_X
    || addressMode == ZP_Y
    || addressMode == REL_ZP) {
        assert(op->code->location);
        if (op->code->location->isLabel) {
            fprintf(stderr, "Cannot process a label on this instruction\n");
            printOperation(op);
            free(codeToEmit);
            return 1;
        }

        codeToEmit->code[1] = op->code->location->val.literal->literal;
    }
    /* Accumulator: essentially implied */
    /* Implied: nothing after the op */

    codeToEmit->length = opCodeLength(addressMode);
    *ret = codeToEmit;
    return 0;
}

static int getCode(OpCodeType type, AddressMode mode, uint8_t *ret) {
    uint8_t res = opLookupTable[type][mode];

    if (!res && type != BRK) {
        fprintf(stderr, "Emitter: %s has node code for addressing mode %s\n", opName(type), opAddressModeName(mode));
        return 0;
    }
    *ret = res;
    return 1;
}

static const OpCodeType relTypes[] = {
    BCC, BCS, BEQ, BMI, BNE, BPL, BVC, BVS
};

static const int numRels = 8;

static int isRelative(OpCodeType type) {
    int idx = 0;

    while(idx < numRels && type != relTypes[idx])
        idx++;

    return type == relTypes[idx];
}