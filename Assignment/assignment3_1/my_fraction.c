#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_fraction.h"

// gcd = 최대공약수 계산 함수
static int gcd(int a, int b) {
    if(a < 0) a = -a; 
    if(b < 0) b = -b;

    while(b != 0) { 
        int temp = b;
        b = a % b;
        a = temp;
    } 
    return a;
}

// 문자열에서 분수 구조체로 변환하는 함수
Fraction fromString(const char *str) {
    Fraction f;
    // sscanf -> 문자열에서 A/B 형식으로 정수 A와 B를 추출
    if(sscanf(str, "%d/%d", &f.numerator, &f.denominator) != 2)  {
        fprintf(stderr, "잘못된 입력 형식입니다. 'A/B' 형식으로 입력해주세요.\n"); // 오류 메시지 출력
        exit(EXIT_FAILURE); // 프로그램 종료
    }
    // 분모가 0인 경우는 에러 처리
    if(f.denominator == 0) {
        fprintf(stderr, "분모는 0이 될 수 없습니다.\n");
        exit(EXIT_FAILURE);
    }
    return f;
}

// 다시 문자열로 변환하는 함수
void toString(Fraction f, char *buf, int buf_size) {
    // snprintf -> 분자와 분모를 "A/B" 형식의 문자열로 buf에 저장, buf_size는 버퍼 크기
    // sprintf는 버퍼 오버플로우 위험 있으므로 snprintf 사용 
    snprintf(buf, buf_size, "%d/%d", f.numerator, f.denominator);
}

// 기약분수 계산 함수
Fraction reduce(Fraction f) {
    // 분모가 음수일 경우 분자와 분모의 부호를 바꿔서 분모를 양수로 변환 
    if(f.denominator < 0) {
        f.numerator = -f.numerator;
        f.denominator = -f.denominator; 
    }
    // 분자가 0인 경우 분모가 1이 되도록 처리 (0은 어떤 수로 나누어도 0)
    if(f.numerator == 0) { 
        f.denominator = 1; 
        return f; 
    }
    int g = gcd(f.numerator, f.denominator); 
    f.numerator /= g;
    f.denominator /= g;
    return f;
}

Fraction add(Fraction f1, Fraction f2) {
    Fraction result;
    // 분수 덧셈 공식: A/B + C/D = (A*D + C*B) / (B*D)
    result.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    result.denominator = f1.denominator * f2.denominator;

    return reduce(result); // 결과를 기약분수로 약분하여 반환
}

Fraction subtract(Fraction f1, Fraction f2) {
    Fraction result;
    // 분수 뺄셈 공식은 덧셈 공식과 유사힘
    result.numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    result.denominator = f1.denominator * f2.denominator;

    return reduce(result);
}

Fraction multiply(Fraction f1, Fraction f2) {
    Fraction result;

    // 분수 곱셈 공식: A/B * C/D = (A*C) / (B*D)
    result.numerator = f1.numerator * f2.numerator;
    result.denominator = f1.denominator * f2.denominator;

    return reduce(result); 
}

Fraction divide(Fraction f1, Fraction f2) {
    if(f2.numerator == 0) {
        fprintf(stderr, "0으로 나눌 수 없습니다.\n");
        exit(EXIT_FAILURE); 
    } 
    Fraction result;

    // 분수 나눗셈 공식: (A/B) / (C/D) = (A*D) / (B*C)
    result.numerator = f1.numerator * f2.denominator;
    result.denominator = f1.denominator * f2.numerator;

    return reduce(result);
}