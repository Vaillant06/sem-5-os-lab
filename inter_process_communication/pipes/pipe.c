
// pipe.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;

    char message[] = "Hello from parent!";
    char buffer[100];

    // Create pipe
    pipe(fd);

    // Create child process
    pid = fork();

    if (pid > 0) {
        // Parent process

        close(fd[0]);  // Parent doesn't read

        write(fd[1], message, strlen(message) + 1);

        close(fd[1]);  // Close writing end
    }
    else if (pid == 0) {
        // Child process

        close(fd[1]);  // Child doesn't write

        read(fd[0], buffer, sizeof(buffer));

        printf("Child received: %s\n", buffer);

        close(fd[0]);  // Close reading end
    }

    return 0;
}