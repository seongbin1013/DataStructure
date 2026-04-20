#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

sparseMatrix* createSparseMatrix(int row, int col) {
	return createArrayList(row * col);
}

int addElementSparseMatrix(sparseMatrix* sm, int row, int col, int value) {
	int size;
	size = sizeArrayList(sm);
	return insertArrayList(sm, size,
		(elementArrayList) { row, col, value });
	/* [버그 수정 4] 원본: return 없음 (int 함수인데 반환값 누락) */
}

int printSparseMatrix(sparseMatrix* sm) {
	printf("희소행렬입니다\n");
	printArrayList(sm);
	return 1; /* [버그 수정 5] 원본: return 없음 */
}

sparseMatrix* addSparseMatrix(sparseMatrix* sm1, sparseMatrix* sm2) {
	int s1 = sizeArrayList(sm1);
	int s2 = sizeArrayList(sm2);

	/* [버그 수정 6] 원본: createArrayList(100) 고정값
	   -> sm1+sm2 원소 수 기반으로 동적 할당 */
	sparseMatrix* smResult = createArrayList(s1 + s2);

	/* sm1 순회: sm2에 같은 위치 있으면 합산, 없으면 그대로 추가 */
	for (int i = 0; i < s1; i++) {  /* [버그 수정 7] 원본: i <= s1 -> 범위 밖 접근 */
		elementArrayList e1 = getItemArrayList(sm1, i);
		int j;
		for (j = 0; j < s2; j++) {  /* [버그 수정 8] 원본: j <= s2 -> 범위 밖 접근 */
			elementArrayList e2 = getItemArrayList(sm2, j);
			if (e1.row == e2.row && e1.col == e2.col) {
				insertArrayList(smResult, sizeArrayList(smResult),
					(elementArrayList) {
					e1.row, e1.col, e1.value + e2.value
				});
				break;
			}
		}
		if (j == s2) {
			insertArrayList(smResult, sizeArrayList(smResult), e1);
		}
	}

	/* [버그 수정 9] 원본 누락: sm2에만 있는 원소를 결과에 추가하지 않음
	   -> sm1에 없는 sm2 전용 원소도 결과에 포함시켜야 함 */
	for (int j = 0; j < s2; j++) {
		elementArrayList e2 = getItemArrayList(sm2, j);
		int found = 0;
		for (int i = 0; i < s1; i++) {
			elementArrayList e1 = getItemArrayList(sm1, i);
			if (e1.row == e2.row && e1.col == e2.col) {
				found = 1;
				break;
			}
		}
		if (!found) {
			insertArrayList(smResult, sizeArrayList(smResult), e2);
		}
	}

	return smResult;
}