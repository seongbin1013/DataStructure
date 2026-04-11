// 1) 배열

// - 숫자 N을 입력받아 동적 할당으로 크기가 N인 학생 구조체 배열을 생성한다.
// - 학생 구조체 배열에는 이름(문자열), 학번(1~N), 성적(1~100) 필드가 존재한다.
// - 학생의 이름은 아래 참고 학생 이름에서 무작위로 사용, 학번은 순서대로 증가, 성적은 무작위 범위 내 숫자를 사용하여 학생 배열을 생성한다.
// - 이름 리스트는 파일 입출력으로 받아온다.
// - 최처점 학생의 정보, 최고점 학생의 정보, 평균 점수를 출력한다.
// - 이때 모든 배열 접근 연산은 인덱스 연산자(arr[idx])만을 사용한다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50]; // 학생 이름 저장
    int id;        // 학번
    int score;     // 성적
} Student;

int main() {
    int n; 
    char name_list[100][50]; // 최대 100명의 학생 이름을 저장할 배열
    int name_count = 0; 

    printf("학생 수 N을 입력하세요: ");
    scanf("%d", &n);

    FILE *fp = fopen("/Users/hongseongbin/Downloads/name_list.txt", "r");

    if (fp == NULL) { 
        printf("Fail to open\n");
        return 0;
    }

    Student *arr = (Student *)malloc(n * sizeof(Student)); // 학생 구조체 배열 동적 할당
    

    for(int i = 0; i < n; i++) {
        if(fgets(name_list[name_count], sizeof(name_list[name_count]), fp) != NULL) { // 파일에서 이름 읽기
            name_list[name_count][strcspn(name_list[name_count], "\n")] = '\0'; // 개행 문자 제거
            name_count++;
        } else {
            printf("이름이 부족합니다. %d명의 이름이 필요합니다.\n", n);
            free(arr);
            fclose(fp);
            return 0;
        }
        int idx = rand() % name_count;
        strcpy(arr[i].name, name_list[idx]);   
        arr[i].id = i + 1; // 학번은 1부터 시작
        arr[i].score = rand() % 100 + 1; // 1~100 사이의 무작위 성적
    }

    int min_idx = 0;
    int max_idx = 0;
    int sum = 0;

    for(int i = 0; i < n; i++) {
        sum += arr[i].score;
        if(arr[i].score < arr[min_idx].score) min_idx = i;
        if(arr[i].score > arr[max_idx].score) max_idx = i;
    }

    printf("최저점 학생: 이름: %s, 학번: %d, 성적: %d\n", arr[min_idx].name, arr[min_idx].id, arr[min_idx].score);
    printf("최고점 학생: 이름: %s, 학번: %d, 성적: %d\n", arr[max_idx].name, arr[max_idx].id, arr[max_idx].score);
    printf("평균 점수: %.2f\n", (float)sum / n);


    free(arr);

    fclose(fp);

    return 0;
}