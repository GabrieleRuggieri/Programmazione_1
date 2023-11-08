/*
    Scrivere un programma in C che:
    - A prenda in input da tastiera un intero positivo “n”;

    - B legga un file di testo "input.txt". Si assuma che il file di testo contenga sequenze
    di parole separate da spazi. Si assuma una lunghezza massima per ciascuna
    parola pari di 100 caratteri, mentre una lunghezza massima di ciascuna riga pari a
    1000 caratteri. Il programma dovrà creare una lista di struct a partire dal contenuto
    del file. Ogni struct deve rappresentare una riga del file di input e deve contenere
    due campi: una stringa "word” e un intero "count". La stringa "word" deve contenere
    la prima parola nella riga del file di input, mentre "count" deve contenere il numero
    di occorrenze di tale parola nella riga;

    - C una volta creata la lista, elimini da essa le parole aventi un numero di occorrenze
    inferiore a “n”;

    - D  stampi a schermo le parole presenti nella lista con il relativo numero di
    occorrenze.

    --------------------------------------------------------------------------------------------------

    - readN: funzione che permette di leggere l’intero n come parametro passato da riga
    di comando. Questa funzione dovrà gestire correttamente eventuali errori di input,
    stampare   messaggi   di   errore   su   standard   error   e   terminare   il   programma
    opportunamente ove necessario;

    - readFile: funzione che apre il file di input (il cui nome è passato mediante un
    apposito parametro formale), legge le righe e restituisce la lista concatenata di
    struct;

    - filterList: funzione che elimina dalla lista le parole con meno di “n” occorrenze;

    - printList: funzione che stampa il contenuto della lista concatenata.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int readN(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Errore, bisogna passare un parametro intero da riga di comando.\n");
        exit(-1);
    }
    int n = atoi(argv[1]);

    if (n <= 0)
    {
        fprintf(stderr, "Errore: n deve essere positivo\n");
        exit(-1);
    }

    return n;
}

typedef struct
{
    char word[101];
    int count;
} Riga;

typedef struct Node
{
    Riga data;
    struct node *next;
} Node;

bool insertHead(Node **head, Riga r)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
        return false;
    newNode->data = r;
    newNode->next = *head;
    *head = newNode;
    return true;
}

bool insertTail(Node **head, Riga r)
{
    if (*head == NULL)
    {
        return insertHead(head, r);
    }
    Node *ptr = *head;
    while (ptr->next)
    {
        ptr = ptr->next;
    }
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
        return false;
    newNode->data = r;
    newNode->next = NULL;
    ptr->next = newNode;

    return true;
}

Node *readFile(char *name)
{
    Node **head = malloc(sizeof(Node *));
    *head = NULL;

    FILE *f = fopen(name, "r");
    char s[1000];
    bool done = false;
    while (!done)
    {
        char *out = fgets(s, 1000, f);
        if (out != NULL)
        {
            char *tok = strtok(s, " \n");
            char *firstTok = tok;
            int count = 0;
            do
            {
                if (strcmp(firstTok, tok) == 0)
                {
                    count++;
                }

            } while ((tok = strtok(NULL, " \n")));

            Riga r;
            r.count = count;
            strcpy(r.word, firstTok);
            insertTail(head, r);
        }
        else
            done = true;
    }
    return *head;
}

void printList(Node *head)
{
    Node *ptr = head;
    while (ptr)
    {
        Riga *r = &ptr->data;
        printf("%s %d\n", r->word, r->count);
        ptr = ptr->next;
    }
}
bool deleteHead(Node **head)
{
    if (*head)
    {
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return true;
    }
    else
    {

        return false;
    }
}
void filterList(Node **head, int n)
{
    if (*head == NULL)
    {
        return;
    }
    Node *ptr = *head;
    Node *prevPtr = NULL;
    while (ptr)
    {
        if (ptr->data.count < n)
        {
            if (prevPtr == NULL)
            {
                deleteHead(head);
                ptr = *head;
                continue;
            }
            else
            {
                Node *tmp = ptr;
                prevPtr->next = ptr->next;
                free(tmp);
                ptr = prevPtr;
            }
        }
        prevPtr = ptr;
        ptr = ptr->next;
    }
}

int main(int argc, char *argv[])
{
    int n = readN(argc, argv);
    Node **head = malloc(sizeof(Node *));

    *head = readFile("input.txt");
    filterList(head, n);
    printList(*head);
}