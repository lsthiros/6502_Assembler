#include "ParserPrimitives.h"

#include <stdlib.h>
#include <stdio.h>

void printLiteralAddress(LiteralAddress *literal) {
    printf("LiteralAddress\n");
    printf("Zero Page: %s\n", (literal->isZp) ? "yes" : "no");
    printf("literal: %u\n", literal->literal);
}

void printAddressLocation(AddressLocation *location) {
    printf("AddressLocation\n");
    printf("Is Label: %s\n", location->isLabel ? "yes" : "no");
    if (location->isLabel) {
        printf("Label name: %s\n", location->val.label);
    } else {
        printLiteralAddress(location->val.literal);
    }
}

void printAddressCode(AddressCode *code) {
    printf("AddressCode\n");
    printf("Mode: %s\n", opAddressModeName(code->mode));
    if (code->location) {
        printAddressLocation(code->location);
    } else {
        printf("Code: None\n");
    }
}

void printOperation(Operation *op) {
    printf("Operation\n");
    printf("Type: %s\n", opName(op->type));
    printAddressCode(op->code);
    printf("Position: %u\n", op->position);
}
