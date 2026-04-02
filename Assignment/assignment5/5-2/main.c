#include <stdio.h>
#include <stdlib.h>

// 홀수 마방진 생성 함수
int main() {
    int n;
    printf("홀수 마방진 크기 입력:");
    scanf("%d", &n);
    if(n % 2 == 0) {
        fprintf(stderr, "홀수만 입력 가능합니다.\n");
        return EXIT_FAILURE;
    }

    int mabangin[n][n]; // n x n 크기 배열

    // 마방진 초기화
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            mabangin[i][j] = 0; // 모든 칸 0으로 초기화
        }
    }

    int num = 1;
    int row = 0, col = n / 2; // 시작 위치: 첫 번째 행의 중앙

    while(num <= n * n) { // 1부터 n^2까지 숫자 채우기
        mabangin[row][col] = num; // 첫 번쨰 숫자 채우기
        num++;

        int next_row = (row - 1 + n) % n; // 다음 행 계산
        int next_col = (col + 1) % n; // 다음 열 계산

        if(mabangin[next_row][next_col] != 0) {
            row = (row + 1) % n; // 다음 행이 이미 채워져 있으면 아래로 이동
        } else {
            row = next_row;
            col = next_col;
        }
    }

    printf("마방진 배열: \n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%4d", mabangin[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("가로/세로/대각선 합:\n");
    printf("\n");

    // 가로 합
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(int j = 0; j < n; j++) {
            sum += mabangin[i][j];
        }
        printf("가로 %d: %d\n", i+1, sum);
    }

    printf("\n");

    // 세로 합
    for(int j = 0; j < n; j++) {
        int sum = 0;
        for(int i =0; i < n; i++) {
            sum += mabangin[i][j];
        }
        printf("세로 %d: %d\n", j+1, sum);
    }

    // 대각선 합
    int diag1 = 0,diag2 = 0;
    for(int i = 0; i < n; i++) {
        diag1 += mabangin[i][i];
        diag2 += mabangin[i][n-1-i];
    }
    printf("\n대각선 합:\n");
    printf("왼쪽 위 -> 오른쪽 아래: %d\n", diag1);
    printf("오른쪽 위 -> 왼쪽 아래: %d\n", diag2);



    return 0;
}