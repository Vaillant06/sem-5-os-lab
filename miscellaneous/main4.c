
#include <stdio.h>
#include <stdlib.h>

int global1 = 10;
int global2;

void display(int num){
    int local = 20;

    printf("Local Variable: %d\n", local);
    printf("Variable from main: %d\n", num);
}

void main() {
    int mainLocal = 100;
    int *p = (int*)malloc(sizeof(int));

    *p = 200;

    printf("Value pointed by the pointer: %d\n", *p);

    display(mainLocal);

    free(p);

    return;
}