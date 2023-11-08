/*
    Definire una struttura (struct) record che contenga un numero in virgola mobile,
    un carattere e due puntatori a caratteri S ed W (due stringhe). Codificare una funzione
    che prenda in input un puntatore ad una tale struttura e che sia in grado di inizializzare
    la struttura con elementi pseudo-casuali. In particolare il campo W dovrà essere inizializzato
    con caratteri appartenenti all’insieme [0-9], il campo S con caratteri in nell’insieme [a-z].
    Invocare opportunamente la funzione all’interno della funzione main.
*/

/*
    Estendere l’esercizio del punto precedente con la definizione di una struttura data che contenga
    un intero chiamato ID, ed un campo di tipo record definito nel precedente esercizio (struttura annidata).
    ID andrà inizializzato sempre con numeri positivi. All’interno della funzione main(), creare un un array
    di N elementi di tipo data, ed inizializzare un numero k ≤ N di elementi di tale array, con k a piacere.
    L’elemento successivo al k-esimo elemento dello array (se k < N), ovvero il primo elemento “vuoto” sarà
    distinguibuile dagli altri perché ID == −1. Codificare una funzione di inizializzazione che prenda in input
    l’indirizzo di un elemento data, che faccia uso della funzione definita nel precedente esercizio, e che sia
    in grado di assegnare ID univoci ad ogni elemento data.
*/

/*
    Estendere il precedente esercizio con la modifica del tipo data in modo che includa anche un campo
    flag che prenda valori definiti in una enumerazione. Questa avrà possibili valori vowels e three.
    Codificare una opportuna funzione che prenda in input l'array di elementi di tipo data per modificare
    ognuno di questi elementi nel seguente modo:
        se il numero di vocali presenti nel campo S > del numero degli elementi divisibili per 3 del campo W
        allora flag = vowels, altrimenti flag = three.
*/

/*
    Estendere il precedente esercizio con la modifica del tipo data in modo che includa anche un campo
    di tipo union di nome FLAG_DATA. La union sarà composta di un campo unsigned short ed un campo char.
    Codificare una opportuna funzione che prenda in input l'array di elementi di tipo data per modificare
    ognuno di questi elementi nel seguente modo:
        se FLAG = VOWELS allora pone in FLAG_DATA la prima vocale presente nel campo S altrimenti
        se FLAG = THREE pone in FLAG_DATA il primo numero divisibile per tre presente nel campo W
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 10

typedef struct record
{
    double num;
    char ch;
    char *S, *W;
} record;

typedef enum flag
{
    VOWELS,
    THREE,
    NONE
} flag;

typedef union flag_data
{
    char first_in_S;
    unsigned short first_in_W;
} flag_data;

typedef struct data
{
    int ID;
    record *r;
    flag FLAG;
    flag_data FLAG_DATA;
} data;

void rand_init(data *d)
{
    d->r = (record *)malloc(sizeof(record));
    d->r->num = rand() / (RAND_MAX * 1.0);
    d->r->ch = 'a' + rand() % 26;
    d->r->S = (char *)calloc(N, sizeof(char));
    d->r->W = (char *)calloc(N, sizeof(char));
    unsigned short vowels = 0, three = 0;
    for (unsigned short i = 0; i < N; i++)
    {
        d->r->S[i] = 'a' + rand() % 26;
        if (d->r->S[i] == 'a' || d->r->S[i] == 'e' || d->r->S[i] == 'i' || d->r->S[i] == 'o' || d->r->S[i] == 'u')
            vowels++;
        d->r->W[i] = '0' + rand() % 10;
        if ((d->r->W[i] - 48) % 3 == 0)
            three++;
    }
    if (vowels > three)
    {
        d->FLAG = VOWELS;
        d->FLAG_DATA.first_in_S = d->r->S[0];
    }
    else if (three > vowels)
    {
        d->FLAG = THREE;
        d->FLAG_DATA.first_in_W = d->r->W[0] - 48;
    }
    else
        d->FLAG = NONE;
}

void print_results(data *d)
{
    printf("\n\nID = %d", d->ID);
    printf("\nnum = %lf", d->r->num);
    printf("\nch = %c", d->r->ch);
    printf("\nS = %s", d->r->S);
    printf("\nW = %s", d->r->W);
    if (d->FLAG == VOWELS)
    {
        printf("\nflag = VOWELS");
        printf("\nflag_data = %c", d->FLAG_DATA.first_in_S);
    }
    else if (d->FLAG == THREE)
    {
        printf("\nflag = THREE");
        printf("\nflag_data = %hu", d->FLAG_DATA.first_in_W);
    }
    else
        printf("\nflag = NONE");
}

void ID_assignement(data *d, int k)
{
    for (unsigned short i = 0; i <= k; i++)
    {
        if (i < k)
        {
            rand_init(&d[i]);
            d[i].ID = i + 1;
        }
        else if ((i == k) && (i != N))
        {
            rand_init(&d[i]);
            d[i].ID = -1;
        }
        else if (i == N)
            break;
        print_results(&d[i]);
    }
}

int main()
{
    srand(time(NULL));
    data d[N];
    int k = rand() % N + 1;
    printf("\nTHE NEXT %d ELEMENTS: ", k);
    ID_assignement(d, k);
}