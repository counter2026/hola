#include <stdio.h>

// Define a structure to represent each process
struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time of the process
    int burstTime;     // Burst time (CPU time required)
    int remainingTime; // Remaining burst time for the process
    int finishTime;    // Finish time (when the process completes)
    int turnAroundTime; // Turnaround time (finish time - arrival time)
    int waitingTime;   // Waiting time (turnaround time - burst time)
};

// Function to implement Round Robin scheduling
void roundRobin(struct Process processes[], int n, int quantum) {
    int currentTime = 0; // Track the current time (time elapsed)
    int completed = 0;   // Track the number of processes that have completed
    int timeQuantum = quantum; // Time quantum for each process

    // Run the Round Robin scheduling until all processes are completed
    while (completed < n) {
        int done = 1; // Flag to check if all processes are done

        // Iterate through all processes to simulate Round Robin execution
        for (int i = 0; i < n; i++) {
            // Check if process has remaining time and has arrived
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime) {
                done = 0; // Mark that at least one process is running

                // If remaining time of process is less than or equal to time quantum, the process will finish
                if (processes[i].remainingTime <= timeQuantum) {
                    currentTime += processes[i].remainingTime; // Increment current time by process's remaining time
                    processes[i].finishTime = currentTime;    // Set finish time of the process
                    processes[i].turnAroundTime = processes[i].finishTime - processes[i].arrivalTime; // Turnaround time
                    processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime; // Waiting time
                    processes[i].remainingTime = 0; // Process is completed
                    completed++; // Increment completed processes counter
                } else {
                    // Process runs for the full time quantum
                    processes[i].remainingTime -= timeQuantum; // Decrease remaining time by time quantum
                    currentTime += timeQuantum; // Increment the current time by the quantum
                }
            }
        }

        // If no process is executed in the current cycle, increment the current time by 1
        if (done) {
            currentTime++;
        }
    }
}

// Function to display the results of the Round Robin scheduling
void displayResults(struct Process processes[], int n) {
    // Print the header for the results table
    printf("PID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    
    // Print the details for each process
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", // Print each process's ID, arrival time, burst time, etc.
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].finishTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }

    // Calculate average turnaround time and average waiting time
    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime; // Sum of turnaround times
        totalWaitingTime += processes[i].waitingTime; // Sum of waiting times
    }

    // Print the average turnaround time and waiting time
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}

// Main function to execute the program
int main() {
    int n, quantum; // Variables to store number of processes and time quantum

    // Input: Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n); // Get the number of processes from user

    // Declare an array of Process structures
    struct Process processes[n];

    // Input: Arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Assign process ID starting from 1
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Set initial remaining time to burst time
    }

    // Input: Time quantum for Round Robin scheduling
    printf("Enter the time quantum: ");
    scanf("%d", &quantum); // Get the time quantum from user

    // Call the Round Robin function to schedule the processes
    roundRobin(processes, n, quantum);

    // Call the function to display the results (turnaround time, waiting time, etc.)
    displayResults(processes, n);

    return 0;
}

/*
Test Input:
4
0 5
1 4
2 2
4 1
2
*/
