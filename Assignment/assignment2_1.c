#include <stdio.h>
#include <string.h>

int main() {
    float input;
    printf("실수 입력: ");
    scanf("%f", &input);

    // unsinged int로 float의 비트를 그대로 복사함
    unsigned int bits;
    memcpy(&bits, &input, sizeof(bits)); 

    int sign = (bits >> 31) & 1; // 부호 비트

    int exp = (bits >> 23) & 0xFF; // 지수 비트 (8비트) 

    int mantissa = bits & 0x7FFFFF; // 가수 비트 (23비트)

    printf("%d/", sign); // 부호 비트 출력

    // 지수 비트 출력
    for(int i = 7; i >= 0; i--) { 
        printf("%d", (exp >> i) & 1); 
        if(i == 4) printf(" "); // 중간에 공백 추가
    }
    printf("/");

    // 가수 비트 출력
    for(int i = 22; i >= 0; i--) {
        printf("%d", (mantissa >> i) & 1);
        if(i == 19 || i == 15 || i == 11 || i == 7 || i == 3) printf(" "); // 4비트마다 공백 추가
    }

    printf("\n");

    return 0;
}