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
#define PATH "amount_of_honey_in_the_den.txt"

int reading_file() {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    char* file_name = PATH;
    int myfile = open (file_name, O_RDONLY);

    int buffer;

    lock.l_type = F_RDLCK;
    fcntl(myfile, F_SETLKW, &lock);

    read(myfile, &buffer, sizeof(int));
    lseek(myfile, 0, 0);

    lock.l_type = F_UNLCK;
    fcntl(myfile, F_SETLKW, &lock);
    close(myfile);

    return buffer;
}

void reading_and_writing_to_file(int act) {
    struct flock lock;
    memset(&lock, 0, sizeof(lock));

    char* file_name = PATH;
    int myfile = open(file_name, O_RDWR);

    int buffer;

    lock.l_type = F_WRLCK;
    fcntl(myfile, F_SETLKW, &lock);

    read(myfile, &buffer, sizeof(int));
    lseek(myfile, 0, 0);
    if (act == 1) {
        buffer = buffer + ONE_BEE_BRINGS;
    }
    else if (act == -1) {
        buffer = buffer - ONE_PORTION_OF_HONEY;
    } else if (act == 0) {
        buffer = DEN;
    }
    write(myfile, &buffer, sizeof(int));
    lseek(myfile, 0, 0);

    lock.l_type = F_UNLCK;
    fcntl(myfile, F_SETLKW, &lock);
    close(myfile);
}

void bear_create() {
    sleep(5);
    while (1)
    {
        int amount_of_honey_in_the_den = reading_file();
        if (amount_of_honey_in_the_den >= ONE_PORTION_OF_HONEY)
        {
            reading_and_writing_to_file(-1);
            printf("Медведь поел и в целом доволен жизнью\n");
            fflush(stdout);
            amount_of_honey_in_the_den = reading_file();
            printf("Меда в берлоге осталось %d\n", amount_of_honey_in_the_den);
            fflush(stdout);
            sleep(5);
        }
        else
        {
            sleep(5);
            reading_and_writing_to_file(0);
            break;
        }
    }
    exit(0);
}

int main() {
    int amount_of_bees;

    creat(PATH,__S_IREAD|__S_IWRITE);
    int amount_of_honey_in_the_den = 0;
    char* file_name = PATH;

    int myfile = open(file_name, O_WRONLY);
    write(myfile, &amount_of_honey_in_the_den, sizeof(int));
    lseek(myfile, 0, 0);
    close(myfile);

    printf("Введите количество пчел ");
    scanf("%d", &amount_of_bees);

    pid_t bee[amount_of_bees];

    for (int i = 0; i < amount_of_bees; i++) {

        bee[i] = fork();
        srand(getpid());

        if (-1 == bee[i]) {
            perror("fork bee");
            exit(1);
        }

        else if (0 == bee[i]) {
            while (1) {
                amount_of_honey_in_the_den = reading_file();
                printf("ПЧЕЛА №%2.d полетела за медом\n", i+1);
                sleep(rand() % 5);
                printf("ПЧЕЛА №%2.d вернулась\n", i+1);
                sleep(rand() % 1);
                amount_of_honey_in_the_den = reading_file();
                if (amount_of_honey_in_the_den < DEN) {
                    reading_and_writing_to_file(1);
                }
                else {
                    break;
                }
            }
            exit(i+1);
        }
    }

    pid_t bear;
    bear = fork();
    if (-1 == bear) {
        perror("fork bear");
        exit(1);
    }
    else if (0 == bear) {
        bear_create();
    }

    int return_code_bee;
    for (int i = 0; i < amount_of_bees; i++) {
        wait(&return_code_bee);
        printf("Пчела №%d полетела к другому медведю\n", WEXITSTATUS(return_code_bee));
    }

    int return_code_bear;
    waitpid(bear, &return_code_bear, 0);
    printf("Медведь умер\n");

    remove (PATH);
    exit(0);
}

