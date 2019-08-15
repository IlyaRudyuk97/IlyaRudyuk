// 5. Винни-Пух и пчелы. Заданное количество пчел
//    добывают мед равными порциями, задерживаясь в
//    пути на случайное время. Винни-Пух потребляет
//    мед порциями заданной величины за заданное время
//    и столько же времени может прожить без питания.
//    Работа каждой пчелы реализуется в порожденном процессе.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define ONE_PORTION_OF_HONEY 10
#define ONE_BEE_BRINGS 2
#define DEN 20

int count(int n) {
    int count=0;
    while (n)
    {
        n/=10;
        count++;
    }
    return count;
}

int reading_file() {
    char* file_name = "/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt";
    int myfile = open (file_name, O_RDONLY);
    lockf(myfile, F_LOCK, 0L);

    int* buffer = malloc(sizeof(int)*10);

    read(myfile, buffer, sizeof(int));

    lockf(myfile, F_ULOCK, 0L);
    close(myfile);
    return *buffer;
}

void writing_to_file(int amount_of_honey_in_the_den) {
    char* file_name = "/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt";
    int myfile = open (file_name, O_WRONLY);
    lockf(myfile, F_LOCK, 0L);

    int length = count(amount_of_honey_in_the_den);

    write(myfile, (char*)(&amount_of_honey_in_the_den), length);
    lockf(myfile, F_ULOCK, 0L);
    close(myfile);
}

void bear() {
    sleep(100);
    while (1)
    {
        int amount_of_honey_in_the_den = reading_file();
        printf("Меда в берлоге %d\n", amount_of_honey_in_the_den);

        if (amount_of_honey_in_the_den >= ONE_PORTION_OF_HONEY)
        {
            amount_of_honey_in_the_den = amount_of_honey_in_the_den - ONE_PORTION_OF_HONEY;
            printf("Меда в берлоге после того как медведь поел %d\n", amount_of_honey_in_the_den);
            writing_to_file(amount_of_honey_in_the_den);
            printf("Медведь поел и в целом доволен жизнью\n");
            printf("Меда в берлоге %d\n", amount_of_honey_in_the_den);
            sleep(5);
        }
        else
        {
            sleep(5);
            printf ("Медведь умер\n");
            break;
        }
    }
}

int main(int argc, char** argv) {

    int amount_of_honey_in_the_den = 0;
    int amount_of_bees;
    int stat;

    creat("/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt",__S_IREAD|__S_IWRITE);
    writing_to_file(amount_of_honey_in_the_den);

    printf("Введите количество пчел ");
    scanf("%d", &amount_of_bees);


    pid_t bee[amount_of_bees];

    for (int i = 0; i < amount_of_bees; i++) {
        bee[i] = fork();
        srand(getpid());

        if (-1 == bee[i]) {
            perror("fork");
            exit(1);
        }

        else if (0 == bee[i]) {
            while (1) {
                amount_of_honey_in_the_den = reading_file();
                printf("                                    Меда в берлоге %d\n", amount_of_honey_in_the_den);
                if (amount_of_honey_in_the_den < (DEN - ONE_BEE_BRINGS)) {

                    printf("ПЧЕЛА №%3.d полетела за медом\n", i+1);
                    sleep(rand() % 5);
                    printf("ПЧЕЛА №%3.d вернулась\n", i+1);
                    sleep(rand() % 1);

                    amount_of_honey_in_the_den = amount_of_honey_in_the_den + ONE_BEE_BRINGS;
                    writing_to_file(amount_of_honey_in_the_den);
                }
                else {
                                printf("Венрнергрешел\n");
                    break;
                }
            }
            exit(i+1);
            printf("Вышел\n");
        }
    }


    for (int i = 0; i < amount_of_bees; i++) {
        int status = waitpid(bee[i], &stat, 1);
        if (bee[i] == status) {
            printf("Пчела №%d полетела к другому медведю\n", WEXITSTATUS(stat));
        }
    }

  //  bear();

    //for (int i = 0; i < amount_of_bees; i++) {
    //int status = waitpid(bee[i], &stat, 0);
    //if (bee[i] == status) {
    //printf("\n\nХранилище заполнено медом\n\n");
    //}
    //}

//удаление пчел


    //remove ("/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt");
    //printf("Удалено\n");
    //exit(0);
}
