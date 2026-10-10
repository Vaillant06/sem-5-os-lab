
#include <stdio.h>

void display(int frames[], int f) {
    int i;
    for (i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
}

void fifo(int pages[], int n, int f) {
    int frames[20], i, j, k = 0, faults = 0, hit;

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n--- FCFS / FIFO ---\n");

    for (i = 0; i < n; i++) {
        hit = 0;

        for (j = 0; j < f; j++)
            if (frames[j] == pages[i])
                hit = 1;

        if (!hit) {
            frames[k] = pages[i];
            k = (k + 1) % f;
            faults++;
        }

        printf("%d: ", pages[i]);
        display(frames, f);
        printf("%s\n", hit ? "Hit" : "Fault");
    }

    printf("Total page faults = %d\n", faults);
}

void lru(int pages[], int n, int f) {
    int frames[20], last[20];
    int i, j, pos, faults = 0, hit;

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        last[i] = -1;
    }

    printf("\n--- LRU ---\n");

    for (i = 0; i < n; i++) {
        hit = 0;
        pos = -1;

        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) {
                hit = 1;
                pos = j;
                break;
            }

        if (hit) {
            last[pos] = i;
        } else {
            faults++;
            pos = -1;

            for (j = 0; j < f; j++)
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }

            if (pos == -1) {
                pos = 0;
                for (j = 1; j < f; j++)
                    if (last[j] < last[pos])
                        pos = j;
            }

            frames[pos] = pages[i];
            last[pos] = i;
        }

        printf("%d: ", pages[i]);
        display(frames, f);
        printf("%s\n", hit ? "Hit" : "Fault");
    }

    printf("Total page faults = %d\n", faults);
}

void optimal(int pages[], int n, int f) {
    int frames[20], i, j, k, pos, farthest, next;
    int faults = 0, hit;

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n--- Optimal ---\n");

    for (i = 0; i < n; i++) {
        hit = 0;

        for (j = 0; j < f; j++)
            if (frames[j] == pages[i])
                hit = 1;

        if (!hit) {
            faults++;
            pos = -1;

            for (j = 0; j < f; j++)
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }

            if (pos == -1) {
                farthest = -1;
                pos = 0;

                for (j = 0; j < f; j++) {
                    next = n;

                    for (k = i + 1; k < n; k++)
                        if (pages[k] == frames[j]) {
                            next = k;
                            break;
                        }

                    if (next > farthest) {
                        farthest = next;
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
        }

        printf("%d: ", pages[i]);
        display(frames, f);
        printf("%s\n", hit ? "Hit" : "Fault");
    }

    printf("Total page faults = %d\n", faults);
}

int main() {
    int pages[100], n, f, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of pages\n");
        return 1;
    }

    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames (1-20): ");
    scanf("%d", &f);

    if (f < 1 || f > 20) {
        printf("Invalid number of frames\n");
        return 1;
    }

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}
