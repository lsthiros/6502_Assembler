#include "ParserDefs.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
    uint8_t valid;
} Record;

typedef struct {
    unsigned int size;
    unsigned int filled;
    Record *records;
} Table;

typedef struct FirstPass {
    Operation *head;
    Operation *tail;
    Table *table;
} FirstPass;

static unsigned long sdbm(uint8_t *str);
static void innerEntry(Record *records, unsigned int size, char *key, int value);
Table *initTable();

static void innerEntry(Record *records, unsigned int size, char *key, int value) {
    unsigned long seed = sdbm(key) % size;
    Record *current = &(records[seed]);

    while (current->valid) {
        seed = (seed + 1) % size;
        current = &(current[seed]);
    }

    current->key = key;
    current->value = value;
    current->valid = 1;
}

Table *initTable() {
    Table *ret = malloc(sizeof(Table));
    ret->records = calloc(sizeof(Record), 128);
    ret->filled = 0;
    ret->size = 128;

    return ret;
}

uint8_t searchTable(Table *table, char *key, int *ret) {
    unsigned long seed = sdbm(key) % table->size;
    Record *current = &(table->records[seed]);

    while (current->valid && strcmp(key, current->key))
        current++;
    
    if (current->valid) {
        if (ret)
            *ret = current->value;
        return 1;
    }

    return 0;
}

static void rehash(Table *oldTable) {
    int idx;
    int newsize = oldTable->size * 2;
    Record *current;
    Record *newHash = calloc(sizeof(Record), newsize);

    for (idx = 0; idx < oldTable->size; idx++) {
        current = &(oldTable->records[idx]);
        if (current->valid) {
            innerEntry(newHash, newsize, current->key, current->value);
        }
    }

    free(oldTable->records);
    oldTable->records = newHash;
    oldTable->size = newsize;
}

void insertTable(Table *table, char *key, int value) {
    char *newKey = strdup(key);

    if (table->filled * 2 > table->size) {
        rehash(table);
    }

    innerEntry(table->records, table->size, newKey, value);
    table->filled++;
}

void destroyTable(Table *table) {
    free(table->records);
    free(table);
}

/* sdbm hash function */
static unsigned long sdbm(uint8_t *str) {
    unsigned long hash = 0;
    int c;

    while (c = *str++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}
