/*
    Codificare una funzione per il calcolo
    dei numeri di fibonacci con approccio iterativo
*/

#include <stdio.h>

unsigned fibo(unsigned n)
{

    unsigned primo = 1, secondo = 1;
    unsigned terzo;

    printf("%u\n", primo);
    printf("%u\n", secondo);

    for (int i = 2; i < n; i++)
    {
        terzo = primo + secondo;
        primo = secondo;
        secondo = terzo;
        printf("%u\n", terzo);
    }
}

int main()
{
    unsigned n;

    printf("Quanti numeri della successione vuoi visualizzare? ");
    scanf("%u", &n);

    printf("%u\n", fibo(n));
}
