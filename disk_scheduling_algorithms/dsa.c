
// dsa.c

// FCFS, SSTF, SCAN C-SCAN


#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sort(int a[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

void fcfs(int a[], int n, int head) {
    int i, current = head, total = 0;

    printf("\nFCFS\nSeek Sequence: %d", head);
    for (i = 0; i < n; i++) {
        total += abs(current - a[i]);
        current = a[i];
        printf(" -> %d", current);
    }
    printf("\nTotal Head Movement: %d\n", total);
}

void sstf(int a[], int n, int head) {
    int visited[MAX] = {0};
    int i, j, nearest, distance;
    int current = head, total = 0;

    printf("\nSSTF\nSeek Sequence: %d", head);

    for (i = 0; i < n; i++) {
        nearest = -1;
        distance = 1000000;

        for (j = 0; j < n; j++) {
            if (!visited[j] &&
                abs(current - a[j]) < distance) {
                distance = abs(current - a[j]);
                nearest = j;
            }
        }

        visited[nearest] = 1;
        current = a[nearest];
        total += distance;
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void scan(int a[], int n, int head, int size) {
    int b[MAX], i, split = 0;
    int current = head, total = 0;

    for (i = 0; i < n; i++) b[i] = a[i];
    sort(b, n);

    while (split < n && b[split] < head) split++;

    printf("\nSCAN\nSeek Sequence: %d", head);

    for (i = split; i < n; i++) {
        total += abs(current - b[i]);
        current = b[i];
        printf(" -> %d", current);
    }

    if (current != size - 1) {
        total += abs(current - (size - 1));
        current = size - 1;
        printf(" -> %d", current);
    }

    for (i = split - 1; i >= 0; i--) {
        total += abs(current - b[i]);
        current = b[i];
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void cscan(int a[], int n, int head, int size) {
    int b[MAX], i, split = 0;
    int current = head, total = 0;

    for (i = 0; i < n; i++) b[i] = a[i];
    sort(b, n);

    while (split < n && b[split] < head) split++;

    printf("\nC-SCAN\nSeek Sequence: %d", head);

    for (i = split; i < n; i++) {
        total += abs(current - b[i]);
        current = b[i];
        printf(" -> %d", current);
    }

    if (split > 0) {
        if (current != size - 1) {
            total += abs(current - (size - 1));
            current = size - 1;
            printf(" -> %d", current);
        }

        total += size - 1;
        current = 0;
        printf(" -> %d", current);

        for (i = 0; i < split; i++) {
            total += abs(current - b[i]);
            current = b[i];
            printf(" -> %d", current);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

int main(void) {
    int a[MAX], n, head, size, i;

    printf("Enter disk size: ");
    scanf("%d", &size);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (size < 1 || n < 1 || n > MAX) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter request cylinders: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        if (a[i] < 0 || a[i] >= size) {
            printf("Invalid cylinder number\n");
            return 1;
        }
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= size) {
        printf("Invalid head position\n");
        return 1;
    }

    fcfs(a, n, head);
    sstf(a, n, head);
    scan(a, n, head, size);
    cscan(a, n, head, size);

    return 0;
}
