#ifndef HEX_WRITER_H
#define HEX_WRITER_H

#include "Emitter.h"
#include "LinkedList.h"
#include <stdio.h>

typedef struct HexWriter {
    uint8_t recordType;
    uint16_t address;
    uint8_t dataSize;
    uint8_t data[16];
} HexWriter;

void initHexWriter(HexWriter *writer);
int writeHexFile(HexWriter *writer, LinkedList *prog);

#endif