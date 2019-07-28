//Написать программу, выполняющую посимвольную обработку текстового файла

//Заменить цифры на пробелы
//Параметры командной строки:
//1. Имя входного файла
//2. Количество замен

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_STRINGS 1024
#define LINE_LENGTH 1024

typedef struct args {
    char file[1024];
    char replacement_number[1024];
} args;

args define_arguments (int argc, char** argv) {
    args arguments;
    if (argc > 2)
    {
        strcpy(arguments.file, argv[1]);
        strcpy(arguments.replacement_number, argv[2]);
    }
    else
    {
        printf("Не задано имя файла и/или количество замен\n");
        exit(0);
    }
    return arguments;
}

void numerals_deleting(args arguments) {
    FILE *file1 = fopen(arguments.file, "r+");
    int c;
    int cursor = 0;
    int replacement_done = 0;
    while ( ((c=fgetc(file1))!=EOF) \
    && (atoi((char*)&(arguments.replacement_number)) > replacement_done))
    {
        if(c>='0' && c <= '9')
        {
            fseek( file1, cursor,  SEEK_SET );
            fputc(' ', file1);
            cursor++;
            replacement_done++;
        }
        else
        {
            fseek( file1, cursor,  SEEK_SET );
            putc(c, file1);
            cursor++;
        }
    }
}



int main (int argc, char** argv) {
    args arguments = define_arguments(argc, argv);
    numerals_deleting(arguments);
    return 0;
}


