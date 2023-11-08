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

    -----------------------------------------------------------------------------------------------

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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct row
{
    char word[101];
    int count;
} row;

typedef struct Node
{
    row key;
    struct Node *next;
} Node;

void printNode(Node *node)
{
    if (!node || !node->key.word)
    {
        fprintf(stderr, "Error Node\n");
        exit - 1;
    }
    printf("[(%s) --- %d]", node->key.word, node->key.count);
}

typedef struct List
{
    Node *head;
} List;

bool isEmpty(List *list)
{
    return !(list->head);
}

void insertHead(List *list, row val)
{
    Node *toinsert = (Node *)malloc(sizeof(Node));
    toinsert->key = val;

    if (isEmpty(list))
    {
        list->head = toinsert;
        return;
    }
    toinsert->next = list->head;
    list->head = toinsert;
}

void insertTail(List *list, row val)
{
    Node *toinsert = (Node *)malloc(sizeof(Node));
    toinsert->key = val;

    if (isEmpty(list))
    {
        insertHead(list, val);
        return;
    }

    Node *cur = list->head;

    while (cur->next)
        cur = cur->next;
    cur->next = toinsert;
}

void insertInOrder(List *list, row val)
{
    if (isEmpty(list) || val.count <= list->head->key.count)
    {
        insertHead(list, val);
        return;
    }

    Node *cur = list->head;
    while (cur->next && val.count >= list->head->key.count)
    {
        if (val.count < cur->next->key.count)
            break; // interrompe il ciclo while
        cur = cur->next;
    }

    if (!cur->next)
    {
        insertTail(list, val);
        return;
    }

    Node *toinsert = (Node *)malloc(sizeof(Node));
    toinsert->key = val;
    toinsert->next = cur->next;
    cur->next = toinsert;
    return;
}

void removeHead(List *list)
{
    if (isEmpty(list))
    {
        puts("\nEmpty List\n");
        return;
    }
    Node *toremove = list->head;
    list->head = list->head->next;
    free(toremove);
}

void printList(List *list)
{
    if (isEmpty(list))
    {
        puts("\nEmpty List\n");
        return;
    }

    Node *cur = (Node *)malloc(sizeof(Node));
    cur = list->head;
    puts("\nHead");
    while (cur)
    {
        printf("\n");
        printNode(cur);
        cur = cur->next;
    }
    puts("\n\nNIL");
}

void ReadN(int *n)
{
    int c = 0;
    do
    {
        puts("Inserisci un numero da tastiera : ");
        scanf("%d", n);
        if (n <= 0)
        {
            fprintf(stderr, "Errore nell'inserimento di n, tentativo %d!\n", ++c);
            if (c == 3)
                exit(-1);
        }
    } while (n <= 0);
    n = 0;
}

List *ReadFile(const char *path)
{
    FILE *file = fopen(path, "r");

    List *list = malloc(sizeof(List));
    row tmp;
    char s[1000];
    char *tok = NULL;
    char *firstTok = NULL;

    while (fgets(s, 1000, file))
    {
        tok = strtok(s, " \n");
        firstTok = tok;
        int count = 0;
        while (tok)
        {
            if (strcmp(firstTok, tok) == 0)
                count++;
            tok = strtok(NULL, " \n");
        }
        if (firstTok)
        {
            tmp.count = count;
            strcpy(tmp.word, firstTok);
            insertInOrder(list, tmp);
        }
    }
    fclose(file);
    return list;
}

void FilterList(List *list, int n)
{
    Node *cur = (Node *)malloc(sizeof(Node));
    cur = list->head;
    while (cur && cur->key.count < n)
    {
        removeHead(list);
        cur = cur->next;
    }
    puts("\n...filter...\n");
    printList(list);
}

int main()
{
    int n = 0;
    ReadN(&n);
    List *list = ReadFile("input.txt");
    printList(list);
    FilterList(list, n);
}