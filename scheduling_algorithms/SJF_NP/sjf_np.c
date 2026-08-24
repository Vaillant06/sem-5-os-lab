
// sjf_np.c

#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
    int completed[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        completed[i] = 0;

        printf("Enter AT and BT for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    int time = 0;
    int count = 0;

    // Gantt chart arrays
    int gantt_pid[n];
    int gantt_start[n];
    int gantt_end[n];
    int g = 0;

    while (count < n) {

        int shortest = -1;

        // Find shortest burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= time) {

                if (shortest == -1 || bt[i] < bt[shortest]) {
                    shortest = i;
                }
            }
        }

        // CPU idle
        if (shortest == -1) {
            time++;
            continue;
        }

        // Store Gantt chart information
        gantt_pid[g] = pid[shortest];
        gantt_start[g] = time;

        // Execute process completely
        time += bt[shortest];

        gantt_end[g] = time;
        g++;

        // Calculate times
        ct[shortest] = time;
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];

        completed[shortest] = 1;
        count++;
    }

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