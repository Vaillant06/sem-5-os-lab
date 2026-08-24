
// scp_3b.c

// System Calls Programming III (b)

// Working with pipe for reading and writing file contents

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    int val = pipe(pipe_fd);

    if(val < 0) printf("Pipe Creation Failed!\n");
    else printf("Pipe Creation Succeeded!\n");

    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork Failed");
        return 1;

    } else if(pid == 0) {
        // Child Process
        close(pipe_fd[1]); // For reading, close the write end of the pipe

        char msg2[256];

        read(pipe_fd[0], msg2, sizeof(msg2));

        // printf("Child Reads... %s\n", msg2);
        write(1, "Child reads from the file...\n", 29);
        write(1, msg2, strlen(msg2));

        // printf("Child Reads from the pipe...\n");
        // printf("%s\n", msg2);

        close(pipe_fd[0]);

    } else {
        //Parent Process
            
        int fd = open("output.txt", O_RDONLY);

        char msg[256];

        if(fd < 0) {
            perror("File Open Failed");
            return 1;

        } else {
            close(pipe_fd[0]); // For writing, close the read end of the pipe

            // read(pipe_fd[1], msg, sizeof(msg));
            int n = read(fd, msg, sizeof(msg));

            // printf("%s\n", msg);
            

            // printf("Parent writes into the pipe...\n");
            // write(STDOUT_FILE, msg, sizeof(msg));
            write(pipe_fd[1], msg, sizeof(msg));
            write(1, "Parent writes into the file...\n", 31);
            close(fd);
            close(pipe_fd[1]);
        }
    }

    return 0;
}