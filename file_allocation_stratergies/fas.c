
// fas.c

// Contiguous, Linked and Indexed File Allocation Stratergies

#include <stdio.h>

#define MAX 50

void contiguous(int base[], int n, int size) {
    int disk[MAX], i, j, start = -1;

    for (i = 0; i < size; i++)
        disk[i] = base[i];

    for (i = 0; i <= size - n; i++) {
        for (j = i; j < i + n && disk[j] == 0; j++);

        if (j == i + n) {
            start = i;
            break;
        }
    }

    printf("\nCONTIGUOUS ALLOCATION\n");

    if (start == -1) {
        printf("Allocation not possible\n");
        return;
    }

    printf("Allocated blocks: ");
    for (i = start; i < start + n; i++) {
        disk[i] = 1;
        printf("%d ", i);
    }
    printf("\n");
}

void linked(int base[], int n, int size) {
    int disk[MAX], blocks[MAX];
    int i, count = 0;

    for (i = 0; i < size; i++)
        disk[i] = base[i];

    for (i = 0; i < size && count < n; i++)
        if (disk[i] == 0)
            blocks[count++] = i;

    printf("\nLINKED ALLOCATION\n");

    if (count < n) {
        printf("Allocation not possible\n");
        return;
    }

    printf("Linked blocks: ");
    for (i = 0; i < n; i++) {
        disk[blocks[i]] = 1;
        printf("%d", blocks[i]);

        if (i < n - 1)
            printf(" -> ");
    }

    printf(" -> NULL\n");
}

void indexed(int base[], int n, int size) {
    int disk[MAX], blocks[MAX];
    int i, count = 0, indexBlock = -1;

    for (i = 0; i < size; i++)
        disk[i] = base[i];

    for (i = 0; i < size; i++) {
        if (disk[i] == 0) {
            indexBlock = i;
            break;
        }
    }

    printf("\nINDEXED ALLOCATION\n");

    if (indexBlock == -1) {
        printf("No free block for index\n");
        return;
    }

    disk[indexBlock] = 1;

    for (i = 0; i < size && count < n; i++)
        if (disk[i] == 0)
            blocks[count++] = i;

    if (count < n) {
        printf("Allocation not possible\n");
        return;
    }

    for (i = 0; i < n; i++)
        disk[blocks[i]] = 1;

    printf("Index block: %d\n", indexBlock);
    printf("Data blocks: ");

    for (i = 0; i < n; i++)
        printf("%d ", blocks[i]);

    printf("\n");
}

int main(void) {
    int base[MAX] = {0};
    int size, occupied, n, i, block;

    printf("Enter disk size (max 50): ");
    scanf("%d", &size);

    if (size < 2 || size > MAX) {
        printf("Invalid disk size\n");
        return 1;
    }

    printf("Enter number of occupied blocks: ");
    scanf("%d", &occupied);

    if (occupied < 0 || occupied >= size) {
        printf("Invalid number of occupied blocks\n");
        return 1;
    }

    printf("Enter occupied block numbers: ");
    for (i = 0; i < occupied; i++) {
        scanf("%d", &block);

        if (block < 0 || block >= size || base[block]) {
            printf("Invalid or duplicate block\n");
            return 1;
        }

        base[block] = 1;
    }

    printf("Enter number of data blocks required: ");
    scanf("%d", &n);

    if (n < 1 || n >= size) {
        printf("Invalid file size\n");
        return 1;
    }

    contiguous(base, n, size);
    linked(base, n, size);
    indexed(base, n, size);

    return 0;
}
