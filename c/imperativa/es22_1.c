/*
    1) Si generi una matrice di dimensione N×M– con N ed M a piacere –
    di numeri double.

    2) Si codifichi una funzione che prenda in input la matrice e crei un file
    contenente tale matrice in formato testo. In particolare, la prima riga di
    tale file dovr`a contenere i due numeri N ed M.

    3) Si codifichi una funzione in grado di leggere un file come quello creato
    al punto precedente e quindi di caricare una tale matrice in memoria.

    4) Si codifichi una ulteriore funzione che, data una matrice N×M, ne
    calcoli la sua trasposta.
    
    5) Si usi infine la funzione codificata al punto due per salvare tale
    matrice trasposta su file
*/

#include <stdio.h>
#include <stdlib.h>

struct input
{
    int n, m;
};

struct input readInput(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Sono stati immessi troppi o troppi pochi input.");
        exit(-1);
    }
    if (atoi(argv[1]) < 1 || atoi(argv[1]) > 25)
    {
        fprintf(stderr, "Il primo numero deve essere compreso tra 1 e 25.");
        exit(-1);
    }
    if (atoi(argv[2]) < 1 || atoi(argv[2]) > 25)
    {
        fprintf(stderr, "Il secondo numero deve essere compreso tra 1 e 25.");
        exit(-1);
    }
    struct input e1;
    e1.n = atoi(argv[1]);
    e1.m = atoi(argv[2]);
    return e1;
}
double **createMatrix(int rows, int columns)
{
    double **S = malloc(sizeof(double *) * rows);
    for (int i = 0; i < rows; i++)
    {
        S[i] = malloc(sizeof(double) * columns);
    }
    return S;
}

double genDouble(int n, int m)
{
    if (n < m)
    {
        double tmp = m;
        m = n;
        n = tmp;
    }
    double l = rand() / (RAND_MAX * 1.0) * (n - m) + m;
    return l;
}

void fillMatrix(double **matrix, int rows, int columns, int n, int m)
{
    if (!matrix)
    {
        fprintf(stderr, "La matrice e' vuota.");
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = genDouble(n, m);
        }
    }
}

void printOnFile(double **S, int rows, int columns, const char *file_name)
{
    if (!S)
    {
        fprintf(stderr, "La matrice e' vuota.");
        return;
    }
    FILE *fp = fopen(file_name, "w");
    fprintf(fp, "%d %d", rows, columns);
    if (!fp)
    {
        fprintf(stderr, "Errore nell'apertura del file.");
        return;
    }
    for (int i = 0; i < rows; i++)
    {
        fprintf(fp, "\n");
        for (int j = 0; j < columns; j++)
        {
            fprintf(fp, "%.2lf ", S[i][j]);
        }
    }
    fclose(fp);
    return;
}

double **readFile(const char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    if (!fp)
    {
        fprintf(stderr, "Errore nell'apertura del file.");
        return NULL;
    }
    int n, m;

    if (fscanf(fp, "%d %d", &n, &m) != 2)
    {
        perror("\nERROR!");
        exit(-1);
    }
    double **S = createMatrix(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(fp, "%lf", &S[i][j]);
        }
    }
    fclose(fp);
    return S;
}
double **trasposta(double **S, int rows, int columns)
{
    if (!S)
    {
        perror("Error!");
        return NULL;
    }
    double **M = malloc(sizeof(double *) * columns);
    for (int i = 0; i < columns; i++)
    {
        M[i] = malloc(sizeof(double) * rows);
    }
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            M[i][j] = S[j][i];
        }
    }
    return M;
}
int main(int argc, char *argv[])
{
    struct input inp = readInput(argc, argv);

    double **matrix = createMatrix(inp.n, inp.m);
    fillMatrix(matrix, inp.n, inp.m, 1, 100);
    printOnFile(matrix, inp.n, inp.m, "input.txt");
    double **S = readFile("matrix.txt");
    double **T = trasposta(S, inp.n, inp.m);
    printOnFile(T, inp.m, inp.n, "new_input.txt");
}