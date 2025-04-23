#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3  // Number of frames in memory

// Function to simulate FCFS Page Replacement Algorithm
void FCFS(int pageAccess[], int numPages) {
    int frame[MAX_FRAMES];  // Array to store pages in memory
    int pageFaults = 0;      // Counter for page faults
    int i, j, oldest = 0;

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

            // If memory is full, replace the oldest page (First-Come-First-Served)
            frame[oldest] = page;
            oldest = (oldest + 1) % MAX_FRAMES;  // Update the "oldest" pointer (circularly)
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

    // Run the FCFS Page Replacement Algorithm
    FCFS(pageAccess, numPages);

    return 0;
}
