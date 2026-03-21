#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_fraction.h"

// gcd = 최대공약수 계산 함수
static int gcd(int a, int b) {
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    } return a;
}

Fraction reduce(Fraction f) {
    if(f.denominator < 0) {
        f.numerator = -f.numerator;
        f.denominator = -f.denominator;
    }
    return f;
}

Fraction add(Fraction f1, Fraction f2) {
    Fraction result;
    
    // 분자 
    result.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;

    // 분모
    result.denominator = f1.denominator * f2.denominator;

    return reduce(result); // 결과를 기약분수로 약분하여 반환
}