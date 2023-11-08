#include <stdio.h>
#include <math.h> //per funzioni matematiche

// Function definition
int fun(int x, int y)
{
    return x + y;
}

int sum(int k)
{ // somma dei primi 10 numeri
    if (k > 0)
        return k + sum(k - 1);
    else
        return 0;
}

/*
10 + somma(9)
10 + ( 9 + somma(8) )
10 + ( 9 + ( 8 + somma(7) ) )
...
10 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 + somma(0)
10 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 + 0*/

// The main method
int main()
{
    int result = fun(5, 3); // Call the function
    int result2 = sum(10);
    printf("Result is = %i \n", result);
    printf("%i \n", result2);

    // radice quadrata
    printf("%f \n", sqrt(16));

    // arrotonamento numero
    printf("%f \n", ceil(1.4));  //(2.0) ceil arrotonda per eccesso al suo intero più vicino
    printf("%f \n", floor(1.4)); //(1.0) floor arrotonda per difetto al suo intero più vicino

    // potenza
    printf("%f \n", pow(4, 3));

    return 0;
}