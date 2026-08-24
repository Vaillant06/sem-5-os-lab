
// fcfs.c

// Scheduling Algorithm 1: First Come; First Serve Scheduling algorithm
// Implement using Linked List / Queue

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int number_of_process;
    int *burst_time = malloc(number_of_process * sizeof(int));
    int *arrival_time = malloc(number_of_process * sizeof(int));
    int *wait_time = malloc(number_of_process * sizeof(int));
    int *turn_around_time = malloc(number_of_process * sizeof(int));
    int current_time = 0; // Used if arrival time changes
    int total_wait_time = 0;
    int average_wait_time = 0;

    // Get the number of process(s) from the user
    printf("Enter the number of process(s): ");
    scanf("%d", &number_of_process);

    // Get the Burst Time of each process from the user
    printf("\nEnter the burst time of each process:\n");
    for(i = 0; i < number_of_process; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", (burst_time + i));
    }

    // Get the Arrival Time of each process from the user
    printf("\nEnter the Arrival Time of each process:\n");
    for(i = 0; i < number_of_process; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", (arrival_time + i));
    }


    // Calculate FCFS

    // Calculate wait_time, total_wait_time, current_time for each process
    *wait_time = 0;
    for(i = 1; i < number_of_process; i++) {

        if(current_time < *(arrival_time + i)) {
            current_time = *(arrival_time + i);
        }

        *(wait_time + i) = *(wait_time + i - 1) + *(burst_time + i - 1);
        total_wait_time += *(wait_time + i);
        current_time += *(burst_time + i);        
    }

    // Calculate Turn Around Time for each process
    for(i = 0; i < number_of_process; i++) {
        *(turn_around_time + i) = *(wait_time + i) + *(burst_time + i);
    }

    // Results Table
    printf("\nProcess Number\tBurst Time\tWait Time\tTurn Around Time\n");
    for(i = 0; i < number_of_process; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, *(burst_time + i), *(wait_time + i), *(turn_around_time + i));
    }

    // Calculate average Wait Time for the entire process
    average_wait_time = total_wait_time / number_of_process; 
    printf("\nAverage Wait Time: %d\n", average_wait_time);

    // Gantt Chart
    printf("\nGantt Chart\n");

    // Top Border
    for(i = 0; i < number_of_process; i++)
        printf("--------");
    printf("-\n");

    // Print the process IDs
    for(i = 0; i < number_of_process; i++)
        printf("| P%-4d ", i + 1);
    printf("|\n");

    // MiddleBorder
    for(i = 0; i < number_of_process; i++)
        printf("--------");
    printf("-\n");

    // Print the Turn Around Time of each process
    printf("0");

    for(i = 0; i < number_of_process; i++)
        printf("%8d", *(turn_around_time + i));
    printf("\n");

    // Bottom Border
    for(i = 0; i < number_of_process; i++)
        printf("--------");

    printf("-\n");

    return 0;
}