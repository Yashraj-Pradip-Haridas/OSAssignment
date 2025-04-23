#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Function to sort processes based on arrival time and burst time (for SJF Preemptive)
void sortProcesses(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime || 
                (p[j].arrivalTime == p[j + 1].arrivalTime && p[j].burstTime > p[j + 1].burstTime)) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to implement SJF Preemptive Scheduling (Shortest Remaining Time First)
void sjfPreemptive(struct Process p[], int n) {
    int time = 0;  // Start time
    int completed = 0;
    int prevProcess = -1;

    while (completed < n) {
        int idx = -1;
        int shortestRemainingTime = 10000;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= time && p[i].remainingTime > 0 && p[i].remainingTime < shortestRemainingTime) {
                shortestRemainingTime = p[i].remainingTime;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;  // No process to execute, move time forward
            continue;
        }

        // If the process changes, record its start time
        if (p[idx].remainingTime == p[idx].burstTime) {
            p[idx].startTime = time;
        }

        // Execute the process for 1 unit of time
        p[idx].remainingTime--;
        time++;

        // If process is completed
        if (p[idx].remainingTime == 0) {
            p[idx].completionTime = time;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            completed++;
        }
    }
}

// Function to calculate average waiting and turnaround times
void calculateAverages(struct Process p[], int n) {
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += p[i].waitingTime;
        avgTurnaroundTime += p[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time = %.2f", avgWaitingTime / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTurnaroundTime / n);
}

// Function to print process details and Gantt Chart
void printResults(struct Process p[], int n) {
    printf("\nPID\tArrival\tBurst\tStart\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].startTime, p[i].completionTime,
               p[i].waitingTime, p[i].turnaroundTime);
    }
}

// Function to print Gantt chart for the execution order
void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart: ");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", p[i].id);
    }
    printf("|\n");
}

int main() {
    int n;
    struct Process p[20];

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input the details for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
    }

    // Sort processes by arrival time and burst time for SJF Preemptive
    sortProcesses(p, n);

    // Run SJF Preemptive Scheduling
    sjfPreemptive(p, n);

    // Print the results
    printResults(p, n);

    // Calculate averages
    calculateAverages(p, n);

    // Print Gantt Chart
    printGanttChart(p, n);

    return 0;
}
