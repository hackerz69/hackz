#include <stdio.h>
#include <stdlib.h>
struct process
{
    int pid;
    int at, bt;        // Arrival Time, Burst Time
    int tat, wt, ct;   // Turnaround Time, Waiting Time, Completion Time
};
// Function to sort processes by Arrival Time
void sortbyAT(struct process p[], int n)
{
    struct process temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].at < p[i].at)  // Sort based on arrival time
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
// Function to calculate Completion Time
void completionTime(struct process p[], int n, int x)
{
    int currentTime = x;
    for (int i = 0; i < n; i++)
    {
        if (i == 0) // for the first occuring process
        {
            currentTime = p[i].at + p[i].bt;
            p[i].ct = currentTime;
        }
        else
        {
            if (p[i].at > currentTime)  // If there's idle time, wait until process arrives
            {
                int idleTime = p[i].at - currentTime;
                currentTime = currentTime + idleTime + p[i].bt; // adding the idle time and burst time of the process to the currentTime
                p[i].ct = currentTime; // now the current time will be the completion time for the current process
            }
            else  // No idle time, just add burst time
            {
                currentTime += p[i].bt;
                p[i].ct = currentTime;
            }
           
        }
    }
}
// Function to calculate Turnaround Time and Waiting Time
void TATandWT(struct process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;   // TAT = CT - AT
        p[i].wt = p[i].tat - p[i].bt;   // WT = TAT - BT
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct process p[n];
    
    // Input processes details
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
    }

    // Sort processes by Arrival Time
    sortbyAT(p, n);

    // Calculate completion time
    int currentTime = 0;
    completionTime(p, n, currentTime);

    // Calculate Turnaround Time and Waiting Time
    TATandWT(p, n);

    // Display process details
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
