#include "arrayList.h"

typedef arrayList polynomial;

extern polynomial* createPolynomial(int capacity);
extern polynomial* addItemPolynomial(polynomial* po, elementType item);
extern void printPolynomial(polynomial* po);
extern polynomial* addPolynomial(polynomial* p1, polynomial* p2);
// 추가: 곱셈 및 파싱 함수 선언
extern polynomial* multiplyPolynomial(polynomial* p1, polynomial* p2);
extern polynomial* parsePolynomial(char* str);