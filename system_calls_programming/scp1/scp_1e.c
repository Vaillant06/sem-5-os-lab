
// SYSTEM CALLS PROGRAMMING: (zombie process | defunct)

#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/resource.h>
#include <stdlib.h>

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
        exit(0);
    } else {
        printf("I'm a parent\n");
        sleep(40);
        printf("Parent's PID: %d\n", getpid());
        printf("Parent's parent's PID: %d\n", getppid());
        printf("Parent is exiting...\n\n");
    }

    return;

}