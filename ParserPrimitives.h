#ifndef PARSER_DEFS_H
#define PARSER_DEFS_H
#include "OpCodeDefs.h"
#include <stdint.h>

typedef struct LiteralAddress LiteralAddress;
typedef struct AddressLocation AddressLocation;
typedef struct AddressCode AddressCode;
typedef struct Operation Operation;
typedef struct ParseContext ParseContext;

typedef struct LiteralAddress {
    uint8_t isZp;
    uint16_t literal;
} LiteralAddress;

typedef struct AddressLocation {
    uint8_t isLabel;
    union {
        char *label;
        LiteralAddress *literal;
    } val;
} AddressLocation;

typedef struct AddressCode {
    AddressMode mode;
    AddressLocation *location;
} AddressCode;

typedef struct Operation {
    OpCodeType type;
    AddressCode *code;
    unsigned int position;
} Operation;

#endif
