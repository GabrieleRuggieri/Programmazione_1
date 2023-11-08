/*
    Si scriva un programma C che:
    - A chieda all'utente di inserire un intero “n” (si assuma n<256), una stringa "s1", una stringa
    “s2”, e un carattere "c" da tastiera. Si verifichi che entrambe le stringhe siano di lunghezza
    “n”. In caso contrario, si stampi un errore su standard error e si termini il programma con un
    opportuno codice di terminazione;

    - B costruisca una nuova stringa “s3” ottenuta sostituendo tutte le occorrenze del carattere "c"
    in “s1” con i caratteri che si trovano in “s2” nelle posizioni corrispondenti;

    - C definisca una nuova stringa “s4” ottenuta invertendo l’ordine dei caratteri in “s2”;

    - D  concateni le stringhe “s3” e “s4” in una nuova stringa “s5” e la ordini in ordine
    lessicografico ascendente usando un algoritmo di ordinamento a scelta;

    - E stampi a schermo la stringa ordinata. I caratteri i cui codici numerici relativi (fare cast dei
    caratteri a int) siano dispari, vanno sostituiti con “*”.

    --------------------------------------------------------------------------------------------------------------

    - readInput:   funzione   che   permette   di   leggere   gli   input   da   tastiera   e   restituisce
    opportunamente i valori letti al chiamante. La funzione deve gestire correttamente gli errori
    relativi a input non corretti e gestire la terminazione del programma in caso di errori.

    - replaceChar: funzione che riceve come input le stringhe "s1", “s2” e il carattere "c" e
    restituisce la stringa con le occorrenze di "c" in “s1” sostituite dai corrispondenti valori in
    “s2. Ad esempio, se s1=”abcacba”, s2=”fhsuika” e c=’a’, allora il risultato sarà “fbcucba”;

    - invertString:   funzione   che   costruisce   una   stringa   a   partire   da   una   stringa   in   input
    invertendono i caratteri;

    - sort: funzione che permetta di ordinare una stringa in ordine lessicografico;

    - printResult: funzione che stampa a schermo la stringa ottenuta come specificato nel punto
    E.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readInput(int *n, char *s1, char *s2, char *c)
{
    printf("inserisci un intero: ");
    scanf("%d", n);

    printf("inserisci una stringa di lunghezza %d: ", *n);
    scanf("%s", s1);

    printf("inserisci un'altra stringa di lunghezza %d: ", *n);
    scanf("%s", s2);

    if (strlen(s1) != *n || strlen(s2) != *n)
    {
        fprintf(stderr, "Errore! Le stringhe non sono di lunghezza %d\n", *n);
        exit(-1);
    }

    while (!getchar())
        ; // pulisco buffer di input

    printf("inserisci un carattere: ");
    scanf(" %c", c);
}

char *replaceChar(char *s1, char *s2, char c) // s1=”abcacba”,s2=”fhsuika”,c=’a’,sarà “fbcucba”
{
    int n = strlen(s1);
    char *out = malloc(sizeof(char) * n + 1);

    for (int i = 0; i < n; i++)
    {
        if (s1[i] == c)
            out[i] = s2[i];
        else
            out[i] = s1[i];
    }

    return out;
}

void printString(char *s)
{
    int len = strlen(s);

    for (int i = 0; i < len; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}

char *invertString(char *s)
{
    char *out = malloc(sizeof(char) * (strlen(s) + 1));

    for (int i = 0; i < strlen(s); i++)
    {
        out[strlen(s) - i - 1] = s[i];
    }
    out[strlen(s)] = '\0'; // Aggiungi il carattere di terminazione della stringa.
    return out;
}

void sortS(char *S, int n) // bubble sort
{

    for (int i = 0; i < n; i++)
    {
        for (int k = i + 1; k < n; k++)
        {
            if (S[i] > S[k])
            {
                char tmp = S[i];
                S[i] = S[k];
                S[k] = tmp;
            }
        }
    }
}

void sortS2(char *S, int n) // insertion sort
{

    for (int i = 1; i < n; i++)
    {
        char key = S[i];
        int k = i - 1;

        while (k >= 0 && (key < S[k]))
        {
            S[k + 1] = S[k];
            k--;
        }
        S[k + 1] = key;
    }
}

void sortS3(char *S, int n) // selection sort
{

    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int k = i + 1; k < n; k++)
        {
            if (S[k] < S[min_index])
                min_index = k;
        }
        char tmp = S[i];
        S[i] = S[min_index];
        S[min_index] = tmp;
    }
}

void printResult(char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] % 2 == 1)
            printf("*");
        else
            printf("%c", s[i]);
    }
    printf("\n");
}

int main()
{
    char s1[255];
    char s2[255];
    int n;
    char c;
    readInput(&n, s1, s2, &c);

    char *s3 = replaceChar(s1, s2, c);
    printf("Stringa 1: ");
    printString(s3);

    char *s4 = invertString(s2);
    printf("Stringa 2: ");
    printString(s4);

    char *s5 = strcat(s3, s4);
    printString(s5);
    sortS(s5, strlen(s5));
    printString(s5);

    printResult(s5);
}

/*
Eseguendo il programma con i seguenti input:
15
jsudbehdnbvsju9
kduw76_lposhndb
s
Il programma dovrà stampare il seguente output: 9bbdddehhjjnuuv
*/