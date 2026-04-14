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