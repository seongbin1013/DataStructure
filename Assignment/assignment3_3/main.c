#include <stdio.h>
#include <stdlib.h>
#include "my_fraction.h"

// 직사각형의 가로, 세로를 인자로 입력받아 둘레와 넓이를 출력하는 프로그램

int main(int c, char **v) {
    if(c != 3) { 
        fprintf(stderr, "사용법: %s <가로> <세로>\n", v[0]);
        fprintf(stderr, "입력 형식: 분수(A/B), 정수(A), 소수(A.B)\n");
        fprintf(stderr, "예시: %s 3/7 4/9\n", v[0]);
        fprintf(stderr, "예시: %s 3 4\n", v[0]);
        fprintf(stderr, "예시: %s 1.5 2.5\n", v[0]);
        return EXIT_FAILURE;
    }
    
    
    Fraction width = fromString(v[1]);
    Fraction height = fromString(v[2]);

    // 추가 점수 - 가로/세로가 0 이하인 경우 경고
    if(width.numerator <= 0 || height.numerator <= 0) {
        fprintf(stderr, "가로와 세로는 양수여야 합니다.\n");
        return EXIT_FAILURE;
    }

    Fraction two = {2, 1}; // 2를 분수로 표현 (2/1)
    Fraction sum = add(width, height); // 가로와 세로의 합
    Fraction perimeter = multiply(two, sum); // 둘레 = 2 * (가로 + 세로)
    
    Fraction area = multiply(width, height); // 넓이 = 가로 * 세로

    char peri_str[100];
    char area_str[100];

    // 결과를 문자열로 변환
    toString(perimeter, peri_str, sizeof(peri_str));
    toString(area, area_str, sizeof(area_str));

    printf("넓이: %s\n", peri_str);
    printf("면적: %s\n", area_str);

    return 0;
}