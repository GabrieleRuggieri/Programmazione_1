/*
    Scrivere un programma in C che:
    - A prenda un input da tastiera (argomenti della funzione main) costituito da un intero
    positivo N in [10,20], e due numeri in virgola mobile positivi x,y. Dovra' essere 5.0 <
    x < y < 30.0; se gli argomenti a riga di comando non rispondono ai suddetti requisiti,
    il programma stampa un messaggio di errore sullo standard error e termina la
    propria esecuzione;

    - B allochi dinamicamente una matrice A di numeri double pseudo-casuali in [x,y] di
    dimensioni N x N;

    - C calcoli il minimo degli elementi della diagonale principale della matrice (sia mind),
    e il massimo valore degli elementi della diagonale secondaria della matrice stessa
    (sia maxd); si restituisca inoltre il numero di elementi della matrice aventi valori in
    [mind, maxd];

    - D allochi dinamicamente un array di double e lo riempia con tutti gli elementi di A
    nell'intervallo [mind, maxd];

    - E ordini l'array mediante un algoritmo a scelta tra selection sort e insertion sort;

    - F  stampi l’array sullo standard output, insieme alla media aritmetica dei suoi
    elementi.

    ------------------------------------------------------------------------------------------

    - readInput: funzione che prenda in input gli argomenti argv ed argc della funzione
    main, controlli i requisiti dei parametri e restituisca un record (una struct) che
    contiene tali parametri. Verificare che i requisiti dei parametri siano rispettati come
    specificato nel punto A. Nel caso in cui i requisiti non fossero specificati, stampare
    un opportuno messaggio di errore e terminare il programma;

    - genDouble: genera un numero double in un intervallo specificato mediante
    parametri formali;

    - genMatrix: funzione che crea e restituisce una matrice con elementi double
    generati dalla funzione genDouble;

    - computeMinMax: calcola mind e maxd e restituisce il numeri di elementi che
    ricadono nell’intervallo [mind, maxd] come specificato nel punto C. La funzione
    permette di restituire al chiamante anche i valori di mind e maxd;

    - createArray: creazione e riempimento array come specificato nel punto D;

    - sortArray: ordinamento dell’array come specificato nel punto E;

    - printArray: stampa dell’array come specificato nel punto F.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct Args
{
    int N;
    float x, y; // 5.0 < x < y < 30.0
} Args;

Args readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Errore: numero non corretto di parametri\n");
        exit(-1);
    }

    if (atoi(argv[1]) < 10 || atoi(argv[1]) > 20)
    {
        fprintf(stderr, "Errore: N deve essere in [10, 20]\n");
        exit(-1);
    }

    if (atof(argv[2]) < 0)
    {
        fprintf(stderr, "Errore: x deve essere positivo\n");
        exit(-1);
    }

    if (atof(argv[3]) < 0)
    {
        fprintf(stderr, "Errore: y deve essere positivo\n");
        exit(-1);
    }

    if (atof(argv[2]) < 5.0 || atof(argv[2]) > atof(argv[3]) || atof(argv[3]) < atof(argv[2]) || atof(argv[3]) > 30.0)
    {
        fprintf(stderr, "Errore: x deve essere compreso tra 5.0 e y\n");
        exit(-1);
    }

    Args p;

    p.N = atoi(argv[1]);
    p.x = atof(argv[2]);
    p.y = atof(argv[3]);

    return p;
}

double genDouble(float x, float y)
{
    double d = ((double)get_random() / UINT_MAX) * (y - x) + x;

    return d;
}

double **genMatrix(int N, float x, float y)
{
    double **M = (double **)malloc(sizeof(double *) * N);
    for (int i = 0; i < N; i++)
    {
        M[i] = (double *)malloc(sizeof(double) * N);
        for (int j = 0; j < N; j++)
        {
            M[i][j] = genDouble(x, y);
        }
    }
    return M;
}

void printMatrix(double **M, int dim1, int dim2)
{
    for (int i = 0; i < dim1; i++)
    {
        printf("\n\n");
        for (int j = 0; j < dim2; j++)
        {
            printf("%lf ", M[i][j]);
        }
    }
}

int computeMinMax(double **M, int N, double *mind, double *maxd)
{
    int counter = 0;

    *mind = M[0][0];
    *maxd = M[0][N - 1];

    for (int i = 0; i < N; i++)
    {
        if (M[i][i] < *mind)
            *mind = M[i][i];
        if (M[i][N - 1 - i] > *maxd)
            *maxd = M[i][N - 1 - i];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (M[i][j] >= *mind && M[i][j] <= *maxd)
                counter++;
        }
    }
    return counter;
}

double *createarray(double **M, int N, int count, double mind, double maxd)
{
    double *array = (double *)malloc(sizeof(double) * count);

    int index = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (M[i][j] >= mind && M[i][j] <= maxd)
                array[index++] = M[i][j];
        }
    }
    return array;
}

void printArray(double *array, int dim)
{
    double avg = 0.0;
    for (int i = 0; i < dim; i++)
    {
        printf("%lf\n", array[i]);
        avg += array[i];
    }

    avg /= dim;

    printf("\nMedia: %lf", avg);
}

void sortArray(double arr[], int size) // insertion sort
{
    for (int i = 1; i < size; i++)
    {
        double key = arr[i];
        int j = i - 1;

        // compare key with elements on the left
        while (key < arr[j] && j >= 0)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void swap(double *x, double *y)
{
    double tmp = *x;
    *x = *y;
    *y = tmp;
}

void sortArray2(double arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            // select the min element in each loop
            if (arr[j] < arr[min_index])
                min_index = j;
        }

        // put min at the correct position
        swap(&arr[min_index], &arr[i]);
    }
}

int main(int argc, char *argv[])
{
    Args d = readInput(argc, argv);

    double mind, maxd;

    double **matrix = genMatrix(d.N, d.x, d.y);
    printMatrix(matrix, d.N, d.N);

    printf("\n\n");

    int a = computeMinMax(matrix, d.N, &mind, &maxd);

    printf("min: %lf\n", mind);

    printf("max: %lf\n", maxd);

    printf("counter: %d\n", a);

    double *arr = createarray(matrix, d.N, a, mind, maxd);

    sortArray(arr, a);

    printArray(arr, a);
}