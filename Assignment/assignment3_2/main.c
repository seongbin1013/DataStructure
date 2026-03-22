#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_math.h"

int main(void) {
    int a, b;

    printf("두 정수 입력:");

    if(scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "잘못된 입력입니다.\n");
        return EXIT_FAILURE;
    }

    printf("GCD: %d\n", gcd(a, b));
    printf("LCM: %d\n", lcm(a, b));

    return 0;
}