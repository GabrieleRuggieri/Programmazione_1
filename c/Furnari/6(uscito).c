/*
    Scrivere un programma in C che:
    - A prenda come argomenti da riga di comando il nome di un file di testo di input
    “input” (es. “input.txt”) e il nome di un file di testo di output “output” (es. “output.txt”).
    Si assuma che i nomi dei file non superano i 255 caratteri.

    - B  legga una matrice A di puntatori float di dimensioni n x m dal file “input”. Si
    assuma che il file contenga un numero di righe di testo pari a n e che ogni riga
    contenga m valori separati da spazi. Il programma dovrà inferire le dimensioni n e
    m dal file di input e riempire opportunamente i valori della matrice;

    - C elimini dalla matrice i valori di A che sono superiori ai valori medi delle righe
    corrispondenti (far puntare a NULL i puntatori relativi ai valori identificati e liberare
    la relativa memoria);

    - D inserisca i valori puntati dai puntatori non nulli in A in un array di float;

    - E  scriva i valori dell’array sul file “output” il cui nome è stato passato come
    argomento da riga di comando (es “output.txt”).

    -----------------------------------------------------------------------------------------------------

    - readParameters: funzione che permetta di leggere i parametri da riga di comando,
    verificando che rispettino i criteri specificati nel punto A, gestendo eventuali
    messaggi di errore e terminando il programma ove opportuno;

    - createMatrix: funzione che permetta di creare la matrice A a partire dal nome del
    file di input;

    - sparsify: funzione che permetta di mettere a NULL gli opportuni puntatori di A
    (come da punto C);

    - collect: funzione che permetta di creare e riempire l’array di float come descritto nel
    punto D;

    - writeToFile: funzione che permetta di scrivere i valori della lista su file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct parametri
{
    char input[255];
    char output[255];
};

struct parametri readParameters(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Errore: numero di parametri non corretto.\n");
        fprintf(stderr, "Uso corretto: %s input_file output_file,\n", argv[0]);
        exit(-1);
    }
    struct parametri p;

    strcpy(p.input, argv[1]);
    strcpy(p.output, argv[2]);

    return p;
}
float ***createMatrix(char filename[], int *n, int *m)
{
    char ch;
    *n = 0;
    *m = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Errore: impossibile aprire file %s.\n", filename);
        exit(-1);
    }

    // Calcola il numero di righe
    while ((ch = fgetc(f)) != EOF)
    {
        if (ch == '\n')
            (*n)++;
    }

    // Check if last character is a newline
    ch = fgetc(f);
    if (ch != '\n')
        (*n)++;

    rewind(f);

    // Calcola il numero di colonne nella prima riga
    while ((ch = fgetc(f)) != '\n')
    {
        if (ch == ' ')
            (*m)++;
    }
    (*m)++; // Aggiungi 1 per l'ultimo valore

    rewind(f);

    // Alloca la matrice
    float ***A = calloc(*n, sizeof(float **));
    for (int i = 0; i < *n; i++)
    {
        A[i] = calloc(*m, sizeof(float *));
        for (int j = 0; j < *m; j++)
        {
            A[i][j] = malloc(sizeof(float));
            fscanf(f, "%f", A[i][j]);
        }
    }
    fclose(f);
    return A;
}

void sparsify(float ***A, int n, int m)
{
    for (int i = 0; i < n; i++)
    { // righe
        float mean = 0;
        int count = 0;
        for (int j = 0; j < m; j++)
        {
            if (A[i][j])
            {
                mean += *A[i][j];
                count++;
            }
        }
        mean /= count;
        for (int j = 0; j < m; j++)
        {
            if (A[i][j] && *A[i][j] > mean)
            {
                float *tmp = A[i][j];
                A[i][j] = NULL;
                free(tmp);
            }
        }
    }
}

float *collect(float ***A, int n, int m, int *num)
{
    *num = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (A[i][j])
                (*num)++;
        }
    }

    float *out = calloc(*num, sizeof(float));

    int c = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (A[i][j])
                out[c++] = *A[i][j];
        }
    }
    return out;
}

void writeToFile(char output[], float *array, int n)
{
    FILE *f = fopen(output, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%.2f\n", array[i]);
    }
}

int main(int argc, char *argv[])
{
    struct parametri p = readParameters(argc, argv);

    int N, M;

    float ***A = createMatrix(p.input, &N, &M);

    sparsify(A, N, M);

    int num;

    float *out = collect(A, N, M, &num);

    writeToFile(p.output, out, num);
}