
// round_robin.c

#include <stdio.h>

struct Process {
    int pid;
    int at;         // Arrival Time
    int bt;         // Burst Time
    int remaining;  // Remaining Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
};

int main() {
    int n, tq;

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

        p[i].remaining = p[i].bt;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    /*
        Ready Queue
    */
    int queue[1000];
    int front = 0;
    int rear = 0;

    int visited[n];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    /*
        Gantt Chart arrays
    */
    int gantt_pid[1000];
    int gantt_start[1000];
    int gantt_end[1000];

    int g = 0;

    int time = 0;
    int completed = 0;

    /*
        Find the first arriving process
    */
    int first = -1;

    for (int i = 0; i < n; i++) {
        if (first == -1 || p[i].at < p[first].at)
            first = i;
    }

    time = p[first].at;

    /*
        Add processes that have arrived
    */
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {

        /*
            If queue is empty, CPU is idle
        */
        if (front == rear) {

            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].remaining > 0) {

                    if (next == -1 || p[i].at < p[next].at)
                        next = i;
                }
            }

            if (next != -1) {
                time = p[next].at;
                queue[rear++] = next;
                visited[next] = 1;
            }

            continue;
        }

        /*
            Get process from front of queue
        */
        int index = queue[front++];

        int start = time;

        /*
            Execute for Time Quantum or remaining burst time
        */
        int execution_time;

        if (p[index].remaining < tq)
            execution_time = p[index].remaining;
        else
            execution_time = tq;

        time += execution_time;
        p[index].remaining -= execution_time;

        /*
            Store Gantt chart segment
        */
        gantt_pid[g] = p[index].pid;
        gantt_start[g] = start;
        gantt_end[g] = time;
        g++;

        /*
            Add newly arrived processes to queue
        */
        for (int i = 0; i < n; i++) {

            if (!visited[i] &&
                p[i].at <= time &&
                p[i].remaining > 0) {

                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        /*
            If process is not completed,
            put it at the back of the queue
        */
        if (p[index].remaining > 0) {
            queue[rear++] = index;
        }
        else {
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;

            completed++;
        }
    }

    /*
        -------------------------
           PRINT GANTT CHART
        -------------------------
    */

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

    /*
        Print time values
    */
    printf("%-2d", gantt_start[0]);

    for (int i = 0; i < g; i++)
        printf("%7d", gantt_end[i]);

    printf("\n");

    /*
        -------------------------
           PRINT TABLE
        -------------------------
    */

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float avg_wt = 0;
    float avg_tat = 0;

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f",
           avg_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avg_tat / n);

    return 0;
}