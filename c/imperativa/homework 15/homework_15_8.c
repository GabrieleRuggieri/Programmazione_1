/*

    matrice A di double nxn, e un float delta.
    Restituisce il numero di elementi della diagonale secondaria
    tali che il valore ass. della differenza tra il valore della diagonale e la sommacol/n, < delta

*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

unsigned fun(double **A, int n, float delta)
{
    unsigned counter = 0;
    double sum;

    for (int k = n - 1; k > 0; k--)
    {
        sum = 0.0;
        for (int i = 0; i < n; i++)
        {
            sum += A[i][k];
        }
        if ((k - (sum / n)) < delta)
            counter++;
    }

    return counter;
}

int main()
{

    int n = 5;

    int a = 1, b = 9;

    float val = 
    0.2;
    double **A = (double **)malloc(sizeof(double *) * n); // allocazione dinamica --> Heap
    for (int i = 0; i < n; i++)
        A[i] = (double *)malloc(sizeof(double) * n);

    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        printf("\n");

        for (int j = 0; j < n; j++)
        {

            A[i][j] = rand() % (b - a + 1) + a;

            printf("%lf \t", A[i][j]);
        }
    }

    unsigned x = fun(A, n, val);

    printf("\n%u\n", x);

    free(A);
}