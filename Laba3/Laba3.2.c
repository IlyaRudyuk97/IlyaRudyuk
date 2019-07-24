#include <stdio.h>
#include <stdlib.h>

struct book {
    char book_name[50];
    int edition_year;
    int amount_of_pages;
    int cost;
};
typedef struct book book_pamams;

void read_book_pamams (book_pamams *bk, int i) {

    printf("Введите название %dй книги: ", i);
    scanf("%s", bk -> book_name);
    printf("Введите год издания ");
    scanf("%d", &bk -> edition_year);
    printf("Введите количество страниц: ");
    scanf("%d", &bk -> amount_of_pages);
    printf("Введите стоимость книги ");
    scanf("%d", &bk -> cost);
    printf("\n");
}

static int compare(const void *p1, const void *p2) {
    book_pamams *bk1 = *(book_pamams**)p1;
    book_pamams *bk2 = *(book_pamams**)p2;
    return bk2->book_name - bk1->book_name;
}

int main(int argc, char **argv) {
    int count;
    printf("Введите количество книг: ");
    scanf("%d", &count);
    printf("\n");
    book_pamams **bk = malloc(sizeof(book_pamams*)*count);
    for (int i = 0; i < count ; i++) {
        bk[i] = malloc(sizeof(book_pamams));
        read_book_pamams(bk[i], i+1);
    }

    qsort(bk, count, sizeof(book_pamams*), compare);

    printf("Книги в алфавитном порядке:\n\n");
    for (int i = 0; i < count; i++)
    {
        printf("Название книги: %s\n", bk[i]->book_name);
        printf("Год издания: %d\n", bk[i]->edition_year);
        printf("Количество страниц: %d\n", bk[i]->amount_of_pages);
        printf("Стоимость : %d\n\n", bk[i]->cost);
    }


    for (int i = 0; i < count; i++)
    {
        free(bk[i]);
    }
    free(bk);

    return 0;
}
