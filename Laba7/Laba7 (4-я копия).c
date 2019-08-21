//13. Голодные игры. Родительский процесс создает
//    указанное количество дочерних, фиксируя их
//    идентификаторы (например, в файле). Каждый
//    дочерний процесс удаляет из списка произвольный
//    идентификатор, если он не равен его собственному
//    и отправляет системный запрос на уничтожение
//    другого процесса, чей идентификатор он выбрал.
//    Игра прекращается. когда останется один участник,
//    родительский процесс сообщает идентификатор победителя.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATH "processes.txt"

void clearing_file(char* file_name) {
    remove (file_name);
    FILE* mf = fopen(file_name, "w");
    fclose(mf);
}

void writing_to_file(pid_t* pid, int amount_of_processes) {
    FILE *myfile = fopen(PATH, "a");
    flock(fileno(myfile), LOCK_EX);
    fseek (myfile, 0, SEEK_END);

    for (int i = 0; i < amount_of_processes; i++)
    {
        fprintf (myfile, "%d\n", pid[i]);
    }

    flock(fileno(myfile), LOCK_UN);
    fclose (myfile);
}

int main() {

    clearing_file(PATH);
    int amount_of_processes;
    printf("Введите количество дочерних процессов ");
    scanf("%d", &amount_of_processes);

    pid_t process[amount_of_processes];
    char PIPE_PATH[20];

    for (int i = 0; i < amount_of_processes; i++) {

        process[i] = fork();        
        srand(getpid());

        if (0 == process[i]) {
            printf("Потомок %d\n", i);
            char* buf = malloc(sizeof(char)*20);
            sprintf(buf, "/tmp/fifo.%d", i);
            strcpy(PIPE_PATH ,buf);
            printf("%s!\n", PIPE_PATH);
            mkfifo(PIPE_PATH, 0666);
//exit(0);
            int writefd = open(PIPE_PATH, O_WRONLY, 0);
          exit(0);
            char mypid = getpid();
exit(0);
            write(writefd, &mypid, strlen(&mypid));
            lseek(writefd, 0, 0);
            close(writefd);
exit(0);
            sleep(1);
            sleep(rand() % 1);
exit(0);
            int victum_number = (rand() % amount_of_processes);
            char victum_pid;
            int readfd = open(PIPE_PATH, O_RDONLY, 0);
            read(readfd, &victum_pid, strlen(&victum_pid));
            lseek(readfd, 0, 0);
            close(readfd);

            printf("victum_pid %d\n", victum_pid);


            //int victum_number = (rand() % amount_of_processes);
            ////printf("%d", victum_number);
            //int victum_pid;
            //close(fd[i][1]);
            //read(fd[victum_number][0], &victum_pid, sizeof(int));

            //printf("Процесс №%2.d (pid %d) выбрал к чачестве жертвы процесс №%2.d (pid %d)\n",
            //i+1, getpid(), victum_number+1, victum_pid);
            //fflush(stdout);
            exit(0);
        }
    }


  writing_to_file(process, amount_of_processes);

    int process_return_code;
    for (int i = 0; i < amount_of_processes; i++) {
        wait(&process_return_code);
    }

    fflush(stdout);
    printf("XXX %s\n", PIPE_PATH);
    exit(0);



    //for (int i = 0; i < amount_of_processes; i++) {
    //int my_pid;
    //close(fd[i][1]);
    //read(fd[i][0], &my_pid, sizeof(int));
    //printf("read %d\n", my_pid);
    //}

    exit(0);
}

