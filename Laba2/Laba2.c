#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 1024

int Array_size () {
    int size;
    printf("%s", "Введите размерность массива строк: ");
    scanf("%d", &size);
    if (size==0)
    {
        printf("%s", "Число строк должно быть больше нуля\n");
        exit (EXIT_SUCCESS);
    }
    return size;
}

char** getting_array(int size) {
    char buffer[LINE_LENGTH];
    char **mas = malloc(sizeof(char *) * size);
    for (int i = 0; i < size+1 ; i++)
    {
        fgets(buffer, LINE_LENGTH, stdin);
        mas[i] = malloc(sizeof(char) * strlen(buffer));
        strcpy(mas[i], buffer);
    }
    printf ("\n%s%c%c%c\n","Первая буква первой строки ", '"', mas[1][0], '"');
    return mas;
}

void print_array (char **Array, int size) {
    printf("\n");
    for (int i = 0; i < size+1; i++)
    {
        printf ("%s", Array[i]);
    }
}

char **sort(char **Array, int size) {
    char str[LINE_LENGTH];
    int Changes = 0;
    for(int i = 1; i < size; i++)
    {
        for(int j = 0; j < size - i; j++)
        {
            if(strcmp(Array[j], Array[j+1]) > 0)
            {
                strcpy(str, Array[j]);
                strcpy(Array[j], Array[j+1]);
                strcpy(Array[j+1], str);
                Changes++;
            }
        }
    }
    printf("%s%d\n","Количкство перестановок = ", Changes);
    return Array;
}

void free_array (char **Array, int size) {
    for (int i = 0; i < size+1; i++)
    {
        free (Array[i]);
    }
    free (Array);
}

int main () {
    int size = Array_size();

    char **Array = NULL;
    Array = getting_array(size);

    char **Sorted_Array = NULL;
    Sorted_Array = sort(Array, size);

    print_array (Sorted_Array, size);

    free_array (Array, size);
}
