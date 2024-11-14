#include <stdio.h>
#include <stdlib.h>

// Function to calculate disk scheduling using C-SCAN (Circular SCAN) algorithm
void calculateCSCAN(int requests[], int n, int initial_head, int disk_size, int direction) {
    int total_seek_time = 0;  // Total seek time to be accumulated
    int current_head = initial_head;  // Set the current head position to the initial head

    // Sort the requests array in ascending order for easier traversal
    for (int i = 0; i < n - 1; i++) {  // Outer loop for sorting
        for (int j = 0; j < n - i - 1; j++) {  // Inner loop for comparing adjacent elements
            if (requests[j] > requests[j + 1]) {  // If an element is greater than the next, swap
                int temp = requests[j];  // Temporary variable for swapping
                requests[j] = requests[j + 1];  // Swap the elements
                requests[j + 1] = temp;
            }
        }
    }

    // Find the starting index where the head should start servicing requests
    int start_index = 0;  // Initialize the starting index to 0
    while (start_index < n && requests[start_index] < initial_head) {  // Find the first request greater than or equal to initial_head
        start_index++;  // Move to the next index until we find the correct starting point
    }

    // Display the initial table headers
    printf("\nDisk Scheduling using C-SCAN Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");

    // Move in the selected direction (right or left)
    if (direction == 1) {  // Direction 1 means moving right (towards higher values)
        // Service requests to the right of the initial head position
        for (int i = start_index; i < n; i++) {  // Start servicing requests from the start_index
            int seek_time = abs(requests[i] - current_head);  // Calculate the seek time
            total_seek_time += seek_time;  // Add seek time to total seek time
            printf("|      %2d      |    %3d     |     %3d        |\n", i - start_index + 1, requests[i], seek_time);  // Print request info
            current_head = requests[i];  // Update the current head position
        }

        // Move to the end of the disk, if not already there, and then jump to the start (circular)
        if (current_head < disk_size - 1) {  // Check if we haven't reached the end of the disk
            int end_seek_time = abs(disk_size - 1 - current_head);  // Seek time to the end of the disk
            total_seek_time += end_seek_time;  // Add the end seek time
            printf("|      -       |   %3d     |     %3d        |\n", disk_size - 1, end_seek_time);  // Print the jump to the end
        }
        int reset_seek_time = disk_size - 1;  // Jump from end to the start (circular)
        total_seek_time += reset_seek_time;  // Add the reset seek time
        printf("|      -       |     0     |     %3d        |\n", reset_seek_time);  // Print the reset jump to the start
        current_head = 0;  // Move the head to the start

        // Continue servicing the remaining requests from the start
        for (int i = 0; i < start_index; i++) {  // Now service requests to the left of initial head
            int seek_time = abs(requests[i] - current_head);  // Calculate the seek time
            total_seek_time += seek_time;  // Add seek time to total seek time
            printf("|      %2d      |    %3d     |     %3d        |\n", i + n - start_index + 1, requests[i], seek_time);  // Print request info
            current_head = requests[i];  // Update the current head position
        }
    } else {  // Direction 0 means moving left (towards lower values)
        // Service requests to the left of the initial head position
        for (int i = start_index - 1; i >= 0; i--) {  // Start servicing requests from the left side
            int seek_time = abs(requests[i] - current_head);  // Calculate the seek time
            total_seek_time += seek_time;  // Add seek time to total seek time
            printf("|      %2d      |    %3d     |     %3d        |\n", start_index - i, requests[i], seek_time);  // Print request info
            current_head = requests[i];  // Update the current head position
        }

        // Move to the start of the disk and then jump to the end
        if (current_head > 0) {  // Check if we haven't already reached the start
            int start_seek_time = abs(current_head - 0);  // Seek time to the start of the disk
            total_seek_time += start_seek_time;  // Add the start seek time
            printf("|      -       |     0     |     %3d        |\n", start_seek_time);  // Print the jump to the start
        }
        int reset_seek_time = disk_size - 1;  // Jump from start to the end (circular)
        total_seek_time += reset_seek_time;  // Add the reset seek time
        printf("|      -       |   %3d     |     %3d        |\n", disk_size - 1, reset_seek_time);  // Print the reset jump to the end
        current_head = disk_size - 1;  // Move the head to the end

        // Continue servicing the remaining requests from the end
        for (int i = n - 1; i >= start_index; i--) {  // Now service requests to the right of initial head
            int seek_time = abs(requests[i] - current_head);  // Calculate the seek time
            total_seek_time += seek_time;  // Add seek time to total seek time
            printf("|      %2d      |    %3d     |     %3d        |\n", n - i, requests[i], seek_time);  // Print request info
            current_head = requests[i];  // Update the current head position
        }
    }

    // Print the total seek time after servicing all requests
    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time);  // Display the total seek time
}


int main() {
    int n, initial_head, disk_size, direction;

    // Accept number of requests and initial head position from the user
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];  // Create an array to store disk requests
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {  // Loop to accept disk requests from the user
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);  // Store each request
    }

    // Call the calculateCSCAN function to perform the C-SCAN disk scheduling
    calculateCSCAN(requests, n, initial_head, disk_size, direction);

    return 0;  // End the program
}



