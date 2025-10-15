#include <stdio.h>

typedef struct {
    int pid;       // Process ID
    int bt;        // Burst Time
    int priority;  // Priority
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
} Process;

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    // Input process details
    for(i = 0; i < n; i++){
        p[i].pid = i + 1;
        printf("Enter burst time and priority for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].bt, &p[i].priority);
    }

    // Sort processes based on priority (smaller number = higher priority)
    for(i = 0; i < n-1; i++){
        for(j = i+1; j < n; j++){
            if(p[i].priority > p[j].priority){
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Completion Time, TAT, WT
    p[0].ct = p[0].bt;
    p[0].tat = p[0].ct;
    p[0].wt = p[0].tat - p[0].bt;

    for(i = 1; i < n; i++){
        p[i].ct = p[i-1].ct + p[i].bt;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }

    // Print process table
    printf("\nP#\tBT\tP\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    // Calculate averages
    float totalTAT = 0, totalWT = 0;
    for(i = 0; i < n; i++){
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    printf("\nAverage TAT = %.2f\n", totalTAT / n);
    printf("Average WT = %.2f\n", totalWT / n);

    return 0;
}
