/*
Scrivere un programma in C che:
    - A prenda un input da tastiera (argomenti della funzione main) costituito da un intero
    positivo N. Il programma deve verificare che N sia inserito nel formato corretto e
    restituire un messaggio di errore terminando il programma opportunamente nel
    caso in cui il formato di N non dovesse essere corretto;
    - B generi una sequenza di N operazioni di inserimento (push) di caratteri pseudo-
    casuali in [A-Z,a-z,1-9] in una struttura dati LIFO dinamica (pila o stack) da
    implementare mediante lista concatenata semplice (top==testa della lista), nel
    seguente modo:
    - ad ogni passo, si generi innanzitutto un carattere x in [1-9];
    - se x rappresenta un numero in [1-4], allora si proceda ad x operazioni di
    inserimento (push) di caratteri pseudo-casuali che siano vocali, seguite
    dall’inserimento del carattere x;
    - se x rappresenta un numero in [5-9], allora si proceda ad x operazioni di
    inserimento (push) di caratteri pseudo-casuali che siano consonanti, seguite
    dall’inserimento del carattere x;
    - in particolare, sia c il generico carattere da inserire sullo stack:
    - se c==v, si inserisca sullo stack al posto di esso il carattere '*';
    - se c==w, si inserisca sullo stack al posto di esso il carattere '?';
    - C
    - crei un array di stringhe (puntatori a caratteri) di lunghezza N;
    - proceda nel seguente modo, fino a svuotamento dello stack:
    successivamente proceda ad una sequenza di operazioni di rimozione
    (pop()) come segue:
    - si proceda quindi, ad ogni passo con un'operazione di rimozione
    (pop()) del carattere x che indica (per costruzione) il numero di
    caratteri da rimuovere successivamente mediante x operazioni pop();
    - si memorizzi sull'array di caratteri ogni stringa composta dal carattere
    x e dai successivi x caratteri;

    - D stampi, sullo standard output, il contenuto dell'array di stringhe;

    -----------------------------------------------------------------------------------------------------

    - readInput: funzione che prende in input l'array di puntatori a carattere argv della
    funzione main, controlli che gli argomenti richiesti siano nei limiti specificati, e
    restituisca il record (struct) che contiene tali parametri; se il controllo non va a buon
    fine, stampa un messaggio sullo standard error e termina il programma.
    - genVowel: funzione che produca un carattere vocale pseudo-casuale;
    - genConsonant: funzione che produca un carattere consonante pseudo-casuale;
    - push e pop: funzioni che consentono di inserire un elemento sullo stack o
    rimuovere un elemento da esso;
    - fillStack: funzione con opportuni parametri formali che rappresenti
    l’implementazione della procedura descritta nel punto B;
    - emptyStack: funzione con opportuni parametri formali che sia conforme alla
    procedura descritta nel punto C;
    - printArray: funzione per la stampa dell’array di stringhe prodotto al punto C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}
struct parametri
{
    int N;
};
struct parametri readInput(char *argv[], int argc)
{
    if (argc != 2)
    {
        fprintf(stderr, "Errore: il numero di parametri deve essere pari a 1.\n");
        exit(-1);
    }
    char **end = malloc(sizeof(char *));
    int x = (int)strtol(argv[1], end, 0);
    if (!*end || x < 0)
    {
        fprintf(stderr, "Errore: il parametro inserito deve essere un intero positivo.\n");
        exit(-1);
    }
    struct parametri p = {x};
    return p;
}
struct node
{
    char data;
    struct node *next;
};
typedef struct node Node;
bool empty(Node *head)
{
    return head == NULL;
}
void push(Node **head, char x)
{
    Node *new = malloc(sizeof(Node));
    new->data = x;
    new->next = *head;
    *head = new;
}
char pop(Node **head)
{
    if (empty(*head))
    {
        fprintf(stderr, "Errore: pila vuota!\n");
        exit(-1);
    }
    char x = (*head)->data;
    Node *tmp = *head;
    (*head) = (*head)->next;
    free(tmp);
    return x;
}
char getRandomChar(char *s)
{
    return s[get_random() % strlen(s)];
}
char getVowel()
{
    return getRandomChar("AEIOUaeiou");
}
char getConsonant()
{
    return getRandomChar("QWRTYPDSFGHJKLZXCVBNMqwrtypdsfghjklzxcvbnm");
}
int char2int(char c)
{
    char tmp[2];
    tmp[0] = c;
    tmp[1] = 0;
    char **end = malloc(sizeof(char *));
    int x = (int)strtol(tmp, end, 0);
    free(end);
    return x;
}
Node **fillStack(int N)
{
    Node **head = malloc(sizeof(Node *));
    *head = NULL;
    int i = 0;
    for (int j = 0; j < N; j++)
    {
        char x = getRandomChar("123456789");
        if (x >= '1' && x <= '4')
        {
            for (int i = 0; i < char2int(x); i++)
            {
                push(head, getVowel());
            }
            push(head, x);
        }
        else
        {
            for (int i = 0; i < char2int(x); i++)
            {
                char c = getConsonant();
                if (c == 'v')
                    c = '*';
                if (c == 'w')
                    c = '?';
                push(head, c);
            }
            push(head, x);
        }
    }
    return head;
}
char **emptyStack(Node **head, int N)
{
    char **array = calloc(N, sizeof(char *));
    int i = 0;
    while (!empty(*head))
    {
        char c = pop(head);
        int x = char2int(c);
        array[i] = calloc(x, sizeof(char) + 1);
        for (int j = 0; j < x; j++)
        {
            array[i][j] = pop(head);
        }
        i++;
    }
    return array;
}
void printArray(char **array, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%s\n", array[i]);
    }
}
int main(int argc, char *argv[])
{
    struct parametri p = readInput(argv, argc);
    Node **head = fillStack(p.N);
    char **array = emptyStack(head, p.N);
    printArray(array, p.N);
}