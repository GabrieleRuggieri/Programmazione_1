/*
    Codificare una funzione che prenda in input un
    numero che rappresenti una base ed un altro
    numero positivo che rappresenti l’esponente, e
    calcoli l’elevamento a potenza con approccio
    ricorsivo
*/

#include <stdio.h>

unsigned fun(unsigned base, unsigned esp)
{

    if (esp == 0)
        return 1;
    if (esp == 1)
        return base;

    return base * fun(base, esp - 1);
}

int main()
{
    unsigned base = 3, esp = 3;

    printf("risutato: %u\n", fun(base, esp));
}