#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int completedTime;
};

// Swap helper for sorting
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Calculate waiting & turnaround time
void calculateTimes(struct Process p[], int n) {
    p[0].waitingTime = 0;
    p[0].turnaroundTime = p[0].burstTime;
    p[0].completedTime = p[0].burstTime;

    for (int i = 1; i < n; i++) {
        p[i].waitingTime = p[i - 1].completedTime - p[i].arrivalTime;
        if (p[i].waitingTime < 0) {
            p[i].waitingTime = 0; // Process arrived after previous one completed
        }
        p[i].completedTime = p[i].waitingTime + p[i].burstTime + p[i].arrivalTime;
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
    }
}

// Priority Scheduling (Non-Preemptive)
void priorityScheduling(struct Process p[], int n) {
    // Sort by priority (lower = higher priority), break ties with arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority ||
               (p[j].priority == p[j + 1].priority &&
                p[j].arrivalTime > p[j + 1].arrivalTime)) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    calculateTimes(p, n);

    printf("\nPriority Scheduling (Non-Preemptive):\n");
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].priority, p[i].waitingTime, p[i].turnaroundTime);
    }

    // Calculate averages
    float avgWaiting = 0, avgTurnaround = 0;
    for (int i = 0; i < n; i++) {
        avgWaiting += p[i].waitingTime;
        avgTurnaround += p[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time = %.2f", avgWaiting / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTurnaround / n);

    // Print Gantt Chart
    printf("\nGantt Chart: ");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", p[i].id);
    }
    printf("|\n");
}

int main() {
    int n;
    struct Process p[20];

    // Input
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
    }

    // Run Priority Scheduling
    priorityScheduling(p, n);

    return 0;
}
