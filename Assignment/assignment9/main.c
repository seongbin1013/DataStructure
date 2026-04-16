    // 1) realloc
    // - 순차 리스트는 배열로 구현되므로, 미리 할당된 칸을 모두 소모하면 데이터를 더이상 추가할 수 없는 포화 상태(Full)가 된다.
    // - 이때, realloc을 사용하여 동적으로 배열의 크기를 늘리는 방법으로 포화 상태를 해결할 수 있도록 순차 리스트를 개선한다.
    // 포인터 = realloc(기존포인터, 새로운크기);

    // 1단계: init()   → 리스트 초기화 (malloc으로 첫 배열 생성)
    // 2단계: add()    → 데이터 추가 (꽉 차면 realloc)
    // 3단계: print()  → 출력
    // 4단계: main()   → 테스트

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct {
        int *data;
        int size;
        int capacity;
    } seqList;

    void init(seqList *list, int capacity) {
        list->data = (int *)malloc(capacity * sizeof(int));
        list->size = 0;
        list->capacity = capacity;
    }

    void add(seqList *list, int value) {
        if(list->size >= list->capacity) {
            list->capacity *= 2;
            list->data = (int *)realloc(list->data, list->capacity *sizeof(int)); 
        }
        list->data[list->size++] = value;
    }

    void print(seqList *list) {
        for(int i = 0; i < list->size; i++) {
            printf("%d ", list->data[i]);
        }
        printf("\n");
    } 

    int main() {
        seqList list;
        init(&list, 3);   // 3칸으로 시작

        for(int i = 1; i <= 10; i++) {
            add(&list, i); // 1부터 10까지 추가
        }

        print(&list);

        free(list.data);
        
        return 0;
    }