#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int key;
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
    printf("[%d]", node->key);
}

bool isEmpty(List *list)
{
    return !(list->head);
}

void insertHead(List *list, int val)
{
    Node *toinsert = (Node *)malloc(sizeof(Node));
    toinsert->key = val;
    toinsert->next = NULL;

    if (isEmpty(list))
    {
        list->head = toinsert;
        return;
    }
    
    toinsert->next = list->head;
    list->head = toinsert;
}

void insertTail(List *list, int val)
{
    Node *toinsert = (Node *)malloc(sizeof(Node));
    toinsert->key = val;
    toinsert->next = NULL;

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

void insertInOrder(List *list, int val)
{
    if (isEmpty(list) || val <= list->head->key)
    {
        insertHead(list, val);
        return;
    }

    Node *cur = list->head;
    while (cur->next && val >= cur->key)
    {
        if (val < cur->next->key)
            break;
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

void removeTail(List *list)
{
    if (isEmpty(list))
    {
        puts("\nEmpty List\n");
        return;
    }

    Node *toremove = list->head;
    Node *prev = NULL;

    while (toremove->next)
    {
        prev = toremove;
        toremove = toremove->next;
    }
    prev->next = NULL;
    free(toremove);
}

Node *search(List *list, int val)
{
    if (isEmpty(list))
    {
        puts("\nEmpty List\n");
        return NULL;
    }

    /*
    if(list->head->key == val)
        return list->head;
    */

    Node *cur = list->head;
    while (cur->next && cur->key != val)
        cur = cur->next;

    if (cur->key != val)
    {
        printf("\nElement with key %d not found\n", val);
        return NULL;
    }
    return cur;
}

void invert(List *list)
{
    if (isEmpty(list))
    {
        puts("\nEmpty List\n");
        return;
    }

    Node *cur = list->head;
    Node *prev = NULL;
    Node *succ = NULL;
    while (cur)
    {
        succ = cur->next;
        cur->next = prev;
        prev = cur;
        cur = succ;
    }
    list->head = prev;
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
    printf("\nHead --");
    while (cur)
    {
        printNode(cur);
        printf("--");
        cur = cur->next;
    }
    puts(" NIL");
}

int main()
{
    int vet[11] = {5, 4, 3, 2, 1, 6, 7, 8, 9, 10, 11};
    List l;

    puts("\n...building list...");
    for (int i = 0; i < 6; i++)
        insertHead(&l, vet[i]);

    for (int i = 5; i < 11; i++)
        insertTail(&l, vet[i]);

    printList(&l);

    puts("\nRemove Head");
    removeHead(&l);
    printList(&l);

    puts("\nRemove Tail");
    removeTail(&l);
    printList(&l);

    puts("\nLooking for nodes with keys 9 and 37\n");
    Node *test = search(&l, 9);
    printNode(test);
    test = search(&l, 37);

    puts("\nInvert");
    invert(&l);
    printList(&l);
}
