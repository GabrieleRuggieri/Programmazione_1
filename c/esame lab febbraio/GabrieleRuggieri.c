// Gabriele Ruggieri   1000030748

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Args
{
    int N;
    char a;
    char b;
} Args;

Args readinput(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Errore: numero non corretto di parametri\n");
        exit(-1);
    }

    if (atoi(argv[1]) < 5 || atoi(argv[1]) > 10)
    {
        fprintf(stderr, "Errore: N deve essere in [5, 10]\n");
        exit(-1);
    }

    if (argv[2][0] < 'a' || argv[2][0] > 'z')
    {
        fprintf(stderr, "Errore: il carattere a deve esseere in [a,z]\n");
        exit(-1);
    }

    if (argv[3][0] < 'a' || argv[3][0] > 'z')
    {
        fprintf(stderr, "Errore: il carattere b deve esseere in [a,z]\n");
        exit(-1);
    }

    Args p;
    p.N = atoi(argv[1]);
    p.a = argv[2][0];
    p.b = argv[3][0];

    return p;
}

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct Node
{
    char key;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

char getRandomChar(char *s)
{
    return s[get_random() % strlen(s)];
}

char genVowel()
{
    return getRandomChar("aeiou");
}

char getConsonant()
{
    return getRandomChar("bcdfghlmnpqrstvwxyz");
}

bool isEmpty(Stack *stack)
{
    return !(stack->top);
}

void push(Stack *stack, char c)
{
    Node *toinsert = malloc(sizeof(Node));
    toinsert->next = NULL;
    toinsert->key = c;

    if (isEmpty(stack))
    {
        stack->top = toinsert;
        return;
    }

    toinsert->next = stack->top;
    stack->top = toinsert;
}

Stack *fillStack(int N, char a, char b)
{

    Stack *s = malloc(sizeof(Stack));

    char v;

    for (int i = 0; i < N; i++)
    {
        char x = get_random() % ('9' - '1' + 1) + '1';

        int num = atoi(&x);

        if (x >= '1' || x <= '4')
        {
            for (int j = 0; j < num; j++)
            {
                v = genVowel();
                if (v == a)

                    v = '*';

                if (v == b)

                    v = '?';

                push(s, v);
            }
            push(s, x);
        }

        else if (x >= '5' || x <= '9')
        {
            for (int j = 0; j < num; j++)
            {
                char v = getConsonant();
                if (v == a)

                    v = '*';

                if (v == b)

                    v = '?';

                push(s, v);
            }
            push(s, x);
        }
    }

    return s;
}

void printStack(Stack *stack)
{
    if (isEmpty(stack))
    {
        puts("Empty stack");
        return;
    }
    Node *ptr = stack->top;

    while (stack->top)
    {
        printf("%c ", ptr->key);

        if (!ptr->next)
            break;
        ptr = ptr->next;
    }
}

int main(int argc, char *argv[])
{
    Args d = readinput(argc, argv);

    Stack *s = fillStack(d.N, d.a, d.b);

    /*char ch = genVowel();
    printf("%c\n", ch);*/

    /*char ch = getConsonant();
    printf("%c\n", ch);*/

    printStack(s);

    printf("\n");
}