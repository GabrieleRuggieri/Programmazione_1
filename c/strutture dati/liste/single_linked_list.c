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
    return (head == NULL);
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
    printf(" **END LIST ** \n");
}

void insertNode(dato *ptrDato, node **head)
{
    node *new_node = (node *)malloc(sizeof(node)); // nuovo nodo
    new_node->next = NULL;
    // memcpy((void *)&(new_node->d), (void *)ptrDato, sizeof(dato)); // nuovo nodo
    new_node->d = *ptrDato;

    if (isEmpty(*head))
    {
        *head = new_node;
        return;
    }

    node *current = *head, *previous = NULL; // per la ricerca

    while (current && confronta_dati(&(current->d), &(new_node->d)) < 0)
    {
        previous = current;
        current = current->next;
    }

    if (previous != NULL)
        previous->next = new_node;
    else
        *head = new_node; // inserimento in testa

    // se current == NULL, l'elemento sara' aggiunto in coda alla lista
    if (current != NULL)
        new_node->next = current;
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
    {                                       // elemento esiste nella lista
        if (previous)                       // e non e' la testa della lista
            previous->next = current->next; // aggiorna il link..
        else
            *head = current->next; // aggiorna il puntatore al primo elemento
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

    int deleteData[3] = {1, 10, 34};

    for (unsigned short i = 0; i < 3; i++)
    {
        printf("\n Trying to delete data: [%d]", deleteData[i]);
        my_data.value = deleteData[i];
        deleteNode(&my_data, &head);
    }

    printList(head);
}