/*
    Scrivere un programma in C che:
    - A prenda in input da tastiera (argomenti della funzione main) un intero positivo N in
    [10,20] ed un carattere w; se gli argomenti a riga di comando non rispondono ai
    suddetti requisiti, il programma stampa un messaggio di errore sullo standard error
    e termina la propria esecuzione;

    - B generi, mediante successivi inserimenti, una lista concatenata semplice (ordinata
    in modo crescente - ordinamento lessicografico) che contenga N stringhe con
    caratteri pseudo-casuali in [‘a’-’z’] di lunghezza pseudo-casuale L nell'intervallo
    [5,15];

    - C stampi sullo standard output l'intera lista;

    - D stampi sullo standard output il numero totale di occorrenze del carattere w in tutte
    le stringhe della lista.
    Specifiche

    ---------------------------------------------------------------------------------------------


    - readInput: funzione che prenda in input gli argomenti della funzione main argv ed
    argc, controlli i requisiti dei parametri e restituisca al chiamante un record (struct)
    che contenga tutti i parametri.

    - genString: funzione che restituisca una stringa di caratteri pseudo-casuali
    appartenenti ad un determinato intervallo specificato mediante opportuni parametri
    formali.

    - insertString: funzione che inserisca una stringa nella lista; per tale funzione e’
    possibile usare la funzione di libreria strcmp();

    - genList: funzione che si occupa di creare e riempire la lista di stringhe come
    richiesto nel punto B;

    - printList: funzione che si occupa di stampare la lista a schermo come specificato
    nel punto C;

    - printOcc: funzione che stampa sullo standard output il numero totale di occorrenze
    del carattere w in tutte le stringhe della lista, come specificato nel punto D
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    int N; //[10,20]
    char w;
} Args;

Args readInput(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Errore: numero non corretto di argomenti\n");
        exit(-1);
    }

    if (atoi(argv[1]) < 10 || atoi(argv[1]) > 20)
    {
        fprintf(stderr, "Errore: N in [10,20]\n");
        exit(-1);
    }

    Args p;
    p.N = atoi(argv[1]);
    p.w = *argv[2];

    return p;
}

typedef struct Node
{
    char s[16];
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

void printNode(Node *node)
{
    if (!node)
    {
        fprintf(stderr, "Errore\n");
        exit(-1);
    }
    printf("[%s]", node->s);
}

char *genString()
{

    int L = get_random() % (15 - 5 + 1) + 5;

    char *s = (char *)malloc(sizeof(char) * L);

    for (int i = 0; i < L; i++)
    {
        s[i] = get_random() % ('z' - 'a' + 1) + 'a';
    }
    return s;
}

bool isEmpty(List *list)
{
    return (list->head == NULL);
}

void insertHead(List *list, char *string)
{
    Node *toinsert = (Node *)malloc(sizeof(Node));
    strcpy(toinsert->s, string);
    toinsert->next = NULL;

    if (isEmpty(list))
    {
        list->head = toinsert;
        return;
    }
    toinsert->next = list->head;
    list->head = toinsert;
}

void insertTail(List *list, char *string)
{
    Node *toinsert = (Node *)malloc(sizeof(Node));
    strcpy(toinsert->s, string);
    toinsert->next = NULL;

    if (isEmpty(list))
    {
        insertHead(list, string);
        return;
    }

    Node *cur = list->head;
    while (cur->next)
        cur = cur->next;
    cur->next = toinsert;
}

void insertString(List *list, char *val)
{
    if (isEmpty(list) || strcmp(val, list->head->s) < 0)
    {
        insertHead(list, val);
        return;
    }

    Node *cur = list->head;
    while (cur->next && strcmp(val, cur->s) >= 0)
    {
        if (strcmp(val, cur->next->s) < 0)
            break;
        cur = cur->next;
    }

    if (!cur->next)
    {
        insertTail(list, val);
        return;
    }

    Node *toinsert = (Node *)malloc(sizeof(Node));
    strcpy(toinsert->s, val);
    toinsert->next = cur->next;
    cur->next = toinsert;
    return;
}

List *genList(int N)
{
    List *list = malloc(sizeof(List));

    for (int i = 0; i < N; i++)
        insertString(list, genString());

    return list;
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

    puts("Head");

    while (cur)
    {
        printf("\n");
        printNode(cur);
        
        cur = cur->next;
    }
    printf("\n\nNIL");
}

void printOcc(List *list, char c)
{
    int count = 0;

    Node *tmp = list->head;
    while (tmp)
    {
        char *string = tmp->s;

        for (int i = 0; i < strlen(string); i++)
        {
            if (string[i] == c)
                count++;
        }
        tmp = tmp->next;
    }
    printf("\n\n%d", count);
}

int main(int argc, char *argv[])
{
    Args v = readInput(argc, argv);
    List *list = genList(v.N);
    printList(list);
    printOcc(list, v.w);
}