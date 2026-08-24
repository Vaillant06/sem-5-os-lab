
// ipc_semp.c 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;
};

void wait_sem(int semid)
{
    struct sembuf operation = {0, -1, 0};
    semop(semid, &operation, 1);
}

void signal_sem(int semid)
{
    struct sembuf operation = {0, 1, 0};
    semop(semid, &operation, 1);
}

int main()
{
    key_t key;
    int semid;
    pid_t pid;

    key = ftok(".", 'S');

    // Create semaphore
    semid = semget(key, 1, 0666 | IPC_CREAT);

    if (semid == -1)
    {
        perror("semget");
        exit(1);
    }

    // Initialize semaphore to 1
    union semun arg;
    arg.val = 1;

    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        // Child process

        wait_sem(semid);

        printf("Child: Entering critical section\n");

        for (int i = 1; i <= 5; i++)
        {
            printf("Child: %d\n", i);
            sleep(1);
        }

        printf("Child: Leaving critical section\n");

        signal_sem(semid);
    }
    else
    {
        // Parent process

        wait(NULL);

        wait_sem(semid);

        printf("Parent: Entering critical section\n");

        for (int i = 1; i <= 5; i++)
        {
            printf("Parent: %d\n", i);
            sleep(1);
        }

        printf("Parent: Leaving critical section\n");

        signal_sem(semid);

        // Remove semaphore
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}