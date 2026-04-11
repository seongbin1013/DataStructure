// 2) 
// - 모든 배열 접근 연산을 포인터 연산자(*(arr + idx))를 통해 진행한다.

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
        if(fgets(name_list[name_count], sizeof(name_list[name_count]), fp) != NULL) {
            name_list[name_count][strcspn(name_list[name_count], "\n")] = '\0';
            name_count++;
        } else {
            printf("이름이 부족합니다. %d명의 이름이 필요합니다.\n", n);
            free(arr);
            fclose(fp);
            return 0;
        }
        int idx = rand() % name_count;
        strcpy((*(arr + i)).name, name_list[idx]);   
        (*(arr + i)).id = i + 1;
        (*(arr + i)).score = rand() % 100 + 1;
    }

    int min_idx = 0;
    int max_idx = 0;
    int sum = 0;

    for(int i = 0; i < n; i++) {
        sum += (*(arr + i)).score;
        if((*(arr + i)).score < (*(arr + min_idx)).score) min_idx = i;
        if((*(arr + i)).score > (*(arr + max_idx)).score) max_idx = i;
    }

    printf("최저점 학생: 이름: %s, 학번: %d, 성적: %d\n", (*(arr + min_idx)).name, (*(arr + min_idx)).id, (*(arr + min_idx)).score);
    printf("최고점 학생: 이름: %s, 학번: %d, 성적: %d\n", (*(arr + max_idx)).name, (*(arr + max_idx)).id, (*(arr + max_idx)).score);
    printf("평균 점수: %.2f\n", (float)sum / n);


    free(arr);

    fclose(fp);

    return 0;
}