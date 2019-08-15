#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int count(int n) {
    int count=0;
    while (n) {
        n/=10;
        count++; }
    return count;
}

int* reading_file() {
    char* file_name = "/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt";
    int myfile = open (file_name, O_RDONLY);
    lockf(myfile, F_LOCK, 0L);
    
    int* buffer = malloc(sizeof(int)*10);
    
    read(myfile, buffer, sizeof(int));
    
    lockf(myfile, F_ULOCK, 0L);
    close(myfile);
    return buffer;
}

void writing_to_file(int amount_of_honey_in_the_den) {
    char* file_name = "/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt";
    int myfile = open (file_name, O_WRONLY);
    lockf(myfile, F_LOCK, 0L);
    printf("DEN %d\n", amount_of_honey_in_the_den);
    
    int length = count(amount_of_honey_in_the_den);
    printf("COUNT %d\n", length);
    
    write(myfile, (char*)(&amount_of_honey_in_the_den), 2);
        printf("Writen\n");
        //exit(0);
    lockf(myfile, F_ULOCK, 0L);
    close(myfile);
}

int main () {
    int amount_of_honey_in_the_den;
    scanf("%i", &amount_of_honey_in_the_den);
    //printf("COUNT %d\n", count(amount_of_honey_in_the_den));
    writing_to_file(amount_of_honey_in_the_den);
    int a = *reading_file();
    printf("XXX   %d", a);
    return 0;

}
