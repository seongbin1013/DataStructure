#include <stdio.h>

int main() {
    
    char input[1000];
    int count = 0;

    printf("문자열을 입력하세요: ");
    fgets(input, sizeof(input), stdin); // fgets(문자열배열, 최대크기, 입력스트림)
    // *scanf 하지 않는 이유 : 공백 전까지 입력받기 때문

    while (input[count]) {
        if(input[count] >= 65 && input[count] <= 90) { // 대문자
            input[count] += 32; // 소문자로 치환
        } else if(input[count] >= 97 && input[count] <= 122) { // 소문자
            input[count] -= 32; // 대문자로 변환
        }

        count++;
    }

    printf("%s", input);
    return 0;
}