/*
    allocare la quantità di memoria di volta in volta necessaria
    e de-allocarla quando non serve più, produce chiaramente
    programmi più efficienti.
    Per fare ciò ci sono funzioni come malloc, calloc, free e realloc in c
    che servono a creare e gestire oggetti dinamici.
    MALLOC serve ad allocare un'area di memoria durate l'esecuzione del programma.
    sintassi: void *malloc(size_t), con size_t si indica la
    quantità di memoria in byte da allocare, e ritorna un puntatore void
    al primo byte dell'area allocata
*/

// array di size 10 e calcolo la media senza malloc

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int main()
{
    int numero = 25, *array, i;
    int allocati; // bytes
    printf("Numero di elementi dell'array: %d\n", numero);
    // alloca il numero di elementi interi che ci servono (4x25)
    // e opera un cast che permette alla memoria di essere
    // trattata come array di int
    array = (int *)malloc(sizeof(int) * numero);
    /*
    la funzione calloc inizializza ogni byte del blocco di memoria a zero.
    Quindi la funzione prevede due argomenti,
    il primo rappresenta il numero di elementi da allocare mentre il secondo la quantità di memoria per ogni elemento

    calloc array = (int *) calloc(numero,sizeof(int))
    */
    if (array == NULL)
    {
        printf("Memoria esaurita\n");
        exit(1);
    }
    allocati = sizeof(int) * numero;
    for (i = 0; i < numero; i++)
    {
        array[i] = i;
    }
    printf("Valori degli elementi\n");
    for (i = 0; i < numero; i++)
    {
        printf("%6d%c", array[i], (i % 10 == 9) ? '\n' : ' ');
    }
    printf("\n\nNumero elementi %d\n", numero);
    printf("Dimensione elemento %d\n", sizeof(int));
    printf("Bytes allocati %d\n", allocati);
    free(array);
    printf("\nMemoria Liberata\n");
    return 0;
}