// Homework 15.2

#include <stdio.h>

void fun(short a, short b, unsigned *c) //*c : puntatore
{

    int result = a * b;

    if (result < 0)
        *c = -result;

    else
        *c = result;
}

int main()
{
    int a = 5, b = -2;

    unsigned x;

    fun(a, b, &x);

    printf("function = %u \n", x);

    return 0;
}