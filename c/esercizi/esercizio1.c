/*
    - A (8 punti). Il programma prenda un input da tastiera (argomenti della funzione
    main()) un intero k in [10,15], un carattere w in [‘a’-’z’] e due interi N ed M in [4,8]; se
    gli argomenti a riga di comando non rispondono ai suddetti requisiti, il programma
    stampa un messaggio di errore sullo standard error e termina la propria esecuzione;
    - B (4 punti). Allocazione dinamica di una matrice (sia S) di stringhe (char *) di
    dimensioni N x M;
    - C (5 punti). Si riempia la matrice S con NxM stringhe di lunghezza k composte di
    caratteri pseudo-casuali in [a-z];
    - D (6 punti). Si ordini ogni colonna della matrice S in modo crescente (ordinamento
    lessicografico) con un algoritmo di ordinamento a scelta tra Insertion Sort e Bubble
    Sort.
    - E (2 punti). Si stampi la matrice sullo standard output.
    - F (5 punti). Si stampi sullo standard output la stringa (e gli indici all'interno della
    matrice) che contiene il maggior numero di occorrenze del simbolo w. Queste ultime
    vanno sostituite, sullo standard output, con il carattere '*'.


    - puntoA(): funzione che prenda il vettore argv ed il numero argc della funzione
    main(), che controlli la presenza ed i requisiti degli argomenti k, w, N ed M, e che li
    inserisca in un record (struct) da restituire allo user code (funzione main);
    - puntoB(): - funzione per allocazione dinamica della matrice di dimensioni NxM, tale
    matrice va restituita come dato di ritorno al chiamante (funzione main()).
    - genString() - restituisca una stringa della lunghezza specificata con caratteri
    pseudo-casuali in un  ben determinato insieme specificato mediante opportuni
    parametri formali;
    - puntoC() - funzione di riempimento della matrice S come specificato nel punto C;
    - puntoD() - funzione di ordinamento della matrice come specificato nel punto D; NB:
    si faccia uso, al suo interno, della funzione di libreria strcmp();
    - puntoE() - funzione per il punto E;
    - puntoF() - funzione per il punto F.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*

    double a = 2.2;
    double b = 7.5;
    (b-a)*(1.0*rand()/RAND_MAX)+a;

    1.0 * rand()/RAND_MAX;

    rand()%(b-a+1)+a;

    gcc [nome_programma].c –o [nome_file_eseguibile]
    ./[nome_file_eseguibile]

*/

typedef struct Args
{
    int k;
    char w;
    int N;
    int M;
} Args;

Args puntoA(int a, char **s)
{
    // Verifica che ci siano esattamente 4 argomenti
    if (a != 5)

        fprintf(stderr, "Errore: numero di argomenti non corretto\n");

    // Verifica che gli argomenti soddisfino i requisiti
    if (atoi(s[1]) < 10 || atoi(s[1]) > 15)
    {
        fprintf(stderr, "Errore: k deve essere in [10, 15]\n");
        exit(-1);
    }

    if (s[2][0] < 'a' || s[2][0] > 'z')
    {
        fprintf(stderr, "Errore: w deve essere in ['a', 'z']\n");
        exit(-1);
    }

    if (atoi(s[3]) < 4 || atoi(s[3]) > 8)
    {
        fprintf(stderr, "Errore: N deve essere in [4, 8]\n");
        exit(-1);
    }

    if (atoi(s[4]) < 4 || atoi(s[4]) > 8)
    {
        fprintf(stderr, "Errore: M deve essere in [4, 8]\n");
        exit(-1);
    }

    // Inizializza una struttura di tipo Args
    Args argomenti;

    // Converte gli argomenti da stringa a interi/carattere
    argomenti.k = atoi(s[1]);
    argomenti.w = s[2][0];
    argomenti.N = atoi(s[3]);
    argomenti.M = atoi(s[4]);

    // Se tutti i controlli sono stati superati, stampa gli argomenti
    printf("k = %d, w = %c, N = %d, M = %d\n", argomenti.k, argomenti.w, argomenti.N, argomenti.M);

    return argomenti;
}

void stampa(char ***S, int dim1, int dim2)
{
    for (int i = 0; i < dim1; i++)
    {
        printf("\n");
        for (int j = 0; j < dim2; j++)
            printf("%s  ", S[i][j]);
    }
}

char ***puntoB(char ***A, int dim1, int dim2, int len)
{
    A = (char ***)malloc(sizeof(char **) * dim1);
    for (int i = 0; i < dim1; i++)
    {
        A[i] = (char **)malloc(sizeof(char *) * dim2);
        for (int j = 0; j < dim2; j++)
        {

            A[i][j] = (char *)malloc(sizeof(char) * (len + 1));
        }
    }
    return A;
}

char *genString(int len)
{
    char *str;

    str = (char *)malloc(sizeof(len + 1));

    for (int z = 0; z < len; z++)
    {
        str[z] = rand() % ('z' - 'a' + 1) + 'a';
    }
    return str;
}

void puntoC(char ***S, int n, int m, int k)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            S[i][j] = genString(k);
    }
}

void swap(char **x, char **y)
{
    char *temp = *x;
    *x = *y;
    *y = temp;
}

void puntoD(char ***M, int n, int m, int k) // bubblesort
{
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int t = i + 1; t < n; t++)
            {
                if ((strcmp(M[i][j], M[t][j])) > 0)
                    swap(&(M[i][j]), &(M[t][j]));
            }
        }
    }
}

void puntoE(char ***S, int dim1, int dim2)
{
    printf("Standard output:\n\n");
    for (int i = 0; i < dim1; i++)
    {
        printf("\n");
        for (int j = 0; j < dim2; j++)
        {
            fprintf(stdout, "%s", S[i][j]);
            printf("  ");
        }
    }
}

void puntoF(char ***S, int dim1, int dim2, char c)
{
    int index1, index2;
    char *max_stringa;
    int max_count = 0;

    for (int i = 0; i < dim1; i++)
    {
        for (int j = 0; j < dim2; j++)
        {
            int count = 0;
            char *string = S[i][j];
            int string_len = strlen(string);
            for (int k = 0; k < string_len; k++)
            {
                if (string[k] == c)
                {
                    count++;
                }
            }
            if (count > max_count)
            {
                max_count = count;
                max_stringa = string;
                index1 = i;
                index2 = j;
            }
        }
    }
    fprintf(stdout, "%s %d %d \n", max_stringa, index1, index2);
    for (int i = 0; i < strlen(max_stringa); i++)
    {
        if (max_stringa[i] == c)
            max_stringa[i] = '*';
    }
    fprintf(stdout, "%s %d %d", max_stringa, index1, index2);
}

int main(int argc, char *argv[])
{

    Args args = puntoA(argc, argv);

    char ***S = puntoB(S, args.N, args.M, args.k);

    puntoC(S, args.N, args.M, args.k);

    stampa(S, args.N, args.M);

    puntoD(S, args.N, args.M, args.k);

    printf("\n\n");

    stampa(S, args.N, args.M);

    printf("\n\n");

    puntoE(S, args.N, args.M);

    printf("\n\n");

    puntoF(S, args.N, args.M, args.w);

    return 0;
}