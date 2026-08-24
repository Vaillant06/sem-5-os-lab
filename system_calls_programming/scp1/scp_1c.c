
// SYSTEM CALLS PROGRAMMING: Part (C)

#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void main() {

    int pid = fork();

    if(pid < 0) {
        printf("Fork Failed. No new process created.\n");
    }

    if(pid == 0) {
        printf("I'm a child\n");
        printf("Child's PID: %d\n", getpid());
        printf("Child's parent's PID: %d\n", getppid());
        printf("Child is exiting...\n\n");
    } else {
        // sleep(10); // time to pause the process (seconds default)
        // wait(0);
        wait(NULL);
        printf("I'm a parent\n");
        printf("Parent's PID: %d\n", getpid());
        printf("Parent's parent's PID: %d\n", getppid());
        printf("Parent is exiting...\n\n");
    }

    return;

}