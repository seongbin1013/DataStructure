#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    printf("배열 크기 N을 입력하세요: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("1 이상의 양수를 입력하세요.\n");
        return 1;
    }

    // 동적 할당
    int *arr = (int *)malloc(n * sizeof(int)); 
    if (arr == NULL) {
        printf("메모리 할당 실패\n");
        return 1;
    }

    srand(time(NULL));

    // 0~N 사이의 난수로 배열 채우기
    int *ptr = arr;
    for (int i = 0; i < n; i++) {
        *(ptr + i) = rand() % (n + 1); // 0~N 범위의 난수
    }

    // 순방향 출력
    printf("--- 순방향 출력 ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d: %d\n", i + 1, *(ptr + i));
    }

    // 역방향 출력
    printf("--- 역방향 출력 ---\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d: %d\n", i + 1, *(ptr + i));
    }

    // 총합, 최대값, 최소값
    int sum = 0;
    int max = *ptr;
    int max_idx = 0;
    int min = *ptr;
    int min_idx = 0;

    for (int i = 0; i < n; i++) {
        int val = *(ptr + i);
        sum += val;
        if (val > max) { max = val; max_idx = i; }
        if (val < min) { min = val; min_idx = i; }
    }

    printf("------------------------------------------------------------------\n");
    printf("총합: %d\n", sum);
    printf("최댓값: %d (위치: %d)\n", max, max_idx + 1);
    printf("최솟값: %d (위치: %d)\n", min, min_idx + 1);

    free(arr);
    return 0;
}