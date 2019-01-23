#include "OpCodeLookup.h"
    ABS_X = 0,
    ABS_Y,
    ACCUMULATOR,
    IMMEDIATE,
    IMPLIED,
    INDEX_IND,
    IND_INDEX,
    INDIRECT,
    INDIRECT_ABS,
    REL_ABS_ZP,
    ZP_X,
    ZP_Y

const unsigned int length[] = {
    3, /* ABS_X */
    3, /* ABS_Y */
    1, /* ACCUMULATOR */
    2, /* IMMEDIATE */
    1, /* IMPLIED */
    2, /* INDEX_IND */
    2, /* IND_INDEX */
    /* INDIRECT */
    /* INDIRECT_ABS */
    /* REL_ABS_ZP */
    /* ZP_X */
    /* ZP_Y */
}

unsigned int opCodeLength(AddressMode mode);
