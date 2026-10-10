
// fot.c

// Sequential, Direct and Indexed File Organization Techniques


#include <stdio.h>

#define MAX 100

int records[MAX];
int present[MAX] = {0};
int ids[MAX], count = 0;

void sequential(void) {
    int i;

    printf("\nSEQUENTIAL ORGANIZATION\n");
    for (i = 0; i < count; i++)
        printf("ID = %d, Data = %d\n",
               ids[i], records[ids[i]]);
}

void direct(int id) {
    printf("\nDIRECT ORGANIZATION\n");

    if (id >= 0 && id < MAX && present[id])
        printf("Record found: ID = %d, Data = %d\n",
               id, records[id]);
    else
        printf("Record not found\n");
}

void indexed(int id) {
    int i;

    printf("\nINDEXED ORGANIZATION\n");

    for (i = 0; i < count; i++) {
        if (ids[i] == id) {
            printf("Index found: ID = %d, Position = %d\n",
                   id, i);
            printf("Record data = %d\n", records[id]);
            return;
        }
    }

    printf("Record not found in index\n");
}

int main(void) {
    int n, i, id, data, searchID;

    printf("Enter number of records (max 100): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of records\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter record ID (0-99) and data: ");
        scanf("%d%d", &id, &data);

        if (id < 0 || id >= MAX || present[id]) {
            printf("Invalid or duplicate record ID\n");
            return 1;
        }

        ids[count++] = id;
        records[id] = data;
        present[id] = 1;
    }

    printf("Enter record ID to search: ");
    scanf("%d", &searchID);

    sequential();
    direct(searchID);
    indexed(searchID);

    return 0;
}
