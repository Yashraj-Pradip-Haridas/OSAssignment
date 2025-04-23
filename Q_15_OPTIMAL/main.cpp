#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3  // Number of frames in memory

// Function to find the page that will not be used for the longest time in the future
int findOptimal(int frame[], int n, int pageAccess[], int current, int numPages) {
    int i, j;
    int farthest = -1;
    int indexToReplace = -1;

    // For each page in memory, find when it will be used next, and replace the one with the farthest usage
    for (i = 0; i < n; i++) {
        int nextUse = -1;
        for (j = current + 1; j < numPages; j++) {
            if (frame[i] == pageAccess[j]) {
                nextUse = j;
                break;
            }
        }

        // If the page is not used in the future, it will be replaced
        if (nextUse == -1) {
            return i;
        }

        // If this page will be used later, track the page that is used the farthest in the future
        if (nextUse > farthest) {
            farthest = nextUse;
            indexToReplace = i;
        }
    }

    return indexToReplace;
}

// Function to simulate Optimal Page Replacement Algorithm
void Optimal(int pageAccess[], int numPages) {
    int frame[MAX_FRAMES];  // Array to store pages in memory
    int pageFaults = 0;      // Counter for page faults
    int i, j;

    // Initialize frames with -1 (empty)
    for (i = 0; i < MAX_FRAMES; i++) {
        frame[i] = -1;
    }

    // Simulate the page access
    for (i = 0; i < numPages; i++) {
        int page = pageAccess[i];
        int pageFound = 0;

        // Check if the page is already in one of the frames
        for (j = 0; j < MAX_FRAMES; j++) {
            if (frame[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            // Page fault, we need to add the page to memory
            pageFaults++;

            // If there is space, add the page to an empty frame
            int emptyFrame = -1;
            for (j = 0; j < MAX_FRAMES; j++) {
                if (frame[j] == -1) {
                    emptyFrame = j;
                    break;
                }
            }

            // If there is no empty frame, replace the page that will not be used for the longest time
            if (emptyFrame == -1) {
                int indexToReplace = findOptimal(frame, MAX_FRAMES, pageAccess, i, numPages);
                frame[indexToReplace] = page;
            } else {
                frame[emptyFrame] = page;
            }
        }

        // Display the frames after each page access
        printf("Page %d accessed: ", page);
        for (j = 0; j < MAX_FRAMES; j++) {
            if (frame[j] == -1) {
                printf(" - ");
            } else {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }

    // Display the total number of page faults
    printf("\nTotal page faults: %d\n", pageFaults);
}

int main() {
    int pageAccess[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 3};  // Example page access sequence
    int numPages = sizeof(pageAccess) / sizeof(pageAccess[0]);

    printf("Page Access Sequence: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pageAccess[i]);
    }
    printf("\n\n");

    // Run the Optimal Page Replacement Algorithm
    Optimal(pageAccess, numPages);

    return 0;
}
