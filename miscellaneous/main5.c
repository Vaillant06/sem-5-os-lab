
#include <stdio.h>
#include <stdlib.h>

int global1 = 10;
int global2;

void display(int num){
    int local = 20;

    printf("Local Variable Address: %p\n", (void*)&local);
    printf("Value of the Local Variable: %d\n\n", local);

    printf("Address of variable from main: %p\n", (void*)&num);
    printf("Value of the Variable from main: %d\n\n", num);
}

void main() {
    int mainLocal = 100;
    int *p = (int*)malloc(sizeof(int));

    *p = 200;

    printf("Address of main function: %p\n\n", (void*)main);
    printf("Address of display function: %p\n\n", (void*)display);

    printf("Address of Global 1: %p\n", (void*)&global1);
    printf("Value of Global 1: %d\n\n", global1);

    printf("Address of Global 2: %p\n", (void*)&global2);
    printf("Value of Global 2: %d\n\n", global2);

    printf("Address of the pointer: %p\n", (void*)&p);
    printf("Address of the heap pointed by the pointer: %p\n", (void*)p);
    printf("Value pointed by the pointer: %d\n\n", *p);

    display(mainLocal);

    free(p);

    return;
}