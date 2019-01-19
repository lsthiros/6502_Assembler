#include "ParseTree.h"

typedef struct {
    unsigned long key;
    char *value;
} *Record;

/* sdbm hash function */
static unsigned long sdbm(uint8_t *str) {
    unsigned long hash = 0;
    int c;

    while (c = *str++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}
