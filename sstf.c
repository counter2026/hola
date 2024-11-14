#include <stdio.h>
#include <stdlib.h>

// Function to calculate and display the SSTF (Shortest Seek Time First) disk scheduling
void calculateSSTF(int requests[], int n, int initial_head) {
    int total_seek_time = 0;  // Variable to track the total seek time
    int current_head = initial_head;  // Start with the initial head position
    int visited[n];  // Array to keep track of which requests have been visited
    int i, count = 0;  // Loop counters

    // Initialize the visited array to mark all requests as unvisited
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("\nDisk Scheduling using SSTF Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");

    // Continue the loop until all requests have been processed
    while (count < n) {
        int min_seek_time = 10000; // Arbitrary large value to find the minimum seek time
        int min_index = -1;  // Index of the closest request

        // Loop through all requests to find the one with the shortest seek time
        for (i = 0; i < n; i++) {
            if (!visited[i]) {  // If the request hasn't been visited yet
                int seek_time = abs(requests[i] - current_head);  // Calculate seek time
                if (seek_time < min_seek_time) {  // Find the request with the shortest seek time
                    min_seek_time = seek_time;
                    min_index = i;
                }
            }
        }

        // Process the closest request
        if (min_index != -1) {
            total_seek_time += min_seek_time;  // Add the seek time to the total
            printf("|      %2d      |    %3d     |     %3d        |\n", count + 1, requests[min_index], min_seek_time);
            current_head = requests[min_index];  // Move the head to the current request
            visited[min_index] = 1;  // Mark this request as visited
            count++;  // Increment the request count
        }
    }

    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time);  // Display the total seek time
}

int main() {
    int n;  // Number of disk requests
    int initial_head;  // The initial position of the disk head

    // Accept the number of disk requests from the user
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];  // Array to store the disk requests

    // Accept the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    // Accept the disk requests from the user
    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Calculate and display the SSTF scheduling result
    calculateSSTF(requests, n, initial_head);

    return 0;  // Return 0 to indicate successful program execution
}

/*
Sample Input:
7
50
82
170   
43
140
24
16
190
*/
