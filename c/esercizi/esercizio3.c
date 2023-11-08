#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct parametri
{
    int N;
    float x, y;
} parametri;

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

parametri readInput(int a, char **s)
{
    if (a != 4)
    {
        fprintf(stderr, "Errore: numero di argomenti non corretto");
        exit(-1);
    }

    char **end = malloc(sizeof(char *));
    *end = NULL;

    parametri p;

    p.N = (int)strtol(s[1], end, 0);

    if (!end)
    {
        fprintf(stderr, "Errore: il primo parametro deve essere un intero.\n");
        exit(-1);
    }

    if (p.N < 10 || p.N > 20)
    {
        fprintf(stderr, "Errore: N deve essere nel range [10, 20]");
        exit(-1);
    }

    p.x = strtof(s[2], end);
    if (!end)
    {
        fprintf(stderr, "Errore: il secondo parametro deve essere un float.\n");
        exit(-1);
    }

    p.y = strtof(s[3], end);
    if (!end)
    {
        fprintf(stderr, "Errore: il terzo parametro deve essere un float.\n");
        exit(-1);
    }

    if (p.x < 5.0 || p.x > p.y || p.y < p.x || p.y > 30.0)
    {
        fprintf(stderr, "Errore: il secondo e il terzo parametro devono essere compresi tra 5.0 e 30.0.\n");
        exit(-1);
    }

    return p;
}

double genDouble(float x, float y)
{
    return ((double)get_random() / UINT_MAX) * (y - x) + x;
}

double **genMatrix(int N, float x, float y)
{
    double **A = (double **)malloc(sizeof(double *) * N);

    for (int i = 0; i < N; i++)
    {
        A[i] = (double *)malloc(sizeof(double) * N);
        for (int j = 0; j < N; j++)
        {
            A[i][j] = genDouble(x, y);
        }
    }
    return A;
}

int computeMinMax(double **A, int N, double *mind, double *maxd)
{
    *mind = A[0][0];
    *maxd = A[0][N-1];

    for (int i = 0; i < N; i++)
    {
        if (A[i][i] < *mind)
            *mind = A[i][i];
        if (A[i][N - 1 - i] > *maxd)
            *maxd = A[i][N - 1 - i];
    }

    int count = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] <= *maxd && A[i][j] >= *mind)
            {
                count++;
            }
        }
    }
    return count;
}

double *createArray(double **A, int N, int num, double mind, double maxd)
{
    double *array = (double *)calloc(num, sizeof(double));

    int idx = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] <= maxd && A[i][j] >= mind)
            {
                array[idx++] = A[i][j];
            }
        }
    }
    return array;
}

void sortArray(double *A, int n)
{
    // selection sort
    for (int i = 0; i < n; i++)
    {
        int smallest = i;
        for (int j = i + 1; j < n; j++)
        {
            if (A[j] < A[smallest])
            {
                smallest = j;
            }
        }

        double tmp = A[i];
        A[i] = A[smallest];
        A[smallest] = tmp;
    }
}

void printArray(double *array, int num)
{
    double media = 0;
    for (int i = 0; i < num; i++)
    {
        printf("%f\n", array[i]);
        media += array[i];
    }
    media /= num;
    fprintf(stdout, "Media: %f\n", media);
}

int main(int argc, char *argv[])
{
    parametri p = readInput(argc, argv);

    double **A = genMatrix(p.N, p.x, p.y);

    double min, max;

    int num = computeMinMax(A, p.N, &min, &max);
    double *array = createArray(A, p.N, num, min, max);

    sortArray(array, num);
    printArray(array, num);
}