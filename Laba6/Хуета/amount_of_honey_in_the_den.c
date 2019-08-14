#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)  /* записываем знак */
        n = -n;          /* делаем n положительным числом */
    i = 0;
    do {       /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0';   /* берем следующую цифру */
    } while ((n /= 10) > 0);     /* удаляем */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int reading_file() {
    FILE *myfile = fopen("/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt", "r");
    int amount_of_honey_in_the_den;
    fread(&amount_of_honey_in_the_den, sizeof(int), 1, myfile);
    fclose(myfile);
    return amount_of_honey_in_the_den;
}

void writing_to_file(int amount_of_honey_in_the_den) {
    FILE *myfile = fopen("/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt", "w");
    char* buf = NULL;
    int aaa = amount_of_honey_in_the_den;
    itoa(aaa, buf);
    fwrite(&amount_of_honey_in_the_den, strlen(buf), 1, myfile);
    fclose(myfile);
}

int main () {
    int amount_of_honey_in_the_den = 20;
    int writing_symbols_amount = (sizeof(amount_of_honey_in_the_den));
    printf("%d", writing_symbols_amount);
    return 0;

}
