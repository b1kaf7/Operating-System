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

void swap(struct Process *xp, struct Process *yp)
{
      struct Process temp = *xp;
      *xp = *yp;
      *yp = temp;
}

void sort_by_arrival_time(struct Process proc[], int n)
{
      for (int i = 0; i < n - 1; i++)
      {
            for (int j = 0; j < n - i - 1; j++)
            {
                  if (proc[j].arrival_time > proc[j + 1].arrival_time)
                  {
                        swap(&proc[j], &proc[j + 1]);
                  }
            }
      }
}

void srtf(struct Process proc[], int n)
{
      int current_time = 0;
      int completed = 0;
      int shortest = 0;
      int finish_time;
      int total_waiting_time = 0;
      int total_turnaround_time = 0;

      // Copy burst times to remaining times
      for (int i = 0; i < n; i++)
      {
            proc[i].remaining_time = proc[i].burst_time;
      }

      // Process until all processes are completed
      while (completed != n)
      {
            int min_remaining_time = 9999; // Large number for comparison
            for (int j = 0; j < n; j++)
            {
                  if (proc[j].arrival_time <= current_time && !proc[j].completed && proc[j].remaining_time < min_remaining_time)
                  {
                        shortest = j;
                        min_remaining_time = proc[j].remaining_time;
                  }
            }

            // Execute shortest remaining time process
            proc[shortest].remaining_time--;
            current_time++;

            // Check if process is completed
            if (proc[shortest].remaining_time == 0)
            {
                  proc[shortest].completed = true;
                  completed++;
                  finish_time = current_time;
                  total_waiting_time += finish_time - proc[shortest].burst_time - proc[shortest].arrival_time;
                  total_turnaround_time += finish_time - proc[shortest].arrival_time;
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
                   finish_time - proc[i].burst_time - proc[i].arrival_time, finish_time - proc[i].arrival_time);
      }
      printf("\nAverage waiting time: %.2f\n", avg_waiting_time);
      printf("Average turnaround time: %.2f\n", avg_turnaround_time);
}

int main()
{
      int n;
      printf("Enter number of processes: ");
      scanf("%d", &n);

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

      // Sort processes by arrival time
      sort_by_arrival_time(proc, n);

      // Execute SRTF scheduling
      srtf(proc, n);

      return 0;
}
