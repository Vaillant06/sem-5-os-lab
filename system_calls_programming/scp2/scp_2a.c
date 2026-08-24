
// System Calls Programming II (a)
// Running a C program from another C program

// scp2_a.c (Is Prime number)

#include <stdio.h>

int main() {
    int number, i;
    int isPrime = 1;

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

    return 0;
}