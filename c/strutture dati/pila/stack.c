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

void printDato(dato *ptr)
{
    printf(" [%d] ", ptr->value);
}

int isEmpty(node *top)
{
    return top == NULL;
}

void printStack(node *top)
{
    if (isEmpty(top))
    {
        printf("\n ** Stack is Empty ** \n");
        return;
    }

    node *current = top;
    printf("\n ** STACK ** \n");
    while (current != NULL)
    {
        printDato(&(current->d));
        if (current->next != NULL)
            printf("\n  |  \n");
        current = current->next;
    }

    printf("\n");
}

void push(node **top, dato *d)
{
    node *new_node = malloc(sizeof(node));
    new_node->next = NULL;
    memcpy(&(new_node->d), d, sizeof(dato));
    if (!isEmpty(*top))
        new_node->next = *top;

    *top = new_node;
}

int pop(node **top, dato *d)
{
    if (!isEmpty(*top))
    {
        node *n = *top;
        (*top) = (*top)->next;
        memcpy(d, &(n->d), sizeof(dato));
        free(n);
        return 1;
    }

    else
        return -1;
}

int main()
{
    node *top = NULL;

    dato d;

    int dataToPush[6] = {4, 3, 6, 2, 6, 9};

    for (unsigned short i = 0; i < 6; i++)
    {
        d.value = dataToPush[i];
        printf("\n ** Pushing element %d **", d.value);
        push(&top, &d);
        printStack(top);
    }

    printStack(top);

    for (unsigned short i = 0; i < 6; i++)
    {
        if (pop(&top, &d) > 0)
        {
            printf("\n ** Removed element %d **", d.value);
            printStack(top);
        }
        else
            printf("\n Error while removing the top of the stack");
    }

    printStack(top);
}