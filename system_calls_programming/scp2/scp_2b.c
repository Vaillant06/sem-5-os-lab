
// System Calls Programming II (b)
// scp2_b.c (Is Perfect Square)

#include <stdio.h>

int main() {

    int number, i;
    int isPerfectSquare = 0;

    printf("Enter a number to find if it is a perfect square: ");
    scanf("%d", &number);

    for(i = 0; i * i <= number; i++) {
        if(i * i == number) {
            isPerfectSquare = 1;
            break;
        } 
    }

    if(isPerfectSquare) printf("%d is a perfect square number.\n", number);
    else printf("%d is not a perfect square number.\n", number);

    return 0;
}