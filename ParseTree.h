#ifndef PARSE_TREE_H
#define PARSE_TREE
#include "ParserDefs.h"

typedef struct OpList OpList;

OpList *initOpList();
void addOperation(OpList *list, Operation *op);
uint8_t searchLabels(OpList *list, char *key, int *ret);
void insertLabel(OpList *list, char *key, int value);

#endif