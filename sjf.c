#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid;                // Process ID
    int arrivalTime;        // Time when the process arrives
    int burstTime;          // Total execution time required by the process
    int remainingTime;      // Remaining time for preemptive SJF (used for preemption)
    int finishTime;         // Time when the process finishes execution
    int turnAroundTime;     // Turnaround time = Finish time - Arrival time
    int waitingTime;        // Waiting time = Turnaround time - Burst time
    bool isCompleted;       // Flag to check if the process is completed
};

// Function to implement Non-Preemptive SJF (Shortest Job First) Scheduling
void sjfNonPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;

    // Loop to schedule and process all the tasks
    while (completed < n) {
        int minIndex = -1;
        int minBurstTime = 1e9;  // Start with a large number for comparison

        // Search for the process with the smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime &&
                processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime; // Update the smallest burst time
                minIndex = i;  // Mark the process as the one to execute next
            }
        }

        // If no process has arrived yet, increment current time
        if (minIndex == -1) {
            currentTime++;
        } else {
            // Calculate finish time, turnaround time, and waiting time for the process
            processes[minIndex].finishTime = currentTime + processes[minIndex].burstTime;
            processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
            processes[minIndex].isCompleted = true;  // Mark this process as completed

            // Move current time forward based on the process execution
            currentTime = processes[minIndex].finishTime;
            completed++;  // Increase the count of completed processes
        }
    }
}

// Function to implement Preemptive SJF (Shortest Job First) Scheduling
void sjfPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;
    int minIndex = -1;
    int minRemainingTime = 1e9;  // Start with a large number for comparison

    // Loop until all processes are completed
    while (completed < n) {
        minIndex = -1;
        minRemainingTime = 1e9;

        // Search for the process with the smallest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted &&
                processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;  // Update the process with the least remaining time
                minIndex = i;  // Mark it as the next process to execute
            }
        }

        // If a process is found, reduce its remaining time and check if it's completed
        if (minIndex != -1) {
            processes[minIndex].remainingTime--;  // Decrement the remaining time
            currentTime++;  // Increment the current time

            // If the process is completed (remaining time becomes zero)
            if (processes[minIndex].remainingTime == 0) {
                processes[minIndex].finishTime = currentTime;
                processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
                processes[minIndex].isCompleted = true;  // Mark process as completed
                completed++;  // Increase the completed process count
            }
        } else {
            currentTime++;  // If no process is ready to run, just increment the current time
        }
    }
}

// Function to display the results of the scheduling
void displayResults(struct Process processes[], int n) {
    // Print the header of the table
    printf("PID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");

    // Loop to display each process's details
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].finishTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }

    // Calculate and print average turnaround and waiting times
    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    // Display average times
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}

// Main function to drive the program
int main() {
    int n, choice;

    // Accept number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Declare an array to store processes
    struct Process processes[n];

    // Accept process details (arrival time and burst time) for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;  // Assign PID starting from 1
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;  // Initialize remaining time to burst time
        processes[i].isCompleted = false;  // Set process status as not completed
    }

    // Provide the user with scheduling algorithm options
    printf("Choose Scheduling:\n1. Non-Preemptive SJF\n2. Preemptive SJF\n");
    scanf("%d", &choice);

    // Execute the selected scheduling algorithm
    if (choice == 1) {
        sjfNonPreemptive(processes, n);
    } else if (choice == 2) {
        sjfPreemptive(processes, n);
    } else {
        printf("Invalid choice!\n");
        return 0;  // Exit if invalid choice is entered
    }

    // Display the results after scheduling is completed
    displayResults(processes, n);

    return 0;  // Return 0 to indicate successful execution
}

/*
Sample Input:
3
0 6
2 8
4 7
*/
