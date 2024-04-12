#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SHM_KEY 0x123

double calculateAverage(char * fileName) {
    FILE * file;
    file = fopen(fileName, "r");
    double sum = 0.0;
    int count = 0, num;
    if (file == NULL) {
        printf("Cannot open the file!!!");
        return 0.0;
    } else {
        while (fscanf(file, "%*d %*d %d %*d\n", &num) == 1) {
            sum += num;
            count++;
        }
    }
    fclose(file);
    return (double)(sum / count);
}

int main(int argc, char * argv []){
    pid_t child_pid;
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        printf("- Child process information:\n");

        int shmid;
        double * shm;
        shmid = shmget(SHM_KEY, sizeof(double), 0644 | IPC_CREAT);

        if (shmid < 0) {
            perror("Shared memory");
            return 1;
        } else {
            printf("Shared memory ID: %d\n", shmid);
        }

        shm = (double *) shmat(shmid, NULL, 0);

        if (shm == (double *)- 1) {
            perror("shmat");
            exit(1);
        }

        printf("shared memory -mm :  %p\n", shm);
        *shm = calculateAverage("movie-100k_2.txt");
        printf("Child process calculating average result: %lf\n", *shm);
        printf("Shared memory content: %lf\n\n", *shm);

        if (shmdt(shm) == -1) {
            perror("shmdt");
            return 1;
        }

        return 0;
    } else {
        wait(NULL);
        printf("- Parent process information:\n");

        int shmid;
        double * shm;
        shmid = shmget(SHM_KEY, sizeof(double), 0644 | IPC_CREAT);

        if (shmid < 0) {
            perror("shmget");
            return 1;
        } else {
            printf("shared memory ID:  %d\n", shmid);
        }

        shm = (double *) shmat(shmid, NULL, 0);

        if (shm == (double *)- 1) {
            perror("shmat");
            exit(1);
        }

        printf("shared memory -mm :  %p\n", shm);
        printf("Shared memory content get from child: %lf\n", *shm);
        printf("Parent process calculating average result: %lf\n", calculateAverage("movie-100k_1.txt"));
        
        if (shmdt(shm) == -1) {
            perror("shmdt");
            return 1;
        }
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
        return 0;
    }
}