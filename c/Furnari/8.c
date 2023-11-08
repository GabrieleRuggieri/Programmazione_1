/*
    Scrivere un programma in C che:
    - A prenda in input come argomenti da linea di comando tre interi positivi “n”, “m” e
    “p”. Il programma deve controllare che i parametri inseriti sono nel numero corretto
    e che si tratti di interi positivi, stampando errori su standard output e terminando il
    programma qualora i parametri non dovessero rispettare i formati previsti;

    - B  definisca un array tridimensionale di interi “A” di dimensioni “n x m x p” in
    allocazione dinamica e lo inizializza con n*m*p valori inseriti da riga di comando
    separati da spazi;

    - C  inizializzi un array di puntatori a interi "B" di lunghezza "n", in modo che
    l’elemento i-esimo di “B”, “B[i]” punti al valore massimo contenuto nella matrice di
    dimensione “m x p” individuata da "A[i]".

    - D inserisca gli elementi puntati da “B” in una pila;

    - E scriva in un file di testo “out.txt” i valori puntati da “B” in senso inverso (effettuare
    operazioni di “pop” sulla pila).
    Specifiche

    --------------------------------------------------------------------------------------------------

    ●readInput: funzione che permette di leggere gli input da riga di comando e gestisca
    opportunamente gli errori, come specificato nel testo;
    ● initArray: funzione che permette di dichiarare l’array A e inizializzarlo con i valori
    inseriti da tastiera;
    ● initB: funzione che permette di inizializzare l’array B come indicato nel testo;
    ● initStack: funzione che permette di inizializzare la pila dai valori di B;
    ● saveStack: funzione che permette di scrivere i valori della pila su file in senso
    inverso.

    ./main 5 2 3 < input.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct parameters
{
    int n;
    int m;
    int p;
};

int get(char *s)
{
    char **end = malloc(sizeof(char *));
    int num = (int)strtol(s, end, 0);
    if (!*end || num <= 0)
    {
        fprintf(stderr, "Errore: i parametri inseriti devono essere dei numeri interi positivi.\n");
        exit(-1);
    }
    return num;
}

struct parameters readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Errore: il numero di parametri deve essere tre.\n");
        fprintf(stderr, "Uso corretto: %s n m p.\n", argv[0]);
        exit(-1);
    }
    struct parameters p = {get(argv[1]), get(argv[2]), get(argv[3])};
    return p;
}

int ***initArray(int n, int m, int p)
{
    int ***A = calloc(n, sizeof(int **));
    for (int i = 0; i < n; i++)
    {
        A[i] = calloc(m, sizeof(int *));
        for (int j = 0; j < m; j++)
        {
            A[i][j] = calloc(p, sizeof(int));
            for (int k = 0; k < p; k++)
            {
                scanf("%d", &A[i][j][k]);
            }
        }
    }
    return A;
}

int **initB(int ***A, int n, int m, int p)
{
    int **B = calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        int *max = &A[i][0][0];
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < p; k++)
            {
                if (A[i][j][k] > *max)
                    max = &A[i][j][k];
            }
        }
        B[i] = max;
    }
    return B;
}

struct node
{
    int data;
    struct node *next;
};

typedef struct node Node;

void push(Node **head, int x)
{
    Node *tmp = *head;
    *head = malloc(sizeof(Node *));
    (*head)->next = tmp;
    (*head)->data = x;
}

bool empty(Node *head)
{
    return head == NULL;
}

int pop(Node **head)
{
    if (empty(*head))
        return -1;
    int out = (*head)->data;
    Node *tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return out;
}

Node **initStack(int **B, int n)
{
    Node **head = malloc(sizeof(Node *));
    *head = NULL;
    for (int i = 0; i < n; i++)
    {
        push(head, *B[i]);
    }
    return head;
}

void saveStack(Node **head)
{
    FILE *f = fopen("out.txt", "w");
    while (!empty(*head))
    {
        int x = pop(head);
        fprintf(f, "%d\n", x);
    }
}

int main(int argc, char *argv[])
{
    struct parameters p = readInput(argc, argv);
    int ***A = initArray(p.n, p.m, p.p);
    int **B = initB(A, p.n, p.m, p.p);
    Node **head = initStack(B, p.n);
    saveStack(head);
}