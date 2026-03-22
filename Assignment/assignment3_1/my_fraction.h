#ifndef MY_FRACTION_H
#define MY_FRACTION_H

// 추가 점수 - long long 타입으로 변경 
typedef struct {
    long long numerator;
    long long denominator;
} Fraction;

// 문자열 "A/B" -> Fraction (A와 B는 정수)
Fraction fromString(const char *str);
 
// Fraction -> 문자열 "A/B" (buf는 결과를 저장할 버퍼, buf_size는 버퍼 크기)
void toString(Fraction f, char *buf, int buf_size);

// 기약분수로 약분하는 함수
Fraction reduce(Fraction f);
 
// 사칙연산 함수들
Fraction add(Fraction f1, Fraction f2);
Fraction subtract(Fraction f1, Fraction f2);
Fraction multiply(Fraction f1, Fraction f2);
Fraction divide(Fraction f1, Fraction f2);
 
#endif 