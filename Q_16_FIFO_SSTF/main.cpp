#include <stdio.h>
#include <stdlib.h>

// Function to calculate the total seek time for FIFO scheduling
void FIFO(int requests[], int n, int start) {
    int seekCount = 0;
    int currentTrack = start;

    printf("\nFIFO Disk Scheduling\n");
    printf("Disk Requests: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // Process each request in order
    for (int i = 0; i < n; i++) {
        seekCount += abs(requests[i] - currentTrack);  // Calculate seek time
        currentTrack = requests[i];  // Move the head to the requested track
    }

    printf("Total Seek Time: %d\n", seekCount);
}

// Function to calculate the total seek time for SSTF scheduling
void SSTF(int requests[], int n, int start) {
    int seekCount = 0;
    int currentTrack = start;
    int completed[n];  // Array to track completed requests

    // Initialize completed array to 0 (not completed)
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    printf("\nSSTF Disk Scheduling\n");
    printf("Disk Requests: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // Process each request by selecting the closest track
    for (int i = 0; i < n; i++) {
        int closest = -1;
        int minSeek = 999999;

        // Find the closest unprocessed request
        for (int j = 0; j < n; j++) {
            if (!completed[j] && abs(requests[j] - currentTrack) < minSeek) {
                minSeek = abs(requests[j] - currentTrack);
                closest = j;
            }
        }

        // Update seek count and current track
        seekCount += minSeek;
        currentTrack = requests[closest];
        completed[closest] = 1;  // Mark the request as completed
    }

    printf("Total Seek Time: %d\n", seekCount);
}

int main() {
    int requests[] = {176, 79, 34, 60, 92, 11, 41, 114};  // Disk request queue
    int n = sizeof(requests) / sizeof(requests[0]);
    int start = 50;  // Initial head position

    // Call FIFO Disk Scheduling
    FIFO(requests, n, start);

    // Call SSTF Disk Scheduling
    SSTF(requests, n, start);

    return 0;
}
