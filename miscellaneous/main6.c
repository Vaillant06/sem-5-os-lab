
#include <stdio.h>
#include <stdlib.h>


int a = 100;
int b;

void main() {

    int c = 300;
    char str[256];

    FILE *fp;
    fp = fopen("/proc/self/maps", "r");

    if(fp) {
        printf("Opens\n");
    }
    else printf("Fails\n");

    while(fgets(str, sizeof(str), fp)) {
        printf("%s\n", str);
    }

    fclose(fp);

    return;
}