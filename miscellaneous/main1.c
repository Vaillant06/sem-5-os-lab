#include <stdio.h>
#include <stdlib.h>

#define a 10

void findEvenOdd(int n) {
    // if(n % 2 == 0) printf("%d is an even number.", n);
    // else printf("%d is an odd number", n);

    printf("\nGlobal Variable: %d", a);
}

int main() {

    int num;

    int *p = (int*)malloc(sizeof(int));

    printf("Global Variable: %d", a);

    *p = 123;

    // printf("%d", *p);

    // printf("Enter a number: ");
    // scanf("%d", &num);

    findEvenOdd(num);

    free(p);

    return 0;
}