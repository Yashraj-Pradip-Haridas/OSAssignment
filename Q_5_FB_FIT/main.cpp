#include <stdio.h>
#define MAX 100

// Function to perform First Fit
void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1; // -1 means not allocated
    }

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // reduce available size
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Function to perform Best Fit
void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX], processSize[MAX];
    int blocks, processes;

    // Input
    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter size of each memory block:\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter size of each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // First Fit
    int firstFitBlocks[MAX];
    for (int i = 0; i < blocks; i++) {
        firstFitBlocks[i] = blockSize[i]; // make a copy
    }
    firstFit(firstFitBlocks, blocks, processSize, processes);

    // Best Fit
    int bestFitBlocks[MAX];
    for (int i = 0; i < blocks; i++) {
        bestFitBlocks[i] = blockSize[i]; // make a copy
    }
    bestFit(bestFitBlocks, blocks, processSize, processes);

    return 0;
}
