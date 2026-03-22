#include <stdio.h>
#include <stdlib.h>
#include "my_math.h"

int gcd(int a, int b) {
    // 음수일 경우 양수로 변환
    if(a < 0) a = -a;
    if(b < 0) b = -b;

    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if(a == 0 || b == 0) return 0; // 최소공배수는 0이 될 수 없음
    return ( a / gcd(a,b) ) * b; // 최소공배수 계산 공식
}