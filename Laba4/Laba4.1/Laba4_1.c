#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_STRINGS 1024
#define LINE_LENGTH 1024



typedef struct args {
    char file[1024];
    char word[1024];
} args;

void free_arr(char **arr, int size) {
    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }
    free (arr);
}

void free_string_begin(char **string_begin, int size) {
    for (int i = 0; i < size; i++)
    {
        free(string_begin[i]);
    }
    free (string_begin);
}

char** reading_file(FILE *myfile, int length, int size) {
    char buffer[length];
    char **arr = malloc(sizeof(char*) * length);
    for (int i = 0; i <  size; i++)
    {
        fgets(buffer, length, myfile);
        arr[i] = malloc(sizeof(char) * strlen(buffer));
        strcpy(arr[i], buffer);
    }
    fclose(myfile);
    return arr;
}

int lines_counting() {
    FILE *myfile = fopen("source.txt", "r");
    size_t lines_count = 0;
    while (! feof(myfile))
    {
        if (fgetc(myfile) == '\n')
            lines_count++;
    }
    fclose(myfile);
    return lines_count;
}

void print_readed_arr(char** arr, int size, char* word, char** string_begin, int lines_count) {
    FILE *myfile = fopen("source.doc", "w");
    for (int i = 0; i < lines_count; i++)
    {
        if (strcmp(word, string_begin[i]))
        {
            fwrite(arr[i], sizeof(char), strlen(arr[i]), myfile);
        }
    }
    fclose(myfile);
}

char** reading_strings_begin(FILE *myfile, char** arr, int word_length, int size) {
    char **string_begin = malloc(sizeof(char*) * size);
    for (int i = 0; i < size; i++)
    {
        string_begin[i] = malloc(sizeof(char) * word_length); //ПОЧЕМУ МОЖНО СТАВИТЬ А МОЖНО И НЕ СТАВИТЬ
        strncpy (string_begin[i], arr[i], word_length);
        string_begin[i][word_length] = '\0';
    }
    return string_begin;
}

args define_arguments (int argc, char** argv) {
    args arguments;
    if (argc > 2)
    {
        strcpy(arguments.file, argv[1]);
        strcpy(arguments.word, argv[2]);
    }
    else
    {
        printf("Не задано имя файла и/или искомое слово\n");
        exit(0);
    }
    return arguments;
}

int main (int argc, char** argv) {
    args arguments = define_arguments(argc, argv);
    FILE *myfile = fopen(arguments.file, "r");
    int word_length = strlen(arguments.word);
    char* word_ro_find = arguments.word;
    char** readed_arr = reading_file(myfile,LINE_LENGTH, NUMBER_OF_STRINGS);
    char** string_begin = reading_strings_begin(myfile, readed_arr, word_length, NUMBER_OF_STRINGS);
    int lines_count = lines_counting();
    print_readed_arr(readed_arr, NUMBER_OF_STRINGS, word_ro_find, string_begin, lines_count );
    free_arr(readed_arr, NUMBER_OF_STRINGS);
    free_arr(string_begin, NUMBER_OF_STRINGS);
    return 0;
}


