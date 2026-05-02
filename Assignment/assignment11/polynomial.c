#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "polynomial.h"

polynomial* createPolynomial(int capacity) {
	polynomial* po = (polynomial*)createArrayList(capacity);
	return po;
}

polynomial* addItemPolynomial(polynomial* po, elementType item) {
	int i;
	for (i = 0; i < sizeArrayList(po); i++) {
		if (po->data[i].expo <= item.expo) {
			break;
		}
	}

	if (i == sizeArrayList(po)) {
		insertArrayList(po, i, item);
	}
	else if (po->data[i].expo == item.expo) {
		po->data[i].coef += item.coef;
	}
	else {
		insertArrayList(po, i, item);
	}

	return po;
}

polynomial* addPolynomial(polynomial* p1, polynomial* p2) {
	polynomial* r = createPolynomial(100);

	int i = 0, j = 0;

	while (i < sizeArrayList(p1) && j < sizeArrayList(p2)) {
		if (p1->data[i].expo < p2->data[j].expo) {
			addItemPolynomial(r, p2->data[j]);
			j++;
		}
		else if (p1->data[i].expo > p2->data[j].expo) {
			addItemPolynomial(r, p1->data[i]);
			i++;
		}
		else {
			addItemPolynomial(r, (elementType) {
				p1->data[i].coef + p2->data[j].coef,
				p1->data[i].expo
			});
			i++;
			j++;
		}
	}
	
	// 오류수정: 나머지 항 처리 누락 버그 수정
	while (i < sizeArrayList(p1)) {
		addItemPolynomial(r, p1->data[i]);
		i++;
	}
	while (j < sizeArrayList(p2)) {
		addItemPolynomial(r, p2->data[j]);
		j++;
	}

	return r;
}

// 추가: 곱셈 함수
polynomial* multiplyPolynomial(polynomial* p1, polynomial* p2) {
	polynomial* r = createPolynomial(200);
	for (int i = 0; i < sizeArrayList(p1); i++) {
		for (int j = 0; j < sizeArrayList(p2); j++) {
			elementType item;
			item.coef = p1->data[i].coef * p2->data[j].coef;
			item.expo = p1->data[i].expo + p2->data[j].expo;
			addItemPolynomial(r, item);
		}
	}

	return r;
}

// 추가: 문자열 파싱 함수
polynomial* parsePolynomial(char* str) {
	polynomial* po = createPolynomial(100);
	char* p = str;
	while (*p != '\0') {
		int sign = 1;
		if (*p == '+') { sign = 1; p++; }
		else if (*p == '-') { sign = -1; p++; }

		int coef = 0;
		while (isdigit(*p)) {
			coef = coef * 10 + (*p - '0');
			p++;
		}
		coef *= sign;

		int expo = 0;
		if (*p == 'X' || *p == 'x') {
			p++;
			if (*p == '^') {
				p++;
				while (isdigit(*p)) {
					expo = expo * 10 + (*p - '0');
					p++;
				}
			}
		}
		addItemPolynomial(po, (elementType) { coef, expo });
	}

	return po;
}

void printPolynomial(polynomial* po) {
	printf("Polynomial: ");

	for (int i = 0; i < sizeArrayList(po); i++) {
		if (i > 0) printf("+");
		printf("%dX^%d", po->data[i].coef, po->data[i].expo);
	}

	printf("\n");
}