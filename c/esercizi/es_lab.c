/*
    - siano N ed M (N>1, M>1) due numeri in input a riga di comando
    (argomenti della funzione main) che rappresentano
    la dimensioni di una matrice;

    - si definisca una funzione di allocazione allocaMatrice()
    che sia in grado di allocare sullo HEAP una matrice di elementi
    double di dimensione N x M e che restituisca tale matrice al chiamante;

    - si definisca una ulteriore funzione genDouble() che permetta di generare
    numeri double compresi tra 5.0 e 20.0;

    - si usi la funzione genDouble() per inizializzare la matrice con valori
    generati dalla funzione stessa;

    - si definisca una funzione max(V, j) che restituisca
    il massimo valore della colonna di indice j della matrice V;

    - si definisca una struttura dati dinamica Stack (mediante lista semplice concatenata) ed opportune funzione push(), pop(), stackEmpty(), e si operi
    sullo stack inserendo tutti gli elementi restituiti dalla invocazione della funzione max(V, j) su tutte le colonne della matrice;

    - si stampi il contenuto delo stack, dall'elemento sul top fino
    all'elemento alla base delo stack;

    - Si calcoli la media di di tutti gli elementi dello stack mediante
    invocazioni della funzione pop(), fino a svuotare lo stack.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double genDouble()
{
    int a = 50, b = 200;
    double x = ((rand() % (b - a + 1) + a) / 10) * 1.0;

    return x;
}

double **allocaMatrice(double **M, int n, int m)
{
    M = (double **)malloc(sizeof(double *) * n);
    for (unsigned int i = 0; i < n; i++)
    {
        M[i] = (double *)malloc(sizeof(double) * m);

        for (unsigned int j = 0; j < m; j++)
        {
            M[i][j] = genDouble();
        }
    }

    return M;
}

double max(double **A, int j){
    
}

int main()
{

    srand(time(NULL));

    double **A;
    int N, M;

    printf("Inserisci le dimensionie della matrice N x M\n");
    scanf("%d %d", &N, &M);

    A = allocaMatrice(A, N, M);

    for (int i = 0; i < N; i++)
    {
        printf("\n");

        for (int j = 0; j < M; j++)
        {
            printf("%.1lf\t", A[i][j]);
        }
    }

    printf("\n\n");

    return 0;
}