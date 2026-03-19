#include <stdio.h>
typedef unsigned int my_integer; // my_integer는 unsigned int의 별칭입니다.

// 2개의 정수 i,j를 받아서 합의 되돌려 줌
my_integer add(my_integer i, my_integer j) {
    return i + j;
}
my_integer minus(my_integer i, my_integer j) {
    return i - j;
}
my_integer mult(my_integer i, my_integer j) {
    return i * j;
}
my_integer divide(my_integer i, my_integer j) {
    if(i % j != 0) {
        printf("Divide error\n");
        return 0;
    } else return (my_integer)(i / j);
}