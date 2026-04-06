#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("홀수 마방진 크기 입력: ");
    scanf("%d", &n);
    if (n % 2 == 0) {
        fprintf(stderr, "홀수만 입력 가능합니다.\n");
        return EXIT_FAILURE;
    }

    // 동적 할당: int** 포인터 배열
    int **mabangin = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        *(mabangin + i) = (int *)malloc(n * sizeof(int));
    }

    // 마방진 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(mabangin + i) + j) = 0;
        }
    }

    int num = 1;
    int row = 0, col = n / 2;

    while (num <= n * n) {
        *(*(mabangin + row) + col) = num++;

        int next_row = (row - 1 + n) % n;
        int next_col = (col + 1) % n;

        if (*(*(mabangin + next_row) + next_col) != 0) {
            row = (row + 1) % n;
        } else {
            row = next_row;
            col = next_col;
        }
    }

    // 배열 출력
    printf("마방진 배열:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", *(*(mabangin + i) + j));
        }
        printf("\n");
    }

    printf("가로/세로/대각선 합:\n");
    printf("\n");

    // 가로 합
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += *(*(mabangin + i) + j);
        }
        printf("가로 %d: %d\n", i + 1, sum);
    }

    printf("\n");

    // 세로 합
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += *(*(mabangin + i) + j);
        }
        printf("세로 %d: %d\n", j + 1, sum);
    }

    printf("\n");

    // 대각선 합
    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < n; i++) {
        diag1 += *(*(mabangin + i) + i);
        diag2 += *(*(mabangin + i) + (n - 1 - i));
    }
    printf("왼쪽 위 -> 오른쪽 아래: %d\n", diag1);
    printf("오른쪽 위 -> 왼쪽 아래: %d\n", diag2);

    // 메모리 해제
    for (int i = 0; i < n; i++)
        free(*(mabangin + i));
    free(mabangin);

    return 0;

}