
// sjf_p.c

#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("Enter AT and BT for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);

        rt[i] = bt[i];
    }

    int time = 0;
    int completed = 0;

    // Maximum possible Gantt segments
    int gantt_pid[100];
    int gantt_start[100];
    int gantt_end[100];
    int g = 0;

    int current = -1;

    while (completed < n) {

        int shortest = -1;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {

            if (at[i] <= time && rt[i] > 0) {

                if (shortest == -1 || rt[i] < rt[shortest]) {
                    shortest = i;
                }
            }
        }

        // CPU idle
        if (shortest == -1) {
            time++;
            continue;
        }

        // CPU switched to another process
        if (shortest != current) {

            // Close previous Gantt segment
            if (current != -1) {
                gantt_end[g - 1] = time;
            }

            // Start new Gantt segment
            gantt_pid[g] = pid[shortest];
            gantt_start[g] = time;

            g++;

            current = shortest;
        }

        // Execute for 1 unit
        rt[shortest]--;
        time++;

        // Process completed
        if (rt[shortest] == 0) {

            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            completed++;
        }
    }

    // Close last Gantt segment
    gantt_end[g - 1] = time;

    // Gantt Chart
    printf("\nGantt Chart:\n");

    for (int i = 0; i < g; i++) {
        printf("|  P%d  ", gantt_pid[i]);
    }
    printf("|\n");

    printf("%d", gantt_start[0]);

    for (int i = 0; i < g; i++) {
        printf("      %d", gantt_end[i]);
    }

    printf("\n");

    // Process table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    float avg_wt = 0;
    float avg_tat = 0;

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i]);

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}