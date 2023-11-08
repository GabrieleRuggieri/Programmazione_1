/*

uso della funzione realloc() per definire un array flessibile
la cui dimensione viene quindi ridefinita a seconda delle necessità.

La sintassi della funzione realloc() ha due argomenti,
il primo riguarda l'indirizzo di memoria,
il secondo specifica la nuova dimensione del blocco;
il tipo restituito è un tipo puntatore a void,
del quale provvederemo ad effettuare il casting
all'interno del programma per trasformarlo in un puntatore
ad intero, in questo caso, o nel tipo relativo al nostro array.

Assegneremo al nostro array un primo blocco di memoria e,
una volta "saturato" quello, utilizzeremo realloc()
per allocare il blocco successivo.
La suddivisione in blocchi avviene durante la fase di
lettura dei dati da tastiera, ignorando a priori il
numero di informazioni che dovremo memorizzare.

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int main()
{
    int i = 0, n = 0, x, *array, nb;
    int allocati; /* byte allocati */
    int dimbloc;  /* byte in un blocco */
    int dimint;   /* byte in un intero */
    int usati;    /* byte contenenti interi */
    nb = 1;
    printf("Elementi in un blocco: %d\n", nb);
    dimint = sizeof(int);
    dimbloc = nb * dimint;
    usati = 0;
    array = (int *)malloc(dimbloc);
    if (array == NULL)
    {
        printf("Memoria insufficiente\n");
        exit(1);
    }
    allocati = dimbloc;
    printf("Allocati: %d bytes\n", allocati);
    printf("Input di interi terminati da [invio]:\n");
    while (scanf("%d", &x))
    {
        usati += dimint;
        if (usati > allocati)
        {
            allocati += dimbloc;
            array = (int *)realloc(array, allocati);
            if (array == NULL)
            {
                printf("Memoria insufficiente\n");
                exit(1);
            }
            i++;
        }
        /* in questo modo vengono letti n interi */
        array[n++] = x;
    }
    printf("\n");
    printf("Allocati: %d bytes\n", allocati);
    printf("Dim. blocchi: %d bytes\n", dimbloc);
    printf("Dim. intero: %d bytes\n", dimint);
    printf("Usati: %d bytes\n", usati);
    printf("Chiamate realloc: %d\n", i);
    printf("Numeri: %d\n", n);
    printf("\nEcco i numeri\n");
    for (i = 0; i < n; i++)
    {
        printf("%5d%c", array[i], (i % 10 == 9) ? '\n' : ' ');
    }
    printf("\n");
    return 0;
}