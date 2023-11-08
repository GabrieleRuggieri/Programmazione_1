// Homework 15.1

#include <stdio.h>

unsigned fun(short a, short b)
{

    int result = a * b;

    if (result < 0)
        result = -result;

    else
        result = result;

    return result;
}

int main()
{
    int a = 5, b = -2;

    unsigned x = fun(a, b);

    printf("function = %u \n", x);

    return 0;
}