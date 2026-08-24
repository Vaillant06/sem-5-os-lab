
// priority_scheduling_np.c

#include <stdio.h>

struct Process {
    int pid, at, bt, priority;
    int ct, tat, wt;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nP%d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority: ");
        scanf("%d", &p[i].priority);
    }

    int completed[n];
    for (int i = 0; i < n; i++)
        completed[i] = 0;

    int time = 0;
    int done = 0;

    // Gantt chart arrays
    int gantt_pid[n];
    int gantt_start[n];
    int gantt_end[n];
    int g = 0;

    while (done < n) {

        int index = -1;
        int highest = 9999;

        for (int i = 0; i < n; i++) {
            if (!completed[i] &&
                p[i].at <= time &&
                p[i].priority < highest) {

                highest = p[i].priority;
                index = i;
            }
        }

        // CPU idle
        if (index == -1) {
            time++;
            continue;
        }

        // Store Gantt chart information
        gantt_pid[g] = p[index].pid;
        gantt_start[g] = time;

        time += p[index].bt;

        gantt_end[g] = time;
        g++;

        p[index].ct = time;
        p[index].tat = p[index].ct - p[index].at;
        p[index].wt = p[index].tat - p[index].bt;

        completed[index] = 1;
        done++;
    }

    // ---------------- GANTT CHART ----------------

    printf("\n\nGANTT CHART\n");

    printf("+");
    for (int i = 0; i < g; i++)
        printf("-------+");
    printf("\n");

    printf("|");
    for (int i = 0; i < g; i++)
        printf("  P%d   |", gantt_pid[i]);
    printf("\n");

    printf("+");
    for (int i = 0; i < g; i++)
        printf("-------+");
    printf("\n");

    // Start time
    printf("%-2d", gantt_start[0]);

    for (int i = 0; i < g; i++) {
        printf("%7d", gantt_end[i]);
    }

    printf("\n");

    // ---------------- TABLE ----------------

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    float avg_wt = 0, avg_tat = 0;

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}