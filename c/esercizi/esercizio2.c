/*
    - A (8 punti). Il programma prenda un input da tastiera (argomenti della funzione
    main()) un intero positivo N in [10,20] ed un carattere w; se gli argomenti a riga di
    comando non rispondono ai suddetti requisiti, il programma stampa un messaggio di
    errore sullo standard error e termina la propria esecuzione;
    - B (16 punti) si generi, mediante successivi inserimenti, una lista concatenata
    semplice (ordinata in modo crescente - ordinamento lessicografico) che contenga N
    stringhe con caratteri pseudo-casuali in [‘a’-’z’] di lunghezza pseudo-casuale L
    nell'intervallo [5,15];
    - C (3 punti) il programma stampi sullo standard output l'intera lista;
    - D (3 punti) il programma stampi sullo standard output il numero totale di occorrenze
    del carattere w in tutte le stringhe della lista.


    - puntoA() - funzione che prenda in input gli argomenti della funzione main argv ed
    argc, controlli i requisiti dei parametri e restituisca al chiamante un record (struct) che
    contenga tutti i parametri.
    - genString(): funzione che restituisca una stringa di caratteri pseudo-casuali
    appartenenti ad un determinato intervallo specificato mediante opportuni parametri
    formali.
    - insertString(): funzione che inserisca una stringa nella lista; per tale funzione e’
    possibile usare la funzione di libreria strcmp();
    - puntoB(): funzione che si occupa di creare e riempire la lista di stringhe come
    richiesto nel punto B.
    - puntoC().
    - puntoD().
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char w;
} Args;

typedef struct node
{
    char data[16];
    struct node *next;
} node;

Args readinput(int a, char **s)
{
    if (a != 3)
    {
        fprintf(stderr, "Errore: numero di ergomenti non corretto!\n");
        exit(-1);
    }

    char **end = malloc(sizeof(char *)); // esso permette di modificare il puntatore stesso e non solo il valore puntato.
    *end = NULL;

    /*La funzione strtod accetta due argomenti: la stringa da convertire e un puntatore a una variabile in cui verrà memorizzato l'indice del primo carattere non utilizzato nella conversione.
    La funzione restituisce il valore convertito.*/
    // double strtod(const char *str, char **endptr)
    int num = (int)strtod(s[1], end);

    if (num < 10 || num > 15)
    {
        fprintf(stderr, "Errore: N deve essere in [10, 20]\n");
        exit(-1);
    }

    /*
        if (**end) //* !='\0'
        {
            fprintf(stderr, "Error: il primo parametro deve essere un int");
            exit(-1);
        }
    */

    if (!end)
    {
        fprintf(stderr, "Errore, il primo parametro deve essere un intero.\n");
        exit(-1);
    }

    if (strlen(s[2]) != 1)
    {
        fprintf(stderr, "Errore: il secondo parametro deve essere un char\n");
        exit(-1);
    }

    Args p = {atoi(s[1]), s[2][0]};

    return p;
}

void insertHead(node **head, char *string)
{
    if (*head == NULL)
    {
        *head = malloc(sizeof(node));
        strcpy((*head)->data, string);
        (*head)->next = NULL;
    }
    else
    {
        node *new_node = malloc(sizeof(node));
        strcpy(new_node->data, string);
        new_node->next = *head;
        *head = new_node;
    }
}

void insertString(node **head, char *string)
{
    if (*head == NULL)
    {
        insertHead(head, string);
        return;
    }

    node *ptr = *head;
    node *prev = NULL;

    while (ptr && strcmp(ptr->data, string) < 0)
    {
        prev = ptr;
        ptr = ptr->next;
    }

    if (prev == NULL)
    {
        insertHead(head, string);
        return;
    }

    node *new_node = malloc(sizeof(node));

    strcpy(new_node->data, string);
    prev->next = new_node;
    new_node->next = ptr;
}

void printList(node *head)
{
    node *tmp = head;

    while (tmp)
    {
        fprintf(stdout, "%s\n", tmp->data);
        tmp = tmp->next;
    }
}

char *genString(int len, const char range[2])
{
    char *s = calloc(len, sizeof(char *));

    for (int i = 0; i < len; i++)
    {
        s[i] = get_random() % (range[1] - range[0] + 1) + range[0];
    }
    return s;
}

node **genList(int N)
{
    node **head = malloc(sizeof(node *));
    *head = NULL;

    char range[2] = {'a', 'z'};

    char *tmp = NULL;

    for (int i = 0; i < N; i++)
    {
        int L = get_random() % (15 - 5 + 1) + 5;

        tmp = genString(L, range);
        insertString(head, tmp);
        free(tmp);
    }
    return head;
}

void printOcc(node *head, char w)
{
    node *tmp = head;

    int count = 0;

    while (tmp)
    {
        char *s = tmp->data;

        for (int i = 0; i < strlen(s); i++)
        {
            if (s[i] == w)
                count++;
        }

        tmp = tmp->next;
    }

    fprintf(stdout, "Numero totale di occorrenze di %c: %d\n", w, count);
}

int main(int argc, char *argv[])
{
    Args args = readinput(argc, argv);
    node **head = genList(args.N);
    printList(*head);
    printOcc(*head, args.w);
}