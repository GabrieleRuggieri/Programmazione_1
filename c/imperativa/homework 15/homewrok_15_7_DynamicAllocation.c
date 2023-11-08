#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

/*
    #define n 3
    #define m 4
*/

unsigned fun(int **A, int n, int m, double y)
{

    unsigned col = 0;

    double media;

    for (int j = 0; j < m; j++)
    {
        media = 0.0;

        for (int i = 0; i < n; i++)

            media += A[i][j];

        if ((media / n) <= y)
            col++;
    }

    return col;
}

int main()
{

    int a = 1, b = 5, n = 5, m = 7;

    int **A;

    double y = 3.2;
    // double y = rand() % (b - a + 1) + a;

    srand(time(0));

    A = (int **)malloc(sizeof(int *) * n); // allocazione dinamica --> Heap
    for (int i = 0; i < n; i++)
        A[i] = (int *)malloc(sizeof(int) * m);

    for (int i = 0; i < n; i++)
    {
        printf("\n");

        for (int j = 0; j < m; j++)
        {

            A[i][j] = rand() % (b - a + 1) + a;

            printf("%d \t", A[i][j]);
        }
    }

    unsigned result = fun(A, n, m, y);

    printf("\nCi sono %u colonne con media minore o uguale a y \n", result);

    free(A);
}