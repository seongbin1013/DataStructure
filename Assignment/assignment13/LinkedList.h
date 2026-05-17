#include <stdio.h>
#include <stdlib.h>

typedef struct pointType {
	int x;
	int y;
	struct pointType* next;
} PointType;

typedef struct linkedList {
	struct pointType* head;
	int size;
} LinkedList;

extern LinkedList* createLinkedList();
extern int destroyLinkedList(LinkedList* li);
extern int isEmptyLinkedList(LinkedList* li);
extern int sizeLinkedList(LinkedList* li);

extern LinkedList* insertFirstLinkedList(LinkedList* li, PointType item);
extern LinkedList* insertLastLinkedList(LinkedList* li, PointType item);
extern LinkedList* insertItemLinkedList(LinkedList* li, PointType* pre, PointType item);
extern LinkedList* insertAtLinkedList(LinkedList* li, int at, PointType item);

extern PointType deleteAtLinkedList(LinkedList* li, int at);
extern PointType deleteFirstLinkedList(LinkedList* li);
extern PointType deleteLastLinkedList(LinkedList* li);

extern int printLinkedList(LinkedList* li);