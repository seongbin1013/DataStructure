#include <stdio.h>
#include <stdlib.h>
#include "my_integer.h"

int main() {
    my_integer sum =0;

    for(int i = 1; i <= 100; i++) {
        sum = add(sum, (my_integer)i);
    }
    printf("Sum = %d\n", sum);
    return 0;

}
