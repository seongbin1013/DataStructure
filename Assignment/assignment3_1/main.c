#include <stdio.h>
#include <stdlib.h>
#include "my_fraction.h"

#define BUF_SIZE 100 // buf_size는 충분히 큰 값으로 설정하여 결과 문자열이 버퍼를 초과하지 않도록 함

int main(void) {
    char f1_str[BUF_SIZE], f2_str[BUF_SIZE];
    char op; // 연산자 입력 변수

    printf("분수 연산 입력 (예: 1/2 + 3/4): ");

    if(scanf("%s %c %s", f1_str, &op, f2_str) != 3) {  
        fprintf(stderr, "잘못된 입력 형식입니다.\n"); 
        return EXIT_FAILURE;
    }

    // 입력된 문자열을 분수 구조체로 변환
    Fraction f1 = fromString(f1_str);
    Fraction f2 = fromString(f2_str);
    Fraction result; 
 
    // 연산자에 따라 사칙연산 수행
    switch (op) {
        case '+': result = add(f1, f2);      break;
        case '-': result = subtract(f1, f2); break;
        case '*': result = multiply(f1, f2); break;
        case '/': result = divide(f1, f2);   break;
       default:
            fprintf(stderr, "지원하지 않는 연산자입니다.\n");
            return EXIT_FAILURE;
    }
 
    char result_str[BUF_SIZE];
    toString(result, result_str, BUF_SIZE);
    printf("%s\n", result_str);
 
    return 0;
}