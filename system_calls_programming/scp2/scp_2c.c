
// System Calls Programming II (c)
// Running a C program from another C program

// scp2_c.c (Running Is Perfect Square number inside Prime Number)

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int number, i;
    int isPrime = 1;

    int pid = fork();

    if(pid < 0) {
        printf("Fork Failed!\n");
        return 1;

    } else if(pid == 0) {
        // Child Process
        // scp_2b.c
        printf("Running scp_2b.c (Child)\n");
        execl("scp_2b", "scp_2b", NULL); // Specify Full Path for the first arguement

    } else {
        // scp_2c.c
        // Parent Process
        wait(0);
        printf("\n");
        printf("Running scp_2c.c (Parent)\n");
        printf("Enter a number to find if it is prime: ");
        scanf("%d", &number);

        if(number <= 1) isPrime = 0;
        else {
            for(i = 2; i * i <= number; i++) {
                if(number % i == 0) {
                    isPrime = 0;
                    break;
                }
            }
        }

        if(isPrime) printf("%d is a prime Number.\n", number);
        else printf("%d is not a prime number.\n", number);
    }

    return 0;
}