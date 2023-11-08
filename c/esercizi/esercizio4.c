#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct record
{
    int N;    // 20-25
    int M;    // 10-15
    double x; // 5.0-10.0
    double y; // 40-50
} Record;

typedef struct stack
{
    double *arr;
    int top;
} Stack;

Record verifica(int n, char **arg)
{
    if (n != 5)
    {
        fprintf(stderr, "Inserire due int in 10-15 e 20-25 e due double in 5.0-10.0 e 40.0-50-0");
        exit(-1);
    }
    Record ret;
    if (atoi(arg[1]) < 20 || atoi(arg[1]) > 25)
    {
        fprintf(stderr, "ERR N");
        exit(-1);
    }

    ret.N = atoi(arg[1]);
    if (atoi(arg[2]) < 10 || atoi(arg[2]) > 15)
    {
        fprintf(stderr, "ERR M");
        exit(-1);
    }
    ret.M = atoi(arg[2]);

    char **end = malloc(sizeof(char *));
    *end = NULL;
    if ((ret.x = (strtod(arg[3], end))) < 5.0 || ret.x > 10.0)
    {
        fprintf(stderr, "ERR x");
        exit(-1);
    }
    if (**end)
    {
        fprintf(stderr, "ERR x");
        exit(-1);
    }
    char **end2 = malloc(sizeof(char *));
    *end2 = NULL;
    if ((ret.y = (strtod(arg[4], end2))) < 40.0 || ret.y > 50.0)
    {
        fprintf(stderr, "ERR y");
        exit(-1);
    }
    if (**end2)
    {
        fprintf(stderr, "ERR y");
        exit(-1);
    }

    return ret;
}

void printStack(Stack *S)
{
    if ((*S).top - 1 < 0)
    {
        printf("\n%s\n", "STACK VUOTO");
        return;
    }
    for (int i = (*S).top; i >= 0; i--)
    {
        printf("||%lf||\n", (*S).arr[i]);
    }
    puts("\n--FINESTACK--\n");
}

Stack BuildStack(int LIMIT)
{
    Stack S;
    S.arr = (double *)malloc(sizeof(double) * LIMIT);
    S.top = 0;
    return S;
}
void push(Stack *S, double *dato, int limit)
{
    if ((*S).top == limit)
    {
        printf("\n%s\n", "---STACK PIENO---");
        return;
    }
    (*S).arr[(*S).top] = *dato;
    (*S).top++;
}
double pop(Stack *S)
{
    if ((*S).top - 1 < 0)
    {
        printf("\n%s\n", "STACK VUOTO");
        return 0;
    }
    double ret;
    ret = (*S).arr[(*S).top - 1];
    (*S).arr[(*S).top - 1] = 0;
    (*S).top--;

    return ret;
}
double genDouble(double x, double y)
{
    double ret;
    ret = rand() / (RAND_MAX + 1.0) * (y - x) + x;
    return ret;
}
void fillStack(Stack *S1, Stack *S2, double x, double y, int M, int N)
{

    int i = 0;
    int j = 0;
    double val1;
    double val2;
    double popped;

    do
    {

        val1 = genDouble(x, y);
        push(S1, &val1, N / 2);
        i++;
        if (val1 >= (x + y) / 2 && j < M)
        {
            popped = pop(S1);
            j++;
            push(S2, &popped, N / 2);
            fprintf(stderr, "\nPOPPED VALUE:%lf\n", popped);
            val2 = genDouble(x, y);
            push(S1, &val2, N / 2);
            i++;
        }

    } while (i < N);
}
int main(int argc, char *argv[])
{
    Record R = verifica(argc, argv);
    printf("\n%d %d %lf %lf\n", R.N, R.M, R.x, R.y);

    Stack S1 = BuildStack(R.N / 2);
    Stack S2 = BuildStack(R.N / 2);
    int limit = R.N / 2;
    // double ran=2.3;
    // push(&S1,&ran,limit);
    printStack(&S1);
    // double bab;
    // if((bab=pop(&S1))>0){
    // printf("\npopped value==%lf\n",bab);
    // }
    srand(time(0));
    fillStack(&S1, &S2, R.x, R.y, R.M, R.N);
    puts("\n---S1---\n");
    printStack(&S1);
    puts("\n---S2---\n");
    printStack(&S2);
}