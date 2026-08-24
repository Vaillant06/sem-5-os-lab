
// System Calls Programming II (b)

// menu_driven_program.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    int option;

    while(1) {
        printf("\n1: ls -l\n");
        printf("2: pwd\n");
        printf("3: who\n");
        printf("4: cat filename\n");
        printf("5: cal\n");
        printf("6: date\n");
        printf("7: cp filename1 filename2\n");
        printf("8: rm filename\n");
        printf("9: ps -el\n");
        printf("10: sort\n");
        printf("11. End\n");

        printf("Enter an option (1-10): ");
        scanf("%d", &option);

        pid_t pid = fork();

        if(pid < 0) {
            printf("Fork Failed!\n");
            return 1;

        } else if(pid == 0) {
            switch(option) {
                case 1:     
                    execlp("ls", "ls", "-l", NULL);
                    break;
                
                case 2:
                    execlp("pwd", "pwd", NULL);
                    break;
                
                case 3:
                    execlp("who", "who", NULL);
                    break;

                case 4:
                    execlp("cat", "cat", "sample.txt", NULL);
                    break;
                
                case 5:
                    execlp("cal", "cal", NULL);
                    break;
                
                case 6:
                    execlp("date", "date", NULL);
                    break;
                
                case 7:
                    execlp("cp", "cp", "sample.txt", "sample1.txt", NULL);
                    break;
                
                case 8:
                    execlp("rm", "rm", "sample1.txt", NULL);
                    break;

                case 9:
                    execlp("ps", "ps", "-el", NULL);
                    break;
                
                case 10:
                    execlp("sort", "sort", "sample.txt", NULL);
                    break;

                case 11:
                    printf("End of the prgram...\n");
                    exit(0);
                    break;

                default:
                    printf("Enter a valid option!\n");
            }

        } else {
            wait(NULL);

            if(option == 11) break;
        }
    }
    
    return 0;
}