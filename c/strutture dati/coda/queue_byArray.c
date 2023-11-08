#include <stdio.h>
#include <stdlib.h>

#define ENQUEUE_OK 1
#define ENQUEUE_FAIL -1

#define DEQUEUE_OK 1
#define DEQUEUE_FAIL -1

typedef struct circularQueue
{
    unsigned int head, tail;
    int *data;
    unsigned size;
} circularQueue;

int isEmpty(circularQueue *q)
{
    return q->head == q->tail;
}

int isFull(circularQueue *q)
{
    return q->head == (q->tail + 1) % (q->size);
}

void printQueue(circularQueue *q)
{
    if (isEmpty(q))
    {
        printf("\n ** QUEUE EMPTY **\n");
        return;
    }

    printf("\n (head) ");
    int *ptr = q->data;
    unsigned int index = q->head;

    while (index != q->tail)
    {
        printf(" %d ", ptr[index]);
        index = (index + 1) % (q->size);
    }

    printf(" (tail) \n");
}

int initQueue(circularQueue *q, int n) // Inizializzare gli indici tail ed head della coda
{
    q->head = q->tail = 0;
    q->data = (int *)malloc(sizeof(int) * n);
    if (!(q->data))
    {
        fprintf(stderr, "\n initQueue(): memory error!");
        return -1;
    }

    q->size = n;

    return 0;
}

int enqueue(circularQueue *q, int dato) // inserisce un dato in coda e restituisce un numero che indica l'esito dell'operazione
{
    if (isFull(q))
    {
        fprintf(stderr, "\n Queue is full! ");
        return -1;
    }

    // tail punta al primo elemento libero dell'array per l'inserimento in coda
    q->data[q->tail] = dato;
    //  gestione circolare dell'array ...
    q->tail = (q->tail + 1) % (q->size);
    return 1;
}

int dequeue(circularQueue *q, int *dato) // Preleva un dato dalla testa della coda, restituisce un numero che è l'esito dell'operazione
{
    if (isEmpty(q))
    {
        fprintf(stderr, "\n Queue is empty! ");
        return -1;
    }

    // head punta all'elemento in testa
    *dato = q->data[q->head];
    // gestione circolare dell'array
    q->head = (q->head + 1) % (q->size);
    return 1;
}

int main()
{
    circularQueue q;

    initQueue(&q, 20);

    int toInsert[9] = {1, 2, 3, 45, 6, 5, 4, 34, 21};

    for (unsigned short i = 0; i < 9; i++)
    {
        printf("\n Trying to insert element %d ...", toInsert[i]);
        if (enqueue(&q, toInsert[i]) < 0)
            return -1;

        printQueue(&q);
    }

    int dato;

    for (unsigned short i = 0; i < 5; i++)
    {
        if (dequeue(&q, &dato) != DEQUEUE_OK)
            return -1;
        else
            printf("\n Removed from the head: %d", dato);

        printQueue(&q);
    }

    printf("\n Removing all the remaining elements...");

    while (dequeue(&q, &dato) != DEQUEUE_OK || !isEmpty(&q))
        printQueue(&q);
}