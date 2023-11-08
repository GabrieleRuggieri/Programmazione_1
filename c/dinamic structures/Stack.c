#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int key;
    struct Node *next;
} Node;

typedef struct Stack
{
    int size;
    Node *top;
} Stack;

void printNode(Node *node)
{
    printf("[%d]", node->key);
}

bool isEmpty(Stack *stack)
{
    return !(stack->top);
}

void push(Stack *stack, int val)
{
    Node *toinsert = (Node *)malloc(sizeof(Node));
    toinsert->key = val;
    toinsert->next = NULL;

    if (isEmpty(stack))
    {
        stack->top = toinsert;
        stack->size++;
        return;
    }
    toinsert->next = stack->top;
    stack->top = toinsert;
    stack->size++;
}

Node *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        puts("\nEmpty Stack\n");
        return NULL;
    }
    Node *toreturn = stack->top;
    stack->top = stack->top->next;
    stack->size--;
    return toreturn;
}

void printStack(Stack *stack)
{
    if (isEmpty(stack))
    {
        puts("\nEmpty Stack\n");
        return;
    }
    printf("\nSize: %d \n", stack->size);
    printf("Top--");
    Node *cur = stack->top;
    while (stack->top)
    {
        printf(" ");
        printNode(cur);
        if (!cur->next)
            break;
        cur = cur->next;
    }
    printf(" --Down\n");
}

int main()
{
    int vet[15] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 11, 12, 13, 14, 15};
    Stack s;

    puts("\n...building stack...");
    for (int i = 0; i < 15; i++)
        push(&s, vet[i]);
    printStack(&s);

    puts("\nPop: ");
    for (int i = 0; i < 5; i++)
        pop(&s);
    printStack(&s);
}