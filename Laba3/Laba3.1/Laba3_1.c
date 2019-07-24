#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3

struct book_pamams {
    char book_name[50];
    int edition_year;
    int amount_of_pages;
    int cost;
};
typedef struct book_pamams book_pamams;

book_pamams books[N];

int main(int argc, char **argv) {

    for (int i = 1; i < N+1; i++)
    {
        printf("Введите название %dй книги: ", i);
        scanf("%s", books[i].book_name);
        printf("Введите год издания ");
        scanf("%d", &books[i].edition_year);
        printf("Введите количество страниц: ");
        scanf("%d", &books[i].amount_of_pages);
        printf("Введите стоимость книги ");
        scanf("%d", &books[i].cost);
        printf("\n");
    }

    printf("Список добавленных книг:\n\n");

    for (int i = 1; i < N+1; i++)
    {
        printf("Название книги: %s\n", books[i].book_name);
        printf("Год издания: %d\n", books[i].edition_year);
        printf("Количество страниц: %d\n", books[i].amount_of_pages);
        printf("Стоимость : %d\n\n", books[i].cost);
    }
}
