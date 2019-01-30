#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include "ParserPrimitives.h"
#include "LinkedList.h"

typedef struct OpList OpList;

OpList *initOpList();
void addOperation(OpList *list, Operation *op);
uint8_t searchLabels(OpList *list, char *key, int *ret);
void insertLabel(OpList *list, char *key, int value);
LinkedList *getOpListOps(OpList *list);

#endif
