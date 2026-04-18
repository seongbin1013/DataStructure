// 1) 순차 리스트 개선

// - 깃허브에 등록된 과제(9)의 ArrayList 코드를 바탕으로 양의 정수 전용 순차리스트를 만든다.

// - 만든 양의 정수 순차 리스트에 대하여 다음과 같은 메뉴 기능을 추가하고, 이를 사용해 동작하는 프로그램을 작성한다.
//     1. 양의 정수와 위치를 입력 받아서 리스트에 추가 (insert)
//     2. 위치를 입력 받아서 리스트에서 삭제 (delete)
//     3, 양의 정수와 위치를 입력 받아서 항목의 값의 변경 (replace)
//     4. 양의 정수 리스트을 위치와 함께 프린트 (print)
//     5. 양의 정수 리스트에서 모든 값을 삭제 (clear)
// - 기존에 구현된 내용인 경우, 오류를 개선

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} seqList;

void init(seqList *list, int capacity) {
    list->data = (int *)malloc(capacity * sizeof(int));
    if (list->data == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    list->size = 0;
    list->capacity = capacity;
    
}

static void grow(seqList *list) {
    list->capacity *= 2;
    int *tmp = (int *)realloc(list->data, list->capacity * sizeof(int));
    if (tmp == NULL) {
        fprintf(stderr, "메모리 재할당 실패\n");
        exit(1);
    }
    list->data = tmp;
}

// 1. insert: pos 위치(1-based) 항목에 value 삽입
void insert(seqList *list, int pos, int value) {
    // 양의 정수 검사
    if (value <= 0) {
        printf("오류: 양의 정수만 입력할 수 있습니다.\n");
        return;
    }
    // 위치 범위 검사: 1 ~ size+1
    if (pos < 1 || pos > list->size + 1) {
        printf("오류: 위치는 1 ~ %d 사이여야 합니다.\n", list->size + 1);
        return;
    }
    if (list->size >= list->capacity) {
        grow(list);
    }
    // pos 이후 항목들을 한 칸씩 뒤로 이동 (0-based index: pos-1)
    for (int i = list->size; i >= pos; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[pos - 1] = value;
    list->size++;
    printf("위치 %d에 %d 삽입 완료.\n", pos, value);
}

// 2. delete: pos 위치(1-based) 항목 삭제
void delete(seqList *list, int pos) {
    if (list->size == 0) {
        printf("오류: 리스트가 비어 있습니다.\n");
        return;
    }
    if (pos < 1 || pos > list->size) {
        printf("오류: 위치는 1 ~ %d 사이여야 합니다.\n", list->size);
        return;
    }
    int removed = list->data[pos - 1];

    // pos 이후 항목들을 한 칸씩 앞으로 이동 (0-based index: pos-1)
    for (int i = pos - 1; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
    printf("위치 %d의 값 %d 삭제 완료.\n", pos, removed);
}

// 3. replace: pos 위치(1-based) 항목의 값을 value로 변경
void replace(seqList *list, int pos, int value) {
    if (value <= 0) {
        printf("오류: 양의 정수만 입력할 수 있습니다.\n");
        return;
    }
    if (list->size == 0) {
        printf("오류: 리스트가 비어 있습니다.\n");
        return;
    }
    if (pos < 1 || pos > list->size) {
        printf("오류: 위치는 1 ~ %d 사이여야 합니다.\n", list->size);
        return;
    }
    int old = list->data[pos - 1];
    list->data[pos - 1] = value;
    printf("위치 %d의 값 %d → %d 변경 완료.\n", pos, old, value);
}

// 4. print: 리스트의 모든 항목을 위치와 함께 출력s
void print(seqList *list) {
    if (list->size == 0) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }
    printf("┌──────┬───────┐\n");
    printf("│  위치 │  값   │\n");
    printf("├──────┼───────┤\n");
    for (int i = 0; i < list->size; i++) {
        printf("│  %3d  │  %4d │\n", i + 1, list->data[i]);
    }
    printf("└──────┴───────┘\n");
    printf("(총 %d개)\n", list->size);
}

// 5. clear: 모든 항목 삭제
void clear(seqList *list) {
    list->size = 0;
    printf("리스트의 모든 항목을 삭제했습니다.\n");
}

// 입력 버퍼 비우기
static void flush_stdin(void) { 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    seqList list;
    init(&list, 4);

    int choice;

    while (1) {
        printf("\n========== 순차 리스트 메뉴 ==========\n");
        printf("1. 삽입 (insert)\n");
        printf("2. 삭제 (delete)\n");
        printf("3. 변경 (replace)\n");
        printf("4. 출력 (print)\n");
        printf("5. 전체 삭제 (clear)\n");
        printf("0. 종료\n");
        printf("선택 >> ");

        if (scanf("%d", &choice) != 1) {  
            flush_stdin();
            printf("잘못된 입력입니다.\n");
            continue;
        }
        flush_stdin();

        int pos, value;

        switch (choice) {
        case 1:
            printf("삽입할 양의 정수: ");
            if (scanf("%d", &value) != 1) { 
                flush_stdin(); break; 
            }
            flush_stdin();
            printf("삽입할 위치 (1 ~ %d): ", list.size + 1);

            if (scanf("%d", &pos) != 1) { 
                flush_stdin(); break; 
            }
            flush_stdin();

            insert(&list, pos, value);
            break;

        case 2:
            printf("삭제할 위치 (1 ~ %d): ", list.size);
            if (scanf("%d", &pos) != 1) { 
                flush_stdin(); break; 
            }
            flush_stdin();
            delete(&list, pos);
            break;

        case 3:
            printf("변경할 위치 (1 ~ %d): ", list.size);
            if (scanf("%d", &pos) != 1) { 
                flush_stdin(); break; 
            }
            flush_stdin();

            printf("새로운 양의 정수: ");
            if (scanf("%d", &value) != 1) { 
                flush_stdin(); break; 
            }
            flush_stdin();
            replace(&list, pos, value);
            break;

        case 4:
            print(&list);
            break;

        case 5:
            clear(&list);
            break;

        case 0:
            printf("프로그램을 종료합니다.\n");
            free(list.data);
            return 0;

        default:
            printf("0 ~ 5 중에서 선택하세요.\n");
        }
    }
}