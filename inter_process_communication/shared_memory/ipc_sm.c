
// ipc_sm.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int shmid;
    char *shared_memory;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // Attach shared memory
    shared_memory = (char *)shmat(shmid, NULL, 0);

    if (shared_memory == (char *)-1) {
        perror("shmat");
        return 1;
    }

    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        strcpy(shared_memory, "Hello from Parent!");

        printf("Parent wrote: %s\n", shared_memory);

        sleep(2);

        // Detach shared memory
        shmdt(shared_memory);

        // Remove shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }
    else if (pid == 0) {
        // Child process
        sleep(1);

        printf("Child read: %s\n", shared_memory);

        // Detach shared memory
        shmdt(shared_memory);
    }

    return 0;
}