#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long gcd(long long a, long long b) {
    if(a < 0) a = -a;
    if(b < 0) b = -b;

    if(b == 0) return a;

    while(b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 피보나치 수열을 재귀적으로 계산하는 함수
long long fibonacci(int n) {
    if(n <= 0) return 0;
    if(n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    printf("%-6s %-20s %-20s %-6s %-15s\n",
           "n", "F(n)", "F(n-1)", "GCD", "Time(us)");
    printf("------------------------------------------------------------------\n");

    
    for(int n = 5; n <= 50; n++) {
        long long fn  = fibonacci(n);
        long long fn1 = fibonacci(n - 1);

        clock_t start = clock();

        /* 정밀도 향상을 위해 1,000,000회 반복 후 평균 */
        long long result = 0;
        for(int r = 0; r < 1000000; r++) {
            result = gcd(fn, fn1);
        }

        clock_t end = clock();

        // 시간 측정 결과를 마이크로초 단위로 변환
        double elapsed_us = ((double)(end - start) / CLOCKS_PER_SEC * 1e6) / 1000000.0;
 
        printf("%-6d %-20lld %-20lld %-6lld  %.6f\n", n, fn, fn1, result, elapsed_us);
    }

    return 0;
}