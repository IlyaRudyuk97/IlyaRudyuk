#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main (int argc, char* argv[]) {
    float a;
    printf ("Введите число: ");
    scanf ("%f", &a);

    void *ext_library = dlopen("/home/ilya/Чистяков/Лабы/Laba5/Laba5_3/libmath_operations.so", RTLD_LAZY);
    float (*square)(float a);
    float (*root)(float a);

    square = dlsym(ext_library, "square");
    root = dlsym(ext_library, "root");

    printf ("%.6g в квадрате равно %.3f\n", a, square(a));
    printf ("Корень из %.6g равен %.3f\n", a, root(a));
    dlclose(ext_library);
    
    return 0;
}
