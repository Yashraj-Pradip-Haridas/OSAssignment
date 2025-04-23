#include <stdio.h>
#include <stdlib.h>

// Function to calculate total seek time for SCAN Disk Scheduling
void SCAN(int requests[], int n, int start, int diskSize) {
    int seekCount = 0;
    int currentTrack = start;
    int direction = 1;  // 1 means moving right, -1 means moving left

    // Sort the requests to optimize movement
    int sortedRequests[n];
    for (int i = 0; i < n; i++) {
        sortedRequests[i] = requests[i];
    }

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sortedRequests[i] > sortedRequests[j]) {
                int temp = sortedRequests[i];
                sortedRequests[i] = sortedRequests[j];
                sortedRequests[j] = temp;
            }
        }
    }

    printf("\nSCAN Disk Scheduling\n");
    printf("Disk Requests: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // Start moving in the direction of the initial head position
    int i = 0;
    while (i < n && sortedRequests[i] < start) {
        i++;
    }

    // Service all requests in the direction of movement
    for (int j = i - 1; j >= 0 && direction == -1; j--) {
        seekCount += abs(sortedRequests[j] - currentTrack);
        currentTrack = sortedRequests[j];
    }

    for (int j = i; j < n && direction == 1; j++) {
        seekCount += abs(sortedRequests[j] - currentTrack);
        currentTrack = sortedRequests[j];
    }

    printf("Total Seek Time: %d\n", seekCount);
}

// Function to calculate total seek time for C-SCAN Disk Scheduling
void CSCAN(int requests[], int n, int start, int diskSize) {
    int seekCount = 0;
    int currentTrack = start;

    // Sort the requests to optimize movement
    int sortedRequests[n];
    for (int i = 0; i < n; i++) {
        sortedRequests[i] = requests[i];
    }

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sortedRequests[i] > sortedRequests[j]) {
                int temp = sortedRequests[i];
                sortedRequests[i] = sortedRequests[j];
                sortedRequests[j] = temp;
            }
        }
    }

    printf("\nC-SCAN Disk Scheduling\n");
    printf("Disk Requests: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // Service requests in the direction of movement (from start to the right)
    int i = 0;
    while (i < n && sortedRequests[i] < start) {
        i++;
    }

    // First, move to the right end (diskSize-1) and service requests
    for (int j = i; j < n; j++) {
        seekCount += abs(sortedRequests[j] - currentTrack);
        currentTrack = sortedRequests[j];
    }

    // After reaching the right end, move to the beginning (disk 0)
    seekCount += abs(diskSize - 1 - currentTrack);
    currentTrack = 0;

    // Now service the requests from the beginning (disk 0) to the original starting position
    for (int j = 0; j < i; j++) {
        seekCount += abs(sortedRequests[j] - currentTrack);
        currentTrack = sortedRequests[j];
    }

    printf("Total Seek Time: %d\n", seekCount);
}

int main() {
    int requests[] = {176, 79, 34, 60, 92, 11, 41, 114};  // Disk request queue
    int n = sizeof(requests) / sizeof(requests[0]);
    int start = 50;  // Initial head position
    int diskSize = 200;  // Size of the disk

    // Call SCAN Disk Scheduling
    SCAN(requests, n, start, diskSize);

    // Call C-SCAN Disk Scheduling
    CSCAN(requests, n, start, diskSize);

    return 0;
}
