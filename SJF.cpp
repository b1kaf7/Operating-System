#include <stdio.h>
#include <stdbool.h>

struct Process
{
  int pid;                 // Process ID
  int burst_time;          // Burst time
  int arrival_time;        // Arrival time
  int original_burst_time; // Original burst time for correct waiting time calculation
  bool completed;          // Completion status
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

void sjf(struct Process proc[], int n)
{
  int current_time = 0;
  int completed = 0;
  int total_waiting_time = 0;
  int total_turnaround_time = 0;

  // Sort processes by arrival time
  sort_by_arrival_time(proc, n);

  while (completed != n)
  {
    int shortest = -1;

    // Find the process with the shortest burst time that has arrived
    for (int j = 0; j < n; j++)
    {
      if (proc[j].arrival_time <= current_time && !proc[j].completed)
      {
        if (shortest == -1 || proc[j].burst_time < proc[shortest].burst_time)
        {
          shortest = j;
        }
      }
    }

    if (shortest == -1)
    {
      current_time++;
      continue;
    }

    // Calculate waiting and turnaround times
    proc[shortest].burst_time--;
    current_time++;

    if (proc[shortest].burst_time == 0)
    {
      proc[shortest].completed = true;
      completed++;
      int waiting_time = current_time - proc[shortest].arrival_time - proc[shortest].original_burst_time;
      int turnaround_time = current_time - proc[shortest].arrival_time;

      total_waiting_time += waiting_time;
      total_turnaround_time += turnaround_time;
    }
  }

  // Calculate average waiting and turnaround time
  float avg_waiting_time = (float)total_waiting_time / n;
  float avg_turnaround_time = (float)total_turnaround_time / n;

  // Print results
  printf("\nPID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++)
  {
    int waiting_time = current_time - proc[i].arrival_time - proc[i].original_burst_time;
    int turnaround_time = current_time - proc[i].arrival_time;
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].original_burst_time,
           waiting_time, turnaround_time);
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
    proc[i].original_burst_time = proc[i].burst_time; // Store the original burst time
    proc[i].completed = false;
  }

  // Execute SJF scheduling
  sjf(proc, n);

  return 0;
}
