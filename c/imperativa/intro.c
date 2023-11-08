#include <stdio.h>

int main()
{

    printf("Hello World \n");

    // tipi di dato
    int num = 5;
    float floatnum = 5.99;
    char lettera = 'A';

    printf("L'intero è uguale a: %i \n", num); //%d o %i per interi, %f per float, %lf double, %c char, %s stringhe
    printf("Il float vale: %f \n", floatnum);
    printf("La lettera è: %c \n", lettera);

    printf("Il float vale %f e la mia lettera è %c \n", floatnum, lettera);

    // operatori di confronto
    int x = 5;
    int y = 3;
    printf("%i", x > y); // ritorna 1 (true) perchè 5 è più grande di 3

    // dimensione operatore
    int myInt;
    float myFloat;
    double myDouble;
    char myChar;

    printf("%lu \n", sizeof(myInt)); // si usa %lu perchè il compilatore si aspetta che sizeof restituisca un long unsigned int
    printf("%lu \n", sizeof(myFloat));
    printf("%lu \n", sizeof(myDouble));
    printf("%lu \n", sizeof(myChar));

    // operatore ternario
    int time = 20;
    (time < 18) ? printf("good day. \n") : printf("good evening. \n");

    // stringhe
    char stringa[] = "hello world";
    printf("%s \n", stringa);          // stampa l'intera stringa
    printf("%c \n", stringa[0]);       // si usa l'identificatore %c per stampare il carattere
    printf("%lu \n", sizeof(stringa)); // output 12
    char *str2 = "pippoo";             // non si può modificare

    /*
    //input utente
    int valore;
    printf("Scrivi un numero: ");
    scanf("%i", &valore);   //operatore di riferimento (&valore) che memorizza l'indirizzo di memoria della variabile
    printf("Il tuo numero è: %i \n", valore);*/

    /*
    input stringhe
    scanf(“%[^\n]s”,str)
    scanf("%[^\n]%*c", str) (OK)

    char name[30];
    printf("Inserisci nome: \n");
    scanf("%s", name);  //non devo specificare l'operatore di riferimento (&) quando si lavora con stringhe in scanf
    printf("Hello %s \n", name);*/

    // indirizzo di memoria
    int myAge = 20;
    printf("%p \n", &myAge); // output tipo: 0x7ffe4bdc6f6c. Per stampare i valori del putatore si usa %p

    // creazione di puntatori
    int valore2 = 40;
    printf("%i \n", valore2);  // 43
    printf("%p \n", &valore2); // memory address of valore2

    int valore3 = 50;
    int *ptr = &valore3;
    printf("%i \n", valore3);  // 50
    printf("%p \n", &valore3); // memory address
    printf("%p \n", ptr);      // memory address with the pointer

    int valore4 = 45;       // variable declaration
    int *ptr2 = &valore4;   // pointer declaration
    printf("%p \n", ptr2);  // memory address with the pointer
    printf("%i \n", *ptr2); // value with the pointer (45)

    return 0;
}