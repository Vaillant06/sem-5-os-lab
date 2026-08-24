
// scp_3a.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork Failed!\n");
        return 1;

    } else if(pid == 0) {
        // Child Process
        char msg1[64];
        int fd1 = open("output.txt", O_RDONLY);

        printf("%d\n", fd1);

        if(fd1 < 0) {
            perror("Open Error");
            exit(1);
        }

        printf("Child Reads...\n");
        read(fd1, msg1, sizeof(msg1));
        printf("%s\n", msg1);

        close(fd1);

    } else {
        // Parent Process
        // char msg[] = "Linux System calls";
        char msg[] = "Sreenath";
        int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 644);

        printf("%d\n", fd);

        if(fd < 0) {
            perror("Open Error");
            exit(1);
        }

        printf("Parent writes... %s\n", msg);
        write(fd, msg, sizeof(msg));
        // write(fd, msg, strlen(msg));

        close(fd);
    }

    return 0;
}