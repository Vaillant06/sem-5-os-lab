
// priority_scheduling_p.c

#include <stdio.h>

struct Process {
    int pid, at, bt, priority;
    int remaining;
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

        p[i].remaining = p[i].bt;
    }

    int time = 0;
    int completed = 0;

    // Gantt chart arrays
    int gantt_pid[100];
    int gantt_start[100];
    int gantt_end[100];
    int g = 0;

    int previous = -1;
    int segment_start = 0;

    while (completed < n) {

        int index = -1;
        int highest = 9999;

        // Find highest-priority process
        for (int i = 0; i < n; i++) {

            if (p[i].at <= time &&
                p[i].remaining > 0 &&
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

        // CPU switched to another process
        if (index != previous) {

            // Close previous Gantt segment
            if (previous != -1) {
                gantt_pid[g] = previous + 1;
                gantt_start[g] = segment_start;
                gantt_end[g] = time;
                g++;
            }

            // Start new segment
            segment_start = time;
            previous = index;
        }

        // Execute for one time unit
        p[index].remaining--;
        time++;

        // Process completed
        if (p[index].remaining == 0) {

            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;

            completed++;
        }
    }

    // Close final Gantt segment
    if (previous != -1) {
        gantt_pid[g] = previous + 1;
        gantt_start[g] = segment_start;
        gantt_end[g] = time;
        g++;
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

    // Time values
    printf("%-2d", gantt_start[0]);

    for (int i = 0; i < g; i++)
        printf("%7d", gantt_end[i]);

    printf("\n");

    // ---------------- TABLE ----------------

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    float avg_wt = 0;
    float avg_tat = 0;

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