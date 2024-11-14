#include <stdio.h>
#include <stdlib.h>

// Function to calculate the FCFS disk scheduling
void calculateFCFS(int requests[], int n, int initial_head) {
    int total_seek_time = 0;  // Variable to store the total seek time
    int current_head = initial_head;  // Variable to store the current position of the disk head, initially set to the given initial head

    // Print the table header for the FCFS disk scheduling output
    printf("\nDisk Scheduling using FCFS Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");
   
    // Loop through each request and calculate the seek time for each
    for (int i = 0; i < n; i++) {
        // Calculate the seek time by taking the absolute difference between the current head position and the requested position
        int seek_time = abs(requests[i] - current_head);

        // Add the seek time of the current request to the total seek time
        total_seek_time += seek_time;

        // Print the details for the current request (Request number, Requested position, and Seek time)
        printf("|      %2d      |    %3d     |     %3d        |\n", i + 1, requests[i], seek_time);

        // After serving the current request, update the current head to the position of the served request
        current_head = requests[i];
    }

    // Print the total seek time after serving all requests
    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time);
}

int main() {
    int n;  // Variable to store the number of disk requests
    int initial_head;  // Variable to store the initial position of the disk head

    // Accept the number of disk requests from the user
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    // Declare an array to store the disk requests
    int requests[n];

    // Accept the initial position of the disk head from the user
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    // Accept the disk requests from the user
    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);  // Prompt for each disk request
        scanf("%d", &requests[i]);  // Store each disk request in the array
    }

    // Call the function to calculate and display the FCFS scheduling with the entered requests and initial head position
    calculateFCFS(requests, n, initial_head);

    return 0;  // Return 0 to indicate successful program execution
}
