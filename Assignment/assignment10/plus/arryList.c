#include <stdio.h>
#include <stdlib.h>
#include "arrayList.h"

arrayList* createArrayList(int size) {
	arrayList* al;
	al = (arrayList*)malloc(sizeof(arrayList));
	al->data = (elementArrayList*)malloc(
		sizeof(elementArrayList) * size);
	al->size = 0;
	al->capacity = size;
	return al;
}

void destroyArrayList(arrayList* al) {
	free(al->data);
	free(al);
}

int isEmptyArrayList(arrayList* al) {
	if (al->size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int isFullArrayList(arrayList* al) {
	if (al->size == al->capacity) {
		return 1;
	}
	else {
		return 0;
	}
}

int sizeArrayList(arrayList* al) {
	return al->size;
}

int insertArrayList(arrayList* al,
	int pos, elementArrayList item) {
	if (pos < 0 || pos > al->size) {
		return 0;
	}
	/* [버그 수정 1]
	   원본: for (int i = al->size; i >= pos; i--)
	         al->data[i + 1] = al->data[i];
	   i = al->size일 때 data[size+1] 에 접근 -> 범위 밖 쓰기 (undefined behavior)
	   수정: i = al->size - 1 부터 시작 */
	for (int i = al->size - 1; i >= pos; i--) {
		al->data[i + 1] = al->data[i];
	}
	al->data[pos] = item;
	al->size++;
	return 1;
}

elementArrayList deleteArrayList(
	arrayList* al, int pos) {
	/* [버그 수정 2]
	   원본: 범위 초과 시 아무 처리 없이 진행 -> 쓰레기값 반환 위험
	   수정: 빈 elementArrayList 반환 처리 추가 */
	if (pos < 0 || pos > al->size - 1) {
		elementArrayList empty = { 0, 0, 0 };
		return empty;
	}
	elementArrayList item = al->data[pos];
	for (int i = pos; i < al->size - 1; i++) {
		al->data[i] = al->data[i + 1];
	}
	al->size--;
	return item;
}

int initArrayList(arrayList* al) {
	for (int i = al->size - 1; i >= 0; i--) {
		deleteArrayList(al, i);
	}
	return 1; /* [버그 수정 3] 원본: 반환값 없음 (int 함수인데 return 누락) */
}

elementArrayList getItemArrayList(
	arrayList* al, int pos) {
	return al->data[pos];
}

int replaceItemArrayList(arrayList* al,
	int pos, elementArrayList item) {
	if (pos < 0 || pos > al->size - 1) {
		return 0;
	}
	al->data[pos] = item;
	return 1;
}

void printArrayList(arrayList* al) {
	printf("희소 행렬 순차 리스트: ");
	printf("Cap: %d, size: %d\n", al->capacity, al->size);
	for (int i = 0; i < al->size; i++) {
		printf("(%d %d %d) ", al->data[i].row,
			al->data[i].col, al->data[i].value);
	}
	printf("\n");
}