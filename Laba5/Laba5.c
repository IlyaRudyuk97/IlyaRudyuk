#include <stdio.h>
#include <stdlib.h>
extern float square(float a);
extern float root(float a);


int main () {
    float a;
    //char b[1024];

    printf ("Введите число: ");
    scanf ("%f", &a);
    //a = atoi(b);

    float rezult1 = square(a);
    float rezult2 = root(a);

    printf ("%.6g в квадрате равно %.3f\n", a, rezult1);
    printf ("Корень из %.6g равен %.3f\n", a, rezult2);
    return 0;
}
