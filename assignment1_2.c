// 실수를 입력받아 고정 소수점 표현으로 변환한 비트패턴을 출력하는 프로그램을 작성하시오.
// 단, 전체 비트는 16비트, 정수부 8비트, 소수부 8비트로 가정한다. Q8.8 fixed-point, two's complement

#include <stdio.h>
#include <stdint.h> // int16_t 타입을 사용하기 위해 stdint.h 헤더를 포함

int main() {
    float input;
    printf("실수를 입력하세요.: ");
    scanf("%f", &input);

    // Q8.8 고정 소수점 표현으로 변환
    int16_t fixed_point = (int16_t)(input * 256); // 256 = 2^8, 소수부 8비트
    // int16_t는 16비트로 표현하는 정수형, 음수 값도 표현 가능
    
    for(int i = 15; i >= 0; i--) {
        printf("%d", (fixed_point >> i) & 1); // 각 비트를 출력  
        if( i == 8) printf(".");  // 정수부와 소수부 구분
    }
    printf("\n");


}