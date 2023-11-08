#include <stdio.h>

struct Car
{
    char brand[50];
    char model[50];
    int year;
};

int main()
{
    struct Car car1 = {"BMW", "X5", 1999};
    struct Car car2 = {"Ford", "Mustang", 1969};
    struct Car car3 = {"Toyota", "Corolla", 2011};

    printf("%s %s %i \n", car1.brand, car1.model, car1.year);
    printf("%s %s %i \n", car2.brand, car2.model, car2.year);
    printf("%s %s %i \n", car3.brand, car3.model, car3.year);
}

/*
int main(){
    float a = 112.11111;

    printf("%f \n", a);
    printf("%1f \n", a);
    printf("%1.f \n", a);
    printf("%1.1f \n", a);
    printf("%1.2f \n", a);
    printf("%.1f \n", a);
    printf("%2.f \n", a);
    printf("%2.1f \n", a);

}

*/