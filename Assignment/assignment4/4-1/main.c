#include <stdio.h>
#include <stdlib.h> 

int gcd(int a,int b) {
    if(a < 0) a = -a;
    if(b < 0) b = -b;

    if(b == 0) return a;

    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    int a, b;
    printf("두 정수 입력: ");
    
    if(scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "잘못된 입력입니다.\n");
        return EXIT_FAILURE;
    }
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a,b));

    return 0;
}