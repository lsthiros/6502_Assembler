#include "HexWriter.h"

#include <stdlib.h>
#include <string.h>

static void writeRecord(HexWriter *writer);
static void putHex(char *buffer, unsigned int offset, uint8_t byte);

static const uint8_t DataRecord = 0x00;
static const char charLookup[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};


void initHexWriter(HexWriter *writer) {
    memset(writer, 0x00, sizeof(HexWriter));
}

int writeHexFile(HexWriter *writer, LinkedList *prog) {
    LinkedListIterator iterator;
    ByteCode *code;
    int idx;

    initLinkedListIterator(&iterator, prog);

    writer->recordType = DataRecord;
    writer->address = 0;
    while ((linkedListIteratorNext(&iterator, (void**)&code))) {
        for (idx = 0; idx < code->length; idx++) {
            writer->data[writer->dataSize++] = code->code[idx];
            if (writer->dataSize == 16) {
                writeRecord(writer);
                writer->address += writer->dataSize;
                writer->dataSize = 0;
            }
        }
    }
    writeRecord(writer);

    writer->recordType = 0x01;
    writer->address = 0;
    writer->dataSize = 0;
    writeRecord(writer);
    return 0;
}

static void putHex(char *buffer, unsigned int offset, uint8_t byte) {
    buffer[offset] = charLookup[(byte >> 4) & 0x0F];
    buffer[offset + 1] = charLookup[byte & 0x0F];
}


static void writeRecord(HexWriter *writer) {
    int recordLength = 1 + 2 + 4 + 2 + (writer->dataSize * 2) + 2 + 1;
    int idx;
    char *record = malloc(recordLength + 1);
    uint8_t checksum = 0;

    record[0] = ':';
    putHex(record, 1, writer->dataSize);
    putHex(record, 3, ((writer->address & 0xFF00) >> 8));
    putHex(record, 5, (writer->address & 0x00FF));
    putHex(record, 7, writer->recordType);

    checksum += writer->dataSize + ((writer->address & 0xFF00) >> 8) +
        (writer->address & 0x00FF) + writer->recordType;

    for (idx = 0; idx < writer->dataSize; idx++) {
        putHex(record, 9 + (idx * 2), writer->data[idx]);
        checksum += writer->data[idx];
    }
    checksum = (~checksum + 1);

    putHex(record, recordLength - 3, checksum);
    record[recordLength - 1] = '\n';
    record[recordLength] = '\0';
    printf("%s", record);
    free(record);
}
