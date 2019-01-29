#include "LinkedList.h"

#include <stdlib.h>

void initLinkedList(LinkedList *list) {
    list->head = NULL;
    list->tail = &list->head;
    list->length = 0;
}

void linkedListInsert(LinkedList *list, void *item) {
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->data = item;

    *(list->tail) = node;
    list->tail = &node->next;
}

void linkedListDestroy(LinkedList *list) {
    LinkedListNode *current = list->head;
    LinkedListNode *tmp;

    while (current) {
        tmp = current->next;
        free(current);
        current = tmp;
    }
}

void initLinkedListIterator(LinkedListIterator *iterator, LinkedList *list) {
    iterator->list = list;
    iterator->current = &list->head;
    iterator->position = 0;
}

int linkedListIteratorNext(LinkedListIterator *iterator, void **data) {
    LinkedListNode *node;

    node = *(iterator->current);

    if (node) {
        iterator->current = &node->next;
        *data = node->data;
        iterator->position++;
        return 1;
    }
    return 0;
}
