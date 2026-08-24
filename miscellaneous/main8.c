
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int *arr =(int*)malloc(sizeof(int)*5);
    int i;
    for(i=0;i<5;i++){
        arr[i] = i;
    } 

    int pid = fork();

    if(pid != 0){
        for(i=0;i<5;i++){
            printf("%d ", arr[i]* i);
        } 
    }else{
        for(i=0;i<5;i++){
            printf("%d ", arr[i]* 2);
        } 
    }

    printf("\nProcess ID: %d\n", pid);

    return 0;
}