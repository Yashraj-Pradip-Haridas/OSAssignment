#include <stdio.h>
#define MAX 100

// Function to perform Next Fit
void nextFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];
    int lastPos = 0; // To keep track of where we left off

    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
        int count = 0; // to prevent infinite loop
        int j = lastPos;

        while (count < blocks) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastPos = j; // update position
                break;
            }
            j = (j + 1) % blocks;
            count++;
        }
    }

    printf("\nNext Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Function to perform Worst Fit
void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX];

    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
        int worstIdx = -1;

        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
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

    // Next Fit
    int nextFitBlocks[MAX];
    for (int i = 0; i < blocks; i++) {
        nextFitBlocks[i] = blockSize[i]; // make a copy
    }
    nextFit(nextFitBlocks, blocks, processSize, processes);

    // Worst Fit
    int worstFitBlocks[MAX];
    for (int i = 0; i < blocks; i++) {
        worstFitBlocks[i] = blockSize[i]; // make a copy
    }
    worstFit(worstFitBlocks, blocks, processSize, processes);

    return 0;
}
