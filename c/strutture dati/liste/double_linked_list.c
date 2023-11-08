#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

typedef struct dato
{
    int value;
} dato;

typedef struct node
{
    dato d;
    struct node *next;
    struct node *prev;
} node;

int confronta_dati(dato *d1, dato *d2)
{
    if (d1->value > d2->value)
        return 1;
    else if (d1->value < d2->value)
        return -1;
    return 0;
}

void printDato(dato *ptr)
{
    printf(" [%d] ", ptr->value);
}

int isEmpty(node *head)
{
    return head == NULL;
}

void printList(node *head)
{
    node *ptr = head;

    printf("\n ** LIST **");

    while (ptr != NULL)
    {
        printDato(&(ptr->d));
        ptr = ptr->next;
    }

    printf(" **END LIST** \n");
}

void insertNode(dato *ptrdato, node **head)
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->next = NULL;
    new_node->prev = NULL;

    // memcpy((void *)&(new_node->d), (void *)ptrdato, sizeof(dato));
    new_node->d = *ptrdato;

    if (isEmpty(*head))
    {
        *head = new_node;
        return;
    }

    node *current = *head, *previous = NULL; // il riferimento previous va mantenuto nel caso si inserisca in coda

    while (current != NULL && confronta_dati(&(current->d), &(new_node->d)) < 0)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL)
    {

        if (current->prev == NULL) // inserimento in testa o tra due elementi
        {
            *head = new_node; // inseriemnto in testa
            (*head)->next = current;
        }

        else
        {
            (current->prev)->next = new_node;
            new_node->prev = current->prev;
        }

        current->prev = new_node;
    }

    else
    {
        previous->next = new_node; // inseriemnto in coda
        new_node->prev = previous;
    }
}

void deleteNode(dato *ptrDato, node **head)
{
    if (isEmpty(*head))
        return;

    node *current = *head, *previous = NULL;

    while (current != NULL && confronta_dati(&(current->d), ptrDato) != 0)
    {
        previous = current;      // mantiene il riferimento al nodo appena visitato
        current = current->next; // aggiorna il riferimento al prossimo nodo da visitare
    }

    if (current != NULL)
    {
        if (previous)                       // elemento esiste nella lista
        {                                   // e non e' la testa della lista
            previous->next = current->next; // aggiorna il link..
            if (current->next != NULL)
                (current->next)->prev = previous; // double link
        }

        else
        {
            *head = current->next; // aggiorna il puntatore al primo elemento
            (*head)->prev = NULL;  // double link
        }
        free(current);
    }
}

int main()
{
    node *head = NULL;

    dato my_data;

    int inputData[5] = {10, 12, 2, 34, 1};

    for (unsigned short i = 0; i < 5; i++)
    {
        printf("\n Trying to add data: [%d]", inputData[i]);
        my_data.value = inputData[i];
        insertNode(&my_data, &head);
    }

    printList(head);

    int deleteData[3] = {7, 10, 34};

    for (unsigned short i = 0; i < 3; i++)
    {
        printf("\n Trying to delete data: [%d]", deleteData[i]);
        my_data.value = deleteData[i];
        deleteNode(&my_data, &head);
    }

    printList(head);
}