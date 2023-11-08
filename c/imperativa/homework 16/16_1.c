/*
    matrice M nxm di stringhe, restituisce true se esiste
    almeno una colonna che abbia egual numero di
    stringhe palindrome di una delle righe di M
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

int palindroma(char *A)
{
    int x = 0;
    unsigned low;
    unsigned high = strlen(A) - 1;

    for (low = 0; (A[low] == A[high]) && (low <= high); low++)
        high--;
    if (A[low] == A[high])
        x = 1; // true
    else
        x = 0; // false

    return x;
}

int fun(char ***M, int n, int m)
{

    int x = 0;
    unsigned counterCol, counterRow;
    for (int j = 0; j < m; j++) // con i primi 2 for scorro colonna
    {
        counterCol = 0; // conta palindrome colonna

        for (int i = 0; i < n; i++)
        {

            if ((palindroma(M[i][j])) == 1)
                counterRow++;
            for (int k = 0; k < n; k++) // con gli ultimi 2 for scorro riga
            {
                counterRow = 0; // conta palindrome righe

                for (int l = 0; l < m; l++)
                {
                    if ((palindroma(M[k][l])) == 1)
                        counterCol++;
                }
            }
        }
        if (counterCol == counterRow)
        {
            x = 1;
            return x;
        }
    }

    return x;
}

int main()
{
    int n = 3;
    int m = 4;

    char ***M = (char ***)malloc(sizeof(char **) * n); // allocazione dinamica --> Heap
    for (int i = 0; i < n; i++)
    {
        M[i] = (char **)malloc(sizeof(char *) * m);
        for (int j = 0; j < m; j++)
        {
            M[i][j] = (char *)malloc(sizeof(char));
        }
    }

    M[0][0] = "ciao";
    M[0][1] = "oaic";
    M[0][2] = "lnle";
    M[0][3] = "ewdo";

    M[1][0] = "nove";
    M[1][1] = "opwejd";
    M[1][2] = "ewdpojd";
    M[1][3] = "ewdlkd";

    M[2][0] = "evon";
    M[2][1] = "ewdlkm";
    M[2][2] = "ewdòlk";
    M[2][3] = "ewòdlk";

    int z = fun(M, n, m);
    printf("%i\n", z);
}