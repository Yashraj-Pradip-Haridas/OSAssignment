#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3  // Number of frames in memory

// Function to find the least recently used page
int findLRU(int frame[], int n, int pageAccess[], int current) {
    int i, j;
    int index = -1;
    int minDistance = -1;

    for (i = 0; i < n; i++) {
        // Find the page that is least recently used (appears farthest in the pageAccess sequence)
        int distance = -1;
        for (j = current - 1; j >= 0; j--) {
            if (pageAccess[j] == frame[i]) {
                distance = j;
                break;
            }
        }
        
        if (distance == -1) {
            return i;  // If the page has not appeared before, it is the least recently used
        }

        if (minDistance == -1 || distance < minDistance) {
            minDistance = distance;
            index = i;
        }
    }

    return index;
}

// Function to simulate LRU Page Replacement Algorithm
void LRU(int pageAccess[], int numPages) {
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

            // Find a frame to replace using the LRU strategy
            int indexToReplace = findLRU(frame, MAX_FRAMES, pageAccess, i);
            frame[indexToReplace] = page;  // Replace the LRU page with the new one
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

    // Run the LRU Page Replacement Algorithm
    LRU(pageAccess, numPages);

    return 0;
}
