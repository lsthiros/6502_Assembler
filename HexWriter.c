#include "HexWriter.h"

typedef struct HexWriter {
    uint8_t recordType;
    uint16_t address;
    uint8_t dataSize;
    uint8_t data[16];
} hexWriter;

int writeHexFile(HexWriter *writer, Program *prog) {
    beginIterateProgram(prog);
    ByteCode *code;
    int idx;

    writer->recordType = 0x00;
    writer->address = 0;
    while ((code = iterateProgram(prog))) {
        for (idx = 0; idx < code->length; idx++) {
            writer->data[writer->dataSize++] = code->code[idx];
            if (writer->dataSize == 16)
                writeRecord(writer);
        }
    }

    return 0;
}

static const charLookup[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};
#define PUT_HEX(BUFFER, OFFSET, BYTE) \
    BUFFER[OFFSET] = charLookup[BYTE & 0x0F]; \
    BUFFER[OFFSET + 1] = charLookup[(BYTE >> 4) & 0x0F];

static const uint8_t DataRecord = 0x00;

static void writeRecord(HexWriter *writer) {
    int recordLength = 1 + 2 + 4 + 2 + (writer->dataSize * 2) + 2 + 1;
    char *record = malloc(recordLength + 1);
    uint8_t checksum = 0;

    record[0] = ':';
    PUT_HEX(record, 1, writer->dataSize);
    PUT_HEX(record, 3, ((writer->address & 0xFF00) >> 8));
    PUT_HEX(record, 5, (writer->address & 0x00FF));
    PUT_HEX(record, 7, DataRecord);
}