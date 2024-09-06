#include <stdio.h>
#include <stdbool.h>

struct Process
{
    int pid;            // Process ID
    int burst_time;     // Burst time
    int remaining_time; // Remaining time
    int arrival_time;   // Arrival time
    bool completed;     // Completion status
};

void rr(struct Process proc[], int n, int quantum)
{
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int completed = 0;

    // Copy burst times to remaining times
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining_time = proc[i].burst_time;
    }

    // Process until all processes are completed
    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (!proc[i].completed)
            {
                if (proc[i].remaining_time > 0)
                {
                    if (proc[i].remaining_time > quantum)
                    {
                        current_time += quantum;
                        proc[i].remaining_time -= quantum;
                    }
                    else
                    {
                        current_time += proc[i].remaining_time;
                        proc[i].remaining_time = 0;
                        proc[i].completed = true;
                        total_waiting_time += current_time - proc[i].arrival_time - proc[i].burst_time;
                        total_turnaround_time += current_time - proc[i].arrival_time;
                        completed++;
                    }
                }
            }
        }
    }

    // Calculate average waiting and turnaround time
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    // Print results
    printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               current_time - proc[i].arrival_time - proc[i].burst_time, current_time - proc[i].arrival_time);
    }
    printf("\nAverage waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);
}

int main()
{
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details for Process %d:\n", i + 1);
        proc[i].pid = i + 1;
        printf("Arrival time: ");
        scanf("%d", &proc[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &proc[i].burst_time);
        proc[i].completed = false;
    }

    // Execute Round Robin scheduling
    rr(proc, n, quantum);

    return 0;
}
