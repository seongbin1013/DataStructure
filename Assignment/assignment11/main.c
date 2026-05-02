#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

int main() {
	char str1[256], str2[256];

	printf("첫 번째 다항식 입력 (예: 3X^2+2X^1+1X^0): ");
	scanf("%s", str1);
	printf("두 번째 다항식 입력 (예: 1X^1+2X^0): ");
	scanf("%s", str2);

	polynomial* p1 = parsePolynomial(str1);
	polynomial* p2 = parsePolynomial(str2);

	printf("P1 = ");
	printPolynomial(p1);
	printf("P2 = ");
	printPolynomial(p2);

	polynomial* result = multiplyPolynomial(p1, p2);
	printf("P1 * P2 = ");
	printPolynomial(result);

	destroyArrayList(p1);
	destroyArrayList(p2);
	destroyArrayList(result);

	return 0;
}