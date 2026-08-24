
// fcfs.c

#include <stdio.h>
#include <sys/types.h>

#define MAXIMUM_PROCESS 100

// Create a process datatype using structure
typedef struct {
    pid_t id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int wait_time;
} process;

// Create a queue using structure
typedef struct {
    int data[MAXIMUM_PROCESS];
    int front;
    int rear;
} queue;

// Adding elements to queue
void enqueue(queue *q, int value) {
    if(q->rear == MAXIMUM_PROCESS - 1) {
        perror("Queue");
        return;
    }

    q->data[++q->rear] = value;
}

// Removing elements from queue
int dequeue(queue *q) {
    if(q->front > q->rear) {
        perror("Queue");
        return -1;
    }

    return q->data[q->front++];
}

// Check whether the queue is empty
int isEmpty(queue *q) {
    return q->front > q->rear;
}

int main() {

    process p[MAXIMUM_PROCESS];
    queue q;

    int number_of_process;
    int current_time = 0;
    int completed_process = 0;
    float total_turn_around_time = 0;
    float total_waiting_time = 0;

    q.front = 0;
    q.rear = -1;

    printf("Enter the number of process: ");
    scanf("%d", &number_of_process);

    for(int i = 0; i < number_of_process; i++) {
        p[i].id = i + 1;

        printf("Enter the arrival time and burst time for p%d: ", p[i].id);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    int nextProcess = 0;
    int gantt_process[MAXIMUM_PROCESS];
    int gantt_time[MAXIMUM_PROCESS + 1];
    int gantt_count = 0;

    // FCFS 
    while(completed_process < number_of_process) {
        while(nextProcess < number_of_process && p[nextProcess].arrival_time <= current_time) {
            enqueue(&q, nextProcess);
            nextProcess++;
        }

        if(isEmpty(&q)) {
            current_time = p[nextProcess].arrival_time;
            continue;
        }

        int index = dequeue(&q);

        gantt_process[gantt_count] = p[index].id;

        if(current_time < p[index].arrival_time) {
            current_time = p[index].arrival_time;
        }

        gantt_time[gantt_count] = current_time;

        current_time += p[index].burst_time;
        gantt_time[gantt_count + 1] = current_time;
        p[index].completion_time = current_time;
        p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
        p[index].wait_time = p[index].turn_around_time - p[index].burst_time;

        total_turn_around_time += p[index].turn_around_time;
        total_waiting_time += p[index].wait_time;

        completed_process++;
        gantt_count++;
    }

    // Results table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < number_of_process; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].id,
            p[i].arrival_time,
            p[i].burst_time,
            p[i].completion_time,
            p[i].turn_around_time,
            p[i].wait_time
        );
    }

    printf("Average Turn Around Time: %.2f\n", total_turn_around_time/number_of_process);
    printf("Average Wait Time: %.2f\n", total_waiting_time/number_of_process);

    // Gantt Chart
    printf("\nGantt Chart:\n\n");

    for (int i = 0; i < gantt_count; i++) {
        printf("|   P%d   ", gantt_process[i]);
    }

    printf("|\n");

    printf("%d", gantt_time[0]);

    for (int i = 1; i <= gantt_count; i++) {
        printf("       %d", gantt_time[i]);
    }

    printf("\n");

    return 0;
}