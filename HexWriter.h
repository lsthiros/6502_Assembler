#ifndef HEX_WRITER_H
#define HEX_WRITER_H

#include "Emitter.h"
#include <stdio.h>

typedef struct HexWriter HexWriter;
typedef int(*HexWriterSink)(char *);

HexWriter *initHexWriter(HexWriterSink sink);
int writeHexFile(HexWriter *writer, Program *prog);

#endif