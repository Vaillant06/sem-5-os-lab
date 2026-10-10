
// dma.c

// First Fit, Best Fit, Worst Fit


#include <stdio.h>

void firstFit(int block[], int b, int process[], int p) {
    int alloc[20], i, j;

    for (i = 0; i < p; i++)
        alloc[i] = -1;

    for (i = 0; i < p; i++) {
        for (j = 0; j < b; j++) {
            if (block[j] >= process[i]) {
                alloc[i] = j;
                block[j] -= process[i];
                break;
            }
        }
    }

    printf("\nFirst Fit:\n");
    printf("Process\tSize\tBlock\n");
    for (i = 0; i < p; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int block[], int b, int process[], int p) {
    int alloc[20], i, j, best;

    for (i = 0; i < p; i++)
        alloc[i] = -1;

    for (i = 0; i < p; i++) {
        best = -1;

        for (j = 0; j < b; j++) {
            if (block[j] >= process[i]) {
                if (best == -1 || block[j] < block[best])
                    best = j;
            }
        }

        if (best != -1) {
            alloc[i] = best;
            block[best] -= process[i];
        }
    }

    printf("\nBest Fit:\n");
    printf("Process\tSize\tBlock\n");
    for (i = 0; i < p; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int block[], int b, int process[], int p) {
    int alloc[20], i, j, worst;

    for (i = 0; i < p; i++)
        alloc[i] = -1;

    for (i = 0; i < p; i++) {
        worst = -1;

        for (j = 0; j < b; j++) {
            if (block[j] >= process[i]) {
                if (worst == -1 || block[j] > block[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            alloc[i] = worst;
            block[worst] -= process[i];
        }
    }

    printf("\nWorst Fit:\n");
    printf("Process\tSize\tBlock\n");
    for (i = 0; i < p; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int block[20], process[20], b, p, i;
    int temp[20];

    printf("Enter number of memory blocks: ");
    scanf("%d", &b);

    if (b < 1 || b > 20) {
        printf("Invalid number of blocks\n");
        return 1;
    }

    printf("Enter block sizes:\n");
    for (i = 0; i < b; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &p);

    if (p < 1 || p > 20) {
        printf("Invalid number of processes\n");
        return 1;
    }

    printf("Enter process sizes:\n");
    for (i = 0; i < p; i++)
        scanf("%d", &process[i]);

    for (i = 0; i < b; i++)
        temp[i] = block[i];
    firstFit(temp, b, process, p);

    for (i = 0; i < b; i++)
        temp[i] = block[i];
    bestFit(temp, b, process, p);

    for (i = 0; i < b; i++)
        temp[i] = block[i];
    worstFit(temp, b, process, p);

    return 0;
}
