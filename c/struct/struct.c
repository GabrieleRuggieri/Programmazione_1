#include <stdio.h>
#include <string.h>

struct myStructure
{                      // Structure declaration
    int myNum;         // Member (int variable)
    char myLetter;     // Member (char variable)
    char myString[30]; // string
};                     // End the structure with a semicolon

// Create a 2nd structure
struct myStructure2
{
    int myNum2;
    char myLetter2;
    char myString2[30];
};

int main()
{

    // Create different structure variable
    struct myStructure s1;
    struct myStructure s2;

    // Assign values to different struct variables
    s1.myNum = 13;
    s1.myLetter = 'B';

    s2.myNum = 20;
    s2.myLetter = 'C';

    // s1.myString = "Some text";    ERROR!

    // Assign a value to the string using strcpy function
    strcpy(s1.myString, "Some text");

    // Print values
    printf("My number: %i \n", s1.myNum);
    printf("My letter: %c \n", s1.myLetter);
    printf("My string: %s \n\n", s1.myString);

    // 2nd structure

    // Create a structure variable and assign values to it
    struct myStructure2 s3 = {13, 'B', "Some text \n"};

    // Print values
    printf("%i \n%c \n%s \n", s3.myNum2, s3.myLetter2, s3.myString2);

    // Modify values
    s3.myNum2 = 30;
    s3.myLetter2 = 'C';
    strcpy(s3.myString2, "Something else");

    // Print values
    printf("Values after modification: \n");
    printf("%i \n%c \n%s \n", s3.myNum2, s3.myLetter2, s3.myString2);

    return 0;
}
