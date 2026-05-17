#include "LinkedList.h"

int main() {
	struct linkedList* myList1;
	myList1 = createLinkedList();

	int menu;
	int value;
	int index;
	int result;
	PointType item;
	PointType deleted;

	while(1) {
		printf("1. 맨 앞에 추가\n");
		printf("2. 맨 뒤에 추가\n");
		printf("3. 특정 위치에 추가\n");
		printf("4. 특정 위치 삭제\n");
		printf("5. 전체 목록 출력\n");
		printf("6. 리스트 크기 확인\n");
		printf("0. 종료\n");
		printf("메뉴 선택: ");
		scanf("%d", &menu);

		switch(menu) {
			case 1:
			printf("추가할 정수 입력: ");
			scanf("%d", &value);

			item = (PointType) { value, 0, NULL}; 
			insertFirstLinkedList(myList1, item);

			printf("맨 앞에 %d 추가\n", value);
			break;

			case 2:
			printf("추가할 정수 입력: ");
			scanf("%d", &value);

			item = (PointType) { value, 0, NULL};
			insertLastLinkedList(myList1, item);

			printf("맨 뒤에 %d 추가\n", value);
			break;

			case 3:
			printf("추가할 위치 입력: ");
			scanf("%d", &index);

			printf("추가할 정수 입력: ");
			scanf("%d", &value);

			item = (PointType) { value, 0, NULL};
			insertAtLinkedList(myList1, index, item);

			printf("%d 위치에 %d 추가\n", index, value);
			break;

			case 4:
			printf("삭제할 위치 입력: ");
			scanf("%d", &index);

			deleted = deleteAtLinkedList(myList1, index);
			printf("위치 %d의 요소 %d 삭제\n", index, deleted.x);
			break;

			case 5:
			printLinkedList(myList1);
			break;

			case 6:
			result = sizeLinkedList(myList1);
			printf("리스트 크기: %d\n", result);
			break;

			case 0:
			destroyLinkedList(myList1);
			printf("프로그램 종료\n");
			return 0;

			default:
			printf("잘못된 메뉴입니다.\n");

		}
	}
}