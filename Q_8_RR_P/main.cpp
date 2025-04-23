#include <stdio.h>
#define MAX 100

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completed;
};

int main() {
    struct Process p[MAX];
    int n, timeQuantum;
    int totalTime = 0, completed = 0;
    int avgWaiting = 0, avgTurnaround = 0;

    // Input
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].completed = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    // Round Robin Execution
    int time = 0;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};
    int i;

    // Enqueue first arriving processes
    for (i = 0; i < n; i++) {
        if (p[i].arrivalTime == time) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    printf("\nGantt Chart:\n|");
    while (completed < n) {
        if (front == rear) {
            time++;
            for (i = 0; i < n; i++) {
                if (!visited[i] && p[i].arrivalTime <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        printf(" P%d |", p[idx].id);

        if (p[idx].remainingTime > timeQuantum) {
            time += timeQuantum;
            p[idx].remainingTime -= timeQuantum;
        } else {
            time += p[idx].remainingTime;
            p[idx].waitingTime = time - p[idx].arrivalTime - p[idx].burstTime;
            p[idx].turnaroundTime = time - p[idx].arrivalTime;
            p[idx].remainingTime = 0;
            p[idx].completed = 1;
            completed++;
        }

        // Enqueue new processes that arrived during execution
        for (i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrivalTime <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If not completed, re-add to end of queue
        if (!p[idx].completed)
            queue[rear++] = idx;
    }

    // Results
    printf("\n\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivalTime,
               p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime);
        avgWaiting += p[i].waitingTime;
        avgTurnaround += p[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time = %.2f", (float)avgWaiting / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)avgTurnaround / n);

    return 0;
}
