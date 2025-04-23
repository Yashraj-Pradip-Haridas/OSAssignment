#include <stdio.h>

// Structure to store process info
struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
};

// Swap function for sorting
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to calculate Waiting and Turnaround Time
void calculateTimes(struct Process p[], int n) {
    p[0].waitingTime = 0;
    p[0].turnaroundTime = p[0].burstTime;

    for (int i = 1; i < n; i++) {
        p[i].waitingTime = p[i - 1].waitingTime + p[i - 1].burstTime;
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
    }
}

// FCFS Scheduling
void fcfs(struct Process p[], int n) {
    // Sort by arrival time
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].arrivalTime > p[j+1].arrivalTime) {
                swap(&p[j], &p[j+1]);
            }
        }
    }

    calculateTimes(p, n);

    printf("\nFCFS Scheduling:\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].waitingTime, p[i].turnaroundTime);
    }
}

// SJF Non-Preemptive Scheduling
void sjf(struct Process p[], int n) {
    // Sort by burst time (after arrival)
    for (int i = 0; i < n; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].arrivalTime <= p[minIdx].arrivalTime && p[j].burstTime < p[minIdx].burstTime) {
                minIdx = j;
            }
        }
        swap(&p[i], &p[minIdx]);
    }

    calculateTimes(p, n);

    printf("\nSJF (Non-Preemptive) Scheduling:\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].waitingTime, p[i].turnaroundTime);
    }
}

int main() {
    int n;
    struct Process p[20];

    // Input
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }

    // Make copies of the original data for both algorithms
    struct Process p_fcfs[20], p_sjf[20];
    for (int i = 0; i < n; i++) {
        p_fcfs[i] = p[i];
        p_sjf[i] = p[i];
    }

    // Run FCFS
    fcfs(p_fcfs, n);

    // Run SJF
    sjf(p_sjf, n);

    return 0;
}
