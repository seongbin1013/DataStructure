#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

int main() {
    int arr[SIZE]; // n이하의 난수 100개를 저장할 배열

    srand(time(NULL)); // 난수 초기화

    for(int n = 0; n < SIZE; n++) { // 100회 반복 
        arr[n] = rand() % (100 + 1); // 1부터 100 사이의 난수 생성
        printf("%d: %d\n" , n+1, arr[n]); // 생성된 난수 출력
    }

    printf("------------------------------------------------------------------\n");

    // 역순 출력
    for(int n = SIZE - 1; n >= 0; n--) { 
        printf("%d: %d\n", n + 1, arr[n]);
    }

    printf("------------------------------------------------------------------\n");

    // 배열 총합 계산
    int sum = 0;
    for(int n = 0; n < SIZE; n++) {
        sum += arr[n];
    }
    printf("총합: %d\n", sum);

    // 배열의 최대값 계산
    int max = arr[0];
    int max_index = 0; // 최댓값의 위치를 저장할 변수
    for(int n = 1; n < SIZE; n++) {
        if(arr[n] > max) {
            max = arr[n];
            max_index = n;
        }
    }
    printf("최댓값: %d (위치: %d)\n", max, max_index+1); // 최댓값과 그 위치 출력

    // 배열의 최솟값 계산
    int min = arr[0];
    int min_index = 0; // 최솟값의 위치를 저장할 변수
    for(int n = 1; n < SIZE; n++) {
        if(arr[n] < min) {
            min = arr[n];
            min_index = n; 
        }
    }
    printf("최솟값: %d (위치: %d)\n", min, min_index+1); // 최솟값과 그 위치 출력

}