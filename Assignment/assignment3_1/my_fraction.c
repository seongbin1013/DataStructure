#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_fraction.h"

// gcd = 최대공약수 계산 함수
// 추가 점수 - long long 타입으로 확장하여 오버플로우 방지
static long long gcd(long long a, long long b) {
    if(a < 0) a = -a; 
    if(b < 0) b = -b;

    while(b != 0) { 
        long long temp = b;
        b = a % b;
        a = temp;
    } 
    return a;
}

// 추가 점수 - 문자열이 소수 형태인지 확인
static int isDecimal(const char *str) {
    return strchr(str, '.') != NULL; // 문자열에 '.'이 포함되어 있는지 확인
}

// 추가 점수 - 빈 문자열 또는 NULL 포인터에 대한 예외 처리
static Fraction decimalToFraction(const char *str) {
    if (str == NULL || str[0] == '\0') {
        fprintf(stderr, "입력된 문자열이 소수 형태가 아닙니다.\n");
        exit(EXIT_FAILURE);
    }

    // 추가 점수 - 소수점 이하 자릿수를 세어 분모(10^n)를 결정
    const char *dot = strchr(str, '.');
    int decimal_places = 0;
    if (dot != NULL) {
        decimal_places = strlen(dot + 1); // 소수점 이후 자릿수 계산
    }

    // 소수점 9자리 이상은 오버플로우 위험
    if(decimal_places > 9) {
        fprintf(stderr, "소수점 이하 9자리 이하만 지원됩니다.\n");
        exit(EXIT_FAILURE);
    }

    long long denom = 1; // 분모 초기값
    for (int i = 0; i < decimal_places; i++) {
        denom *= 10; // 분모는 10의 n제곱
    }
    
    char buf[64]; // 소수점 제거 후 정수로 변환
    if(strlen(str) >= sizeof(buf)) {
        fprintf(stderr, "입력된 소수 문자열이 너무 깁니다.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(buf, str, sizeof(buf) - 1); // 
    buf[sizeof(buf) - 1] = '\0'; 

    // 소수점 제거
    char *p = strchr(buf, '.');
    if (p) {
        memmove(p, p + 1, strlen(p + 1) + 1);
    }

    // 문자 포함 여부
    int start = (buf[0] == '-') ? 1 : 0;
    for (int i = start; buf[i] != '\0'; i++) {
        if (!isdigit((unsigned char)buf[i])) {
            fprintf(stderr, "입력된 문자열이 유효하지 않습니다.\n");
            exit(EXIT_FAILURE);
        }
    }

    long long numer = atoll(buf);
    Fraction f = { numer, denom };
    return reduce(f);
}

// 문자열에서 분수 구조체로 변환하는 함수
Fraction fromString(const char *str) {
    // 추가 점수 - 입력 문자열이 NULL이거나 빈 문자열인 경우 예외 처리
    if(str == NULL || str[0] == '\0') { 
        fprintf(stderr, "입력된 문자열이 유효하지 않습니다.\n");
        exit(EXIT_FAILURE);
    }

    Fraction f;

    // 1. 분수 형태 A/B
    if (strchr(str, '/') != NULL) {
        if (sscanf(str, "%lld/%lld", &f.numerator, &f.denominator) != 2) {
            fprintf(stderr, "잘못된 입력 형식입니다. 'A/B' 형식으로 입력해주세요.\n");
            exit(EXIT_FAILURE);
        }
        if (f.denominator == 0) {
            fprintf(stderr, "분모는 0이 될 수 없습니다.\n");
            exit(EXIT_FAILURE);
        }
        return reduce(f);
    }

    // 2. 소수 형태 A.B
    if(isDecimal(str)) {
        return decimalToFraction(str);
    }

    // 3. 정수 형태 A
    int start = (str[0] == '-') ? 1 : 0; // 음수인 경우 시작 인덱스 조정
    if(str[start] == '\0') { // 숫자가 없는 경우 예외 처리
        fprintf(stderr, "입력된 문자열이 유효하지 않습니다.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = start; str[i] != '\0'; i++) {
        if(!isdigit((unsigned char)str[i])) { // 숫자가 아닌 문자가 포함된 경우 예외 처리
            fprintf(stderr, "입력된 문자열이 유효하지 않습니다.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    f.numerator = atoll(str);
    f.denominator = 1;
    return f;
}


// 다시 문자열로 변환하는 함수
void toString(Fraction f, char *buf, int buf_size) {
    // snprintf -> 분자와 분모를 "A/B" 형식의 문자열로 buf에 저장, buf_size는 버퍼 크기
    // sprintf는 버퍼 오버플로우 위험 있으므로 snprintf 사용. 

    // 추가 점수 - buf가 NULL이거나 buf_size가 0 이하인 경우 예외 처리
    if(buf == NULL || buf_size <= 0) {
        fprintf(stderr, "출력 버퍼가 유효하지 않습니다.\n");
        exit(EXIT_FAILURE);
    }

    // 추가 점수 - 분모가 1인 경우는 정수로 출력하도록 처리
    if(f.denominator == 1) {
        snprintf(buf, buf_size, "%lld", f.numerator); // 분모가 1인 경우는 정수로 출력
    } else {
        snprintf(buf, buf_size, "%lld/%lld", f.numerator, f.denominator); // 일반적인 분수 형식으로 출력
    }
}

// 기약분수 계산 함수
Fraction reduce(Fraction f) {
    // 추가 점수 - 분모가 0일경우 예외처리
    if(f.denominator == 0) {
        fprintf(stderr, "분모가 0이 될 수 없습니다\n.");
        exit(EXIT_FAILURE);
    }

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
    long long g = gcd(f.numerator, f.denominator); 
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
    // 추가점수 - 오류 핸들링: 0으로 나누기
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