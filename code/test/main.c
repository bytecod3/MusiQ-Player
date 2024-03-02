#include <stdio.h>

int bar(int i) {
    printf("This is bar: %d\n", i);
    return i;
}

typedef int(*f_t)(int);

int main () {
    f_t f1, f2, f3, f4;

    int p;

    int* q;

    q = &p;

    f1 = &bar;

    int n = f(10);
    int m = (*f)(30);

    printf("This is main\n");



}