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
            if (writer->dataSize == 16) {
                writeRecord(writer);
                writer->dataSize = 0;
            }
        }
    }

    return 0;
}

static const charLookup[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

static void putHex(uint8_t *buffer, unsigned int offset, uint8_t byte) {
    buffer[offset] = charLookup[byte & 0x0F];
    buffer[offset + 1] = charLookup[(byte >> 4) & 0x0F];
}

static const uint8_t DataRecord = 0x00;

static void writeRecord(HexWriter *writer) {
    int recordLength = 1 + 2 + 4 + 2 + (writer->dataSize * 2) + 2 + 1;
    int idx;
    char *record = malloc(recordLength + 1);
    uint8_t checksum = 0;

    record[0] = ':';
    putHex(record, 1, writer->dataSize);
    putHex(record, 3, ((writer->address & 0xFF00) >> 8));
    putHex(record, 5, (writer->address & 0x00FF));
    putHex(record, 7, DataRecord);

    checksum += writer->dataSize + ((writer->address & 0xFF00) >> 8) +
        (writer->address & 0x00FF) + DataRecord;

    for (idx = 0; idx < writer->dataSize; idx++) {
        putHex(record, 9 + (idx * 2), writer->data[idx]);
        checksum += writer->data[idx];
    }
    checksum = (~checksum + 1);

    putHex(record, recordLength - 3, checksum);
    record[recordLength - 1] = '\n';
    record[recordLength] = '\0';
    printf(record);
    free(record);
}