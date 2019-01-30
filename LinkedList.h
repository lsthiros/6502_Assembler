#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedListNode {
    void *data;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode *head;
    LinkedListNode **tail;
    unsigned int length;
} LinkedList;

typedef struct LinkedListIterator {
    LinkedList *list;
    LinkedListNode **current;
    unsigned int position;
} LinkedListIterator;

void initLinkedList(LinkedList *list);
void linkedListInsert(LinkedList *list, void *item);
void linkedListDestroy(LinkedList *list);

void initLinkedListIterator(LinkedListIterator *iterator, LinkedList *list);
int linkedListIteratorNext(LinkedListIterator *iterator, void **data);

#endif