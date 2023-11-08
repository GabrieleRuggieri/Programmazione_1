#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 3
#define m 4

unsigned fun(int A[n][m], double y)
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

    int a = 1, b = 5;

    int A[n][m]; // allocazione automatica (o statica) --> Stack uno dietro l'altra

    double y = 3.2;
    //double y = rand() % (b - a + 1) + a;

    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        printf("\n");

        for (int j = 0; j < m; j++)
        {

            A[i][j] = rand() % (b - a + 1) + a;

            printf("%d \t", A[i][j]);
        }
    }

    unsigned result = fun(A, y);

    printf("\nCi sono %u colonne con media minore o uguale a y \n", result);
}