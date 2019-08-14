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
#define ONE_PORTION_OF_HONEY 10
#define ONE_BEE_BRINGS 2

int reading_file() {
    FILE *myfile = fopen("/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt", "r");
    int amount_of_honey_in_the_den;
    fread(&amount_of_honey_in_the_den, sizeof(int), 1, myfile);
    fclose(myfile);
    return amount_of_honey_in_the_den;
}

void writing_to_file(int amount_of_honey_in_the_den) {
    FILE *myfile = fopen("/home/ilya/Чистяков/Лабы/Laba6/amount_of_honey_in_the_den.txt", "w");
    fwrite(&amount_of_honey_in_the_den, sizeof(int), 1, myfile);
    sleep(10);
    fclose(myfile);
}

void bear() {
    sleep (10);
    while (1) {
        int amount_of_honey_in_the_den = reading_file();
        printf ("%d", amount_of_honey_in_the_den);
        if (amount_of_honey_in_the_den >= ONE_PORTION_OF_HONEY)
        {
            amount_of_honey_in_the_den = (amount_of_honey_in_the_den-ONE_PORTION_OF_HONEY);
            writing_to_file(amount_of_honey_in_the_den);
            sleep(10);
        }
        else
        {
            sleep(10);
            printf ("Медведь умер");
            exit(0);
        }
    }
}

int main(int argc, char** argv) {

    //int amount_of_honey_in_the_den = 0;
    //writing_to_file(amount_of_honey_in_the_den);
    int amount_of_bees;
   // int stat;

    printf("Введите количество пчел ");
    scanf("%d", &amount_of_bees);

    //pid_t bee[amount_of_bees];

    //for (int i = 0; i < amount_of_bees; i++)
    //{
        //bee[i] = fork();
        //srand(getpid());

        //if (-1 == bee[i])
        //{
            //perror("fork");
            //exit(1);
        //}

        //else if (0 == bee[i])
        //{
            //amount_of_honey_in_the_den = reading_file();
            //while (amount_of_honey_in_the_den <= 20)
            //{
                //printf("ПЧЕЛА №%d полетела за медом\n", i+1);
                //sleep(rand() % 5); // Время в пути
                //printf("ПЧЕЛА №%d вернулась\n", i+1);
                //sleep(rand() % 2); // Время выгрузки меда

                //amount_of_honey_in_the_den = reading_file();
                //printf("ДО ЗАПИСИ      %d\n", amount_of_honey_in_the_den);
                ////sleep(10);
                
                //amount_of_honey_in_the_den = (amount_of_honey_in_the_den+ONE_BEE_BRINGS);
                //writing_to_file(amount_of_honey_in_the_den);
               
                //amount_of_honey_in_the_den = reading_file();
                //printf("ПОСЛЕ ЗАПИСИ      %d\n", amount_of_honey_in_the_den);
                ////sleep(10);
            //}
            //printf ("Хранилище полно меда");
            //exit(0);


            
        //}
    //}

    //for (int i = 1; i < amount_of_bees; i++) {
        //int status = waitpid(bee[i], &stat, 0);
        //if (bee[i] == status) {
            //bear();
        //}
    //}

//printf ("Хранилище полно меда");

}
