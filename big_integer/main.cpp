

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include "big_integer.hpp"

using namespace std;

bool testOneAdd() {
    int sign1 = -1;
    if (rand() % 2 == 1) {
        sign1 = 1;
    }
    int lhs = rand() % 1000000;
    lhs *= sign1;
    int sign2 = -1;
    if (rand() % 2 == 1) {
        sign2 = 1;
    }
    int rhs = rand() % 1000000;
    rhs *= sign2;
    int ansInt = lhs + rhs;
    big_integer bi1 = big_integer(lhs);
    big_integer bi2 = big_integer(rhs);
    bi1 += bi2;
    big_integer ans = big_integer(ansInt);
    if (to_string(bi1) != to_string(ans))
        cerr << lhs << " += " << rhs << " -> " << to_string(bi1) << " ? " << to_string(ans) << endl;
    return to_string(bi1) == to_string(ans);
}

bool testOneSub() {
    int sign1 = -1;
    if (rand() % 2 == 1) {
        sign1 = 1;
    }
    int lhs = rand() % 1000000;
    lhs *= sign1;
    int sign2 = -1;
    if (rand() % 2 == 1) {
        sign2 = 1;
    }
    int rhs = rand() % 1000000;
    rhs *= sign2;
    int ansInt = lhs - rhs;
    big_integer bi1 = big_integer(lhs);
    big_integer bi2 = big_integer(rhs);
    bi1 -= bi2;
    big_integer ans = big_integer(ansInt);
    if (to_string(bi1) != to_string(ans))
        cerr << lhs << " -= " << rhs << " -> " << to_string(bi1) << " ? " << to_string(ans) << endl;
    return to_string(bi1) == to_string(ans);
}

bool testOneMul() {
    int sign1 = -1;
    if (rand() % 2 == 1) {
        sign1 = 1;
    }
    int lhs = rand() % 10000;
    lhs *= sign1;
    int sign2 = -1;
    if (rand() % 2 == 1) {
        sign2 = 1;
    }
    int rhs = rand() % 10000;
    rhs *= sign2;
    int ansInt = lhs * rhs;
    big_integer bi1 = big_integer(lhs);
    big_integer bi2 = big_integer(rhs);
    bi1 *= bi2;
    big_integer ans = big_integer(ansInt);
    //cerr << lhs << " * " << rhs << " = " << bi1 << " (" << ansInt << ")" << endl;
    return to_string(bi1) == to_string(ans);
}

void testAdd(int number) {
    int total = 0;
    for (int i = 0; i < number; ++i) {
        total += testOneAdd();
    }
    printf("Add: %d\\%d\n", total, number);

}

void testSub(int number) {
    int total = 0;
    for (int i = 0; i < number; ++i) {
        total += testOneSub();
    }
    printf("Sub: %d\\%d\n", total, number);

}

void testMul(int number) {
    int total = 0;
    for (int i = 0; i < number; ++i) {
        total += testOneMul();
    }
    printf("Mul: %d\\%d\n", total, number);

}

int main() {
    srand (time(NULL));
    big_integer x = big_integer(145);
    big_integer y = big_integer(514);
    x *= y;
    cout << x << endl;
    testAdd(1000);
    testSub(1000);
    testMul(1000);

    return 0;
}