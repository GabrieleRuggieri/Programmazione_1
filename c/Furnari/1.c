/*
    Si scriva un programma C che:
    - A prenda un input da tastiera (argomenti della funzione main()) un intero k in [10,15], un
    carattere w in [‘a’-’z’] e due interi N ed M in [4,8]; se gli argomenti a riga di comando non
    rispondono ai suddetti requisiti, il programma  stampa un messaggio di errore sullo standard
    error e termina la propria esecuzione con codice di errore -1;
    
    - B allochi dinamicamente una matrice S di stringhe (char*) di dimensioni N x M;

    - C riempia  la matrice S con NxM stringhe di lunghezza k composte di caratteri pseudo-
    casuali in [a-z];
    
    - D ordini ogni colonna della matrice S in modo crescente (ordinamento lessicografico) con
    un algoritmo di ordinamento a scelta tra Insertion Sort e Bubble Sort;

    - E stampi la matrice sullo standard output;
    
    - F stampi sullo standard output la stringa (e gli indici all'interno della matrice) che contiene il
    maggior numero di occorrenze del simbolo w. Queste ultime vanno sostituite, sullo standard
    output, con il carattere '*'.
    

    --------------------------------------------------------------------------------------------------------


    - readInput: funzione che prende in input il numero argc e il vettore argv della funzione
    main(), che controlli la presenza ed i requisiti degli argomenti k, w, N ed M, e che li
    inserisca in un record (struct) da restituire allo user code (funzione main). La funzione deve
    gestire correttamente gli errori relativi a input non corretti;

    - allocateS: funzione per allocazione dinamica della matrice di dimensioni NxM, tale matrice
    va restituita come dato di ritorno al chiamante (funzione main());

    - genString: funzione che restituisce una stringa della lunghezza specificata con caratteri
    pseudo-casuali in un ben determinato insieme specificato mediante opportuni parametri
    formali;

    - fillS: funzione di riempimento della matrice S come specificato nel punto C;

    - sortS: funzione di ordinamento della matrice come specificato nel punto D; NB: si faccia
    uso, al suo interno, della funzione di libreria strcmp();

    - printMatrix: funzione per la stampa della matrice S;

    - printMax: funzione per la stampa della stringa contenente il maggior numero di occorrenze
    del simbolo w come specificato nel punto F.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Args
{
    int k;  //[10,15]
    char w; //[a-z]
    int N;  //[4,8]
    int M;  //[4,8]

} Args;

Args readInput(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Erorre: numero errato di argomenti\n");
        exit(-1);
    }

    Args p;
    p.k = atoi(argv[1]);
    p.w = argv[2][0];
    p.N = atoi(argv[3]);
    p.M = atoi(argv[4]);

    if (p.k < 10 || p.k > 15)
    {
        fprintf(stderr, "Errore: k deve essere in [10,15]\n");
        exit(-1);
    }

    if (p.w < 'a' || p.w > 'z')
    {
        fprintf(stderr, "Errore: w deve essere in [a,z]\n");
        exit(-1);
    }

    if (p.N < 4 || p.N > 8)
    {
        fprintf(stderr, "Errore: N deve essere in [4,8]\n");
        exit(-1);
    }

    if (p.M < 4 || p.M > 8)
    {
        fprintf(stderr, "Errore: M deve essere in [4,8]\n");
        exit(-1);
    }

    return p;
}

char ***allocateS(int dim1, int dim2)
{
    char ***S = (char ***)malloc(sizeof(char **) * dim1);
    for (int i = 0; i < dim1; i++)
    {
        S[i] = (char **)malloc(sizeof(char *) * dim2);
    }
    return S;
}

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

char *genString(int len)
{
    char *stringa = (char *)malloc(sizeof(char) * len);

    for (int i = 0; i < len; i++)
    {
        stringa[i] = get_random() % ('z' - 'a' + 1) + 'a';
    }
    return stringa;
}

void fillS(char ***S, int n, int m, int k)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            S[i][j] = genString(k);
        }
    }
}

void sortS(char ***S, int n, int m) // bubble sort
{
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int k = i + 1; k < n; k++)
            {
                if ((strcmp(S[i][j], S[k][j]) > 0))
                {
                    char *tmp = S[i][j];
                    S[i][j] = S[k][j];
                    S[k][j] = tmp;
                }
            }
        }
    }
}

void sortS2(char ***S, int n, int m) // insertion sort
{
    for (int j = 0; j < m; j++)
    {
        for (int i = 1; i < n; i++)
        {
            char *key = S[i][j];
            int k = i - 1;

            while (k >= 0 && strcmp(key, S[k][j]) < 0)
            {
                S[k + 1][j] = S[k][j];
                k--;
            }
            S[k + 1][j] = key;
        }
    }
}

void sortS3(char ***S, int n, int m) // selection sort
{
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            int min_index = i;
            for (int k = i + 1; k < n; k++)
            {
                if (strcmp(S[k][j], S[min_index][j]) < 0)
                    min_index = k;
            }
            char *tmp = S[i][j];
            S[i][j] = S[min_index][j];
            S[min_index][j] = tmp;
        }
    }
}

void printMatrix(char ***S, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n");
        for (int j = 0; j < m; j++)
        {
            fprintf(stdout, "%s  ", S[i][j]);
        }
    }
}

void printMax(char ***S, int dim1, int dim2, char c)
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

    fprintf(stdout, "\n\n%s %d %d\n", max_stringa, index1, index2);

    for (int i = 0; i < strlen(max_stringa); i++)
    {
        if (max_stringa[i] == c)
            max_stringa[i] = '*';
    }

    fprintf(stdout, "\n%s %d %d\n", max_stringa, index1, index2);
}

int main(int argc, char *argv[])
{
    Args d = readInput(argc, argv);

    char ***S = allocateS(d.N, d.M);

    fillS(S, d.N, d.M, d.k);

    sortS(S, d.N, d.M);

    printMatrix(S, d.N, d.M);

    printMax(S, d.N, d.M, d.w);
}