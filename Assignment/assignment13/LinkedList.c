#include "LinkedList.h"

LinkedList* createLinkedList() {
	LinkedList* li;
	li = (LinkedList*)malloc(sizeof(LinkedList));
	li->head = NULL;
	li->size = 0;

	return li;
}

int destroyLinkedList(LinkedList* li) {
	if (li == NULL) {
		return 0;
	}

	while (li->size > 0) {
		int temp;
		deleteAtLinkedList(li, 0, &temp);
	}

	free(li);
	return 1;
}

int isEmptyLinkedList(LinkedList* li) {
	return (li->size == 0);
}

int sizeLinkedList(LinkedList* li) {
	return li->size;
}

LinkedList* insertFirstLinkedList(LinkedList* li, int value) {
	NodeType* nPtr;
	nPtr = (NodeType*)malloc(sizeof(NodeType));
	nPtr->data = value;

	if (li->head == NULL) {
		nPtr->next = nPtr;
		nPtr->prev = nPtr;
		li->head = nPtr;
	}
	else {
		NodeType* tail;
		tail = li->head->prev;
		nPtr->next = li->head;
		nPtr->prev = tail;
		tail->next = nPtr;
		li->head->prev = nPtr;
		li->head = nPtr;
	}

	li->size++;
	return li;
}

LinkedList* insertLastLinkedList(LinkedList* li, int value) {
	NodeType* nPtr;
	nPtr = (NodeType*)malloc(sizeof(NodeType));
	nPtr->data = value;

	if (li->head == NULL) {
		nPtr->next = nPtr;
		nPtr->prev = nPtr;
		li->head = nPtr;
	}
	else {
		NodeType* tail;
		tail = li->head->prev;
		nPtr->next = li->head;
		nPtr->prev = tail;
		tail->next = nPtr;
		li->head->prev = nPtr;
	}

	li->size++;
	return li;
}

LinkedList* insertAtLinkedList(LinkedList* li, int at, int value) {
	if (at < 0 || at > li->size) {
		printf("잘못된 위치입니다.\n");
		return li;
	}

	if (at == 0) {
		return insertFirstLinkedList(li, value);
	}

	if (at == li->size) {
		return insertLastLinkedList(li, value);
	}

	NodeType* current;
	current = li->head;

	for (int i = 0; i < at; i++) {
		current = current->next;
	}

	NodeType* nPtr;
	nPtr = (NodeType*)malloc(sizeof(NodeType));
	nPtr->data = value;
	nPtr->prev = current->prev;
	nPtr->next = current;
	current->prev->next = nPtr;
	current->prev = nPtr;

	li->size++;

	return li;
}

int deleteAtLinkedList(LinkedList* li, int at, int* deletedValue) {
	if (li->head == NULL) {
		printf("리스트가 비어 있습니다.\n");
		return 0;
	}

	if (at < 0 || at >= li->size) {
		printf("잘못된 위치입니다.\n");
		return 0;
	}

	NodeType* dPtr;
	dPtr = li->head;

	for (int i = 0; i < at; i++) {
		dPtr = dPtr->next;
	}

	*deletedValue = dPtr->data;

	if (li->size == 1) {
		li->head = NULL;
	}
	else {
		dPtr->prev->next = dPtr->next;
		dPtr->next->prev = dPtr->prev;

		if (at == 0) {
			li->head = dPtr->next;
		}
	}

	free(dPtr);
	li->size--;

	return 1;
}

int printLinkedList(LinkedList* li) {
	if (li->head == NULL) {
		printf("리스트가 비어 있습니다.\n");
		return 0;
	}

	NodeType* current;
	current = li->head;

	printf("리스트 크기: %d\n", li->size);
	printf("전체 목록: ");

	for (int i = 0; i < li->size; i++) {
		printf("%d", current->data);

		if (i != li->size - 1) {
			printf(" -> ");
		}
		current = current->next;
	}

	printf("\n");
	return 1;
}