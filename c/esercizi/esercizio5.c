#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct parametri
{
    int N;
    char v, w;
} parametri;

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

parametri readInput(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Errore:numero di argomenti non corretto\n");
        exit(-1);
    }

    char **end = malloc(sizeof(char *));

    parametri p;

    p.N = (int)strtol(argv[1], end, 0);
    if (!end || p.N < 0)
    {
        fprintf(stderr, "Errore: il primo parametro deve essere un intero positivo\n");
        exit(-1);
    }

    if (p.N < 5 && p.N > 9)
    {
        fprintf(stderr, "Errore: N deve essere in [5, 9]\n");
        exit(-1);
    }

    p.v = argv[2][0]; // vocale
    if (p.v != 'a' && p.v != 'e' && p.v != 'i' && p.v != 'o' && p.v != 'u')
    {
        fprintf(stderr, "Errore: il secondo parametro deve essere una vocale minuscola\n");
        exit(-1);
    }

    p.w = argv[3][0]; // consonante
    if ((int)p.w < 97 && (int)p.w > 122)
    {
        fprintf(stderr, "Errore: il terzo parametro deve essere una consonante\n");
        exit(-1);
    }

    return p;
}

typedef struct node
{
    char data;
    struct node *next;
} node;

bool empty(node *head)
{
    return head == NULL;
}

void push(node **head, char x)
{
    node *new = malloc(sizeof(node));

    new->data = x;
    new->next = *head;
    *head = new;
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
    return getRandomChar("BCDFGHLMNPQRSTVWXYZbcdfghlmnpqrstvwxyz");
}

char getNumber()
{
    return getRandomChar("123456789");
}

char pop(node **head)
{
    if (empty(*head))
    {
        fprintf(stderr, "Errore: pila vuota\n");
        exit(-1);
    }

    char x = (*head)->data;
    node *tmp = *head;
    (*head) = (*head)->next;

    free(tmp);

    return x;
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

node **fillStack(int N)
{
    node **head = malloc(sizeof(node *));
    *head = NULL;

    parametri z;

    for (int j = 0; j < N; j++)
    {
        char x = getNumber();
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

                if (c == z.v)
                    c = '*';
                if (c == z.w)
                    c = '?';
                push(head, c);
            }
            push(head, x);
        }
    }
    return head;
}

char **emptyStack(node **head, int N)
{
    char **array = malloc(sizeof(char *) * N);
    int i = 0;
    while (!empty(*head))
    {
        char c = pop(head);
        int x = char2int(c);
        array[i] = malloc((sizeof(char) + 1) * x);
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
    parametri p = readInput(argc, argv);
    node **head = fillStack(p.N);
    char **array = emptyStack(head, p.N);
    printArray(array, p.N);
}
