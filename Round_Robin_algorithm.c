#include <stdio.h>
struct process {
    int pid;
    int bt;
    int tat;
    int wt;
    int rbt;
};
int main() {
    int n, tq, i, x = 0, y = 0; // x for current time and y for process number count
    // Accept the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    // Accept pid and burst time (bt) of each process
    for (i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d",&p[i].bt);
        p[i].pid = i + 1;
        p[i].rbt = p[i].bt;  // Initialize remaining burst time (rbt) to burst time (bt)
    }
    // Accept time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &tq);
    i = 0;
    while (1) {
        if (p[i].rbt > 0) {
            if (p[i].rbt > tq) {
                x += tq;
                p[i].rbt -= tq;
            } else {
                x += p[i].rbt;
                p[i].rbt = 0;
                y++;                        // incrementing the process number count
                p[i].tat = x;               // Calculate Turnaround Time
                p[i].wt = p[i].tat - p[i].bt; // Calculate Waiting Time
            }
        }
        if (y == n) {  // All processes completed
            break;
        }
        if (i == n - 1) { // to continue the process schedule loop
            i = 0;
        } else {
            i++;
        }
    }
    // Print PID, BT, TAT, and WT in table format
    printf("\nPID\tBT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].tat, p[i].wt);
    }
    return 0;
}