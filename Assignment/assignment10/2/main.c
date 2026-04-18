// 2) 순차리스트 행렬
// - 10*10 크기의 행렬을 순차리스트로 형성하고, 이를 0이 아닌 원소 20개가 있는 희소행렬로 초기화한다.
// - 이 희소행렬을 기존의 순차리스트를 사용하여 표현 및 저장하고, 이 희소행렬의 전치행렬을 만드는 프로그램을 실행하여 데이터 이동 횟수를 출력한다. 
// - 추가 점수: 여러 단계의 포인터를 활용하여 구조를 설계시 가산점이 있습니다.
// sparseMatrix
// ㄴ col
// ㄴ row
// ㄴ arrayList*
// ㄴ 과제 (9)의 arrayList

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1단계: Element 구조체 (행, 열, 값)
typedef struct {
    int row;
    int col;
    int value;
} Element;

// 2단계: arrayList (Element 배열 + 크기 정보)
typedef struct {
    Element *data; // Element 배열을 가리키는 포인터
    int size;
    int capacity;
} arrayList;

// 3단계: sparseMatrix (행렬 전체 정보 + arrayList 포인터)
typedef struct {
    int rows; // 행렬 전체 행 수
    int cols; // 행렬 전체 열 수
    arrayList *list; // arrayList를 가리키는 포인터 (2단계 포인터)
} sparseMatrix;


// arrayList 함수들
void al_init(arrayList *al, int capacity) {
    al->data = (Element *)malloc(capacity * sizeof(Element));
    if (al->data == NULL) { fprintf(stderr, "메모리 할당 실패\n"); exit(1); }
    al->size = 0;
    al->capacity = capacity;
}

static void al_grow(arrayList *al) {
    al->capacity *= 2;
    Element *tmp = (Element *)realloc(al->data, al->capacity * sizeof(Element));
    if (tmp == NULL) { fprintf(stderr, "메모리 재할당 실패\n"); exit(1); }
    al->data = tmp;
}

// arrayList에 원소 추가
void al_add(arrayList *al, int row, int col, int value) {
    if (al->size >= al->capacity) al_grow(al);
    al->data[al->size].row   = row;
    al->data[al->size].col   = col;
    al->data[al->size].value = value;
    al->size++;
}

void al_free(arrayList *al) {
    free(al->data);
    al->data = NULL;
    al->size = al->capacity = 0;
}


// 4단계: sparseMatrix 함수들
// sparseMatrix 초기화
void sm_init(sparseMatrix *sm, int rows, int cols, int capacity) {
    sm->rows = rows;
    sm->cols = cols;
    sm->list = (arrayList *)malloc(sizeof(arrayList));
    if (sm->list == NULL) { fprintf(stderr, "메모리 할당 실패\n"); exit(1); }
    al_init(sm->list, capacity);
}

void sm_free(sparseMatrix *sm) {
    al_free(sm->list);
    free(sm->list);
    sm->list = NULL;
}

// sparseMatrix에 원소 추가
void sm_add(sparseMatrix *sm, int row, int col, int value) {
    al_add(sm->list, row, col, value);
}

// sparseMatrix를 2차원 행렬 형태로 출력
void sm_print_matrix(const sparseMatrix *sm) {
    // 희소행렬을 2차원 배열로 변환
    int mat[10][10] = {0};
    for (int i = 0; i < sm->list->size; i++) {
        Element *e = &(sm->list->data[i]);   /* 3단계 포인터 접근 */
        mat[e->row][e->col] = e->value;
    }
    printf("     ");
    for (int c = 0; c < sm->cols; c++) printf("[%2d] ", c);
    printf("\n");
    for (int r = 0; r < sm->rows; r++) {
        printf("[%2d] ", r);
        for (int c = 0; c < sm->cols; c++) {
            printf("%4d ", mat[r][c]);
        }
        printf("\n");
    }
}

// 출력
void sm_print_list(const sparseMatrix *sm) {
    printf("┌──────┬──────┬───────┐\n");
    printf("│  행  │  열  │  값   │\n");
    printf("├──────┼──────┼───────┤\n");
    for (int i = 0; i < sm->list->size; i++) {
        Element *e = &(sm->list->data[i]);
        printf("│  %3d │  %3d │  %4d │\n", e->row, e->col, e->value);
    }
    printf("└──────┴──────┴───────┘\n");
    printf("(총 %d개의 비영 원소)\n", sm->list->size);
}

// 전치행렬 생성 (열 우선 방식)
sparseMatrix sm_transpose(const sparseMatrix *sm, int *move_count) {
    sparseMatrix result;
    sm_init(&result, sm->cols, sm->rows, sm->list->size);
    *move_count = 0;

    // 열 우선 방식으로 원소 탐색
    for (int c = 0; c < sm->cols; c++) {
        for (int i = 0; i < sm->list->size; i++) {
            Element *e = &(sm->list->data[i]);   // 3단계 포인터 접근
            if (e->col == c) {
                // 열이 c인 원소를 찾으면, 행과 열을 바꿔서 결과 행렬에 추가
                al_add(result.list, e->col, e->row, e->value);
                (*move_count)++;
            }
        }
    }
    return result;
}

// 랜덤한 희소행렬 초기화 (비영 원소 20개)
void sm_init_random(sparseMatrix *sm) {
    int used[10][10] = {0};
    int count = 0;

    srand((unsigned int)time(NULL));

    while (count < 20) {
        int r = rand() % 10;
        int c = rand() % 10;
        if (!used[r][c]) {
            int v = rand() % 98 + 1; // 1~99 사이의 양의 정수
            sm_add(sm, r, c, v);
            used[r][c] = 1;
            count++;
        }
    }
}


int main(void) {
    // 원본 희소행렬 생성 및 초기화
    sparseMatrix origin;
    sm_init(&origin, 10, 10, 20);
    sm_init_random(&origin);

    printf("========================================\n");
    printf("  원본 희소행렬 (10x10, 비영 원소 20개)\n");
    printf("========================================\n\n");

    printf("[행렬 형태]\n");
    sm_print_matrix(&origin);

    printf("\n[리스트 표현 - sparseMatrix → arrayList* → Element*]\n");
    sm_print_list(&origin);

    // 전치행렬 생성 및 데이터 이동 횟수 계산
    int move_count = 0;
    sparseMatrix transposed = sm_transpose(&origin, &move_count);

    printf("\n========================================\n");
    printf("  전치행렬\n");
    printf("========================================\n\n");

    printf("[행렬 형태]\n");
    sm_print_matrix(&transposed);

    printf("\n[리스트 표현]\n");
    sm_print_list(&transposed);

    printf("\n========================================\n");
    printf("  데이터 이동 횟수: %d회\n", move_count);
    printf("  (전체 원소 수 %d × 열 수 %d = %d번 탐색)\n",
           origin.list->size, origin.cols,
           origin.list->size * origin.cols);
    printf("========================================\n");

    // 메모리 해제
    sm_free(&origin);
    sm_free(&transposed);

    return 0;
}