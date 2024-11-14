#include <stdio.h>

// Define a structure to hold process details
struct Process {
    int pid;            // Process ID (identifier for each process)
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time (execution time) of the process
    int finishTime;     // Finish time (when the process completes its execution)
    int turnAroundTime; // Turnaround time (total time from arrival to completion)
    int waitingTime;    // Waiting time (time spent waiting in the ready queue)
};

// Function to calculate the finish time, turnaround time, and waiting time for each process
void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;  // Variable to keep track of the current time during execution

    // Loop through each process and calculate the required times
    for (int i = 0; i < n; i++) {
        // If the process arrives after the current time, update the current time to the arrival time of the process
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Finish time is the current time plus the burst time (execution time of the process)
        processes[i].finishTime = currentTime + processes[i].burstTime;

        // Turnaround time is finish time minus arrival time (total time from arrival to completion)
        processes[i].turnAroundTime = processes[i].finishTime - processes[i].arrivalTime;

        // Waiting time is turnaround time minus burst time (how long the process was waiting in the queue)
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        // Update the current time to the finish time of the current process (the time when the process finishes execution)
        currentTime = processes[i].finishTime;
    }
}

// Function to display the results in a tabular format and calculate averages
void displayResults(struct Process processes[], int n) {
    // Print the table header for the output
    printf("PID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    
    // Loop through each process and print its details
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n",
               processes[i].pid,             // Process ID
               processes[i].arrivalTime,     // Arrival time
               processes[i].burstTime,       // Burst time
               processes[i].finishTime,      // Finish time
               processes[i].turnAroundTime,  // Turnaround time
               processes[i].waitingTime);    // Waiting time
    }

    // Calculate the total turnaround time and total waiting time
    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    // Calculate and print the average turnaround time and average waiting time
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n;  // Variable to store the number of processes

    // Ask the user to input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Declare an array to hold details for each process
    struct Process processes[n];

    // Loop through each process and accept the arrival time and burst time
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;  // Assign a unique PID starting from 1
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    // Sort the processes by their arrival time (this is necessary for FCFS scheduling)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // If the arrival time of the i-th process is greater than that of the j-th, swap them
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Call the function to calculate times (finish time, turnaround time, and waiting time)
    calculateTimes(processes, n);

    // Call the function to display the results (including averages)
    displayResults(processes, n);

    return 0;  // Return 0 to indicate successful program execution
}
