// 1) 피보나치 수열

// - 피보나치 수열을 정수 N에 대해 순환적 방법과 재귀적 방법으로 계산하는 코드를 각각 작성한다.
// - 정수 N을 1부터 차례로 늘려가며 각각의 방법에 대한 수행시간을 프로파일링해본다.
// - 결과를 그래프 + 표 등을 포함한 마크다운 문서로 작성하여 깃허브에 등록하고, 링크를 제출한다.
// - 마크다운 문서에는 각각의 방법에 대한 분석, 비교 등을 포함한다.
// - 피보나치 수열의 값은 F(1)=1, F(2)=1, F(3)=2... 로 정의한다.

#include <stdio.h>
#include <time.h>

// 재귀적 방법
long long fib_recursive(int n) {
    if (n <= 2) return 1;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// 순환적 방법 (반복문)
long long fib_iterative(int n) {
    if (n <= 2) return 1;
    long long a = 1, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(void) {
    printf("%-5s %-20s %-15s %-15s\n",
           "N", "F(N)", "Iterative(ns)", "Recursive(ns)");
    printf("------------------------------------------------------------\n");

    // 재귀는 N이 커질수록 폭발적으로 느려지므로 최대 45로 제한
    int max_recursive = 45;
    int max_iterative = 45;

    struct timespec start, end;
    long long iter_ns, rec_ns;

    for (int n = 1; n <= max_iterative; n++) {
        // 순환적 측정
        clock_gettime(CLOCK_MONOTONIC, &start);
        long long val = fib_iterative(n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        iter_ns = (end.tv_sec - start.tv_sec) * 1000000000LL
                + (end.tv_nsec - start.tv_nsec);

        // 재귀적 측정 (N <= 45만)
        if (n <= max_recursive) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            fib_recursive(n);
            clock_gettime(CLOCK_MONOTONIC, &end);
            rec_ns = (end.tv_sec - start.tv_sec) * 1000000000LL
                   + (end.tv_nsec - start.tv_nsec);
            printf("%-5d %-20lld %-15lld %-15lld\n", n, val, iter_ns, rec_ns);
        } else {
            printf("%-5d %-20lld %-15lld %-15s\n", n, val, iter_ns, "N/A");
        }
    }

    return 0;
}