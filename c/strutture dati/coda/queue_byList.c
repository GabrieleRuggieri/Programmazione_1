#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dato
{
    int value;
} dato;

typedef struct node
{
    dato d;
    struct node *next;
} node;

typedef struct queue
{
    node *tail;
    node *head;
} queue;

void printDato(const dato *ptr)
{
    printf(" [%d] ", ptr->value);
}

int isEmpty(queue *q)
{
    return (q->head == NULL);
}

void printQueue(queue *q)
{
    if (isEmpty(q))
    {
        printf(" ** EMPTY QUEUE ** ");
        return;
    }
    node *current = q->head;

    printf("\n ** QUEUE ** \n ");
    printf(" (head) ");
    while (current != NULL)
    {
        printDato(&(current->d));
        current = current->next;
    }

    printf(" (tail) ");
}

void enqueue(queue *q, dato *d)
{

    node *new_node = (node *)malloc(sizeof(node));
    memcpy(&(new_node->d), d, sizeof(dato));

    new_node->next = NULL;

    if (isEmpty(q))
        q->head = q->tail = new_node;

    else
    {
        (q->tail)->next = new_node;
        q->tail = new_node;
    }
}

int dequeue(queue *q, dato *d)
{
    if (isEmpty(q))
        return -1;

    // copia il dato nell'area di memoria predisposta dallo user code
    memcpy(d, &((q->head)->d), sizeof(dato));

    node *tmp = q->head;
    (q->head) = tmp->next;

    free(tmp); // libera lo spazio occupato dal node

    return 1;
}

int main()
{

    queue q;
    q.head = q.tail = NULL;

    int array[] = {1, 2, 3, 4, 5, 6};

    dato d;

    for (int i = 0; i < 6; i++)
    {
        d.value = array[i];
        enqueue(&q, &d);
        printQueue(&q);
    }

    printQueue(&q);

    for (int i = 0; i < 6; i++)
    {
        if (dequeue(&q, &d) < 0)
            fprintf(stderr, "\n Error removing element from the queue..");
        else
            printf("\n\n ** Removed element %d ** \n", d.value);

        printQueue(&q);
    }
}