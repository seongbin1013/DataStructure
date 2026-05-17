#include <stdio.h>
#include <stdlib.h>

typedef struct nodeType {
	int data;
	struct nodeType* next;
	struct nodeType* prev;
} NodeType;

typedef struct linkedList {
	NodeType* head;
	int size;
} LinkedList;

extern LinkedList* createLinkedList();
extern int destroyLinkedList(LinkedList* li);
extern int isEmptyLinkedList(LinkedList* li);
extern int sizeLinkedList(LinkedList* li);

extern LinkedList* insertFirstLinkedList(LinkedList* li, int value);
extern LinkedList* insertLastLinkedList(LinkedList* li, int value);
extern LinkedList* insertAtLinkedList(LinkedList* li, int at, int value);

extern int deleteAtLinkedList(LinkedList* li, int at, int* deleted);
extern int printLinkedList(LinkedList* li);