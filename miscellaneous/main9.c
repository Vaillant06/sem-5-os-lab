
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char str[] = "SSNCE";

int main() {
    int pid = fork();
    int i;

    printf("Before : %s\n\n", str);
    
    if(pid == 0){
        for(i = 0; i < 5; i++)
        {
            if(i == 3){
                str[3] = 'S';
                printf("%c",str[i]);
            }else{
                printf("%c",str[i]);
            }
        }
    }else{
    for(i = 0; i < 5; i++)
        {
        printf("%c",str[i]);
            
        }    }

    printf("\nProcess ID: %d\n", pid);

    return 0;
}