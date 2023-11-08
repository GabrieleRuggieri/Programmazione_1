#include <stdio.h>

unsigned fun(char *A)
{
    int i = 0;
    while (A[i] != '\0')
        i++;

    return i;
}

int main()
{

    int n = 30;
    char A[n];
    scanf("%[^\n]%*c", A);

    int count = fun(A);

    printf("ci sono: %d \n", count);
}