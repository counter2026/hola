#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process with various attributes
struct Process {
    int pid;          // Process ID
    int arrivalTime;  // Arrival time of the process
    int burstTime;    // Burst time (CPU time required) of the process
    int remainingTime; // Remaining time for preemptive scheduling
    int priority;     // Priority of the process (lower value = higher priority)
    int finishTime;   // Time at which the process finishes execution
    int turnAroundTime; // Turnaround time of the process
    int waitingTime;  // Waiting time of the process
    bool isCompleted; // Completion status of the process
};

// Function for Non-Preemptive Priority Scheduling
void priorityNonPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int minIndex = -1;
        int highestPriority = 1e9; // Start with a high priority for comparison

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime &&
                processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                minIndex = i;
            }
        }

        // If no process has arrived, increment the current time
        if (minIndex == -1) {
            currentTime++;
        } else {
            // Calculate the process metrics (finish, turnaround, waiting times)
            processes[minIndex].finishTime = currentTime + processes[minIndex].burstTime;
            processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
            processes[minIndex].isCompleted = true;

            // Update the current time to the finish time of the completed process
            currentTime = processes[minIndex].finishTime;
            completed++;  // Increase the count of completed processes
        }
    }
}

// Function for Preemptive Priority Scheduling
void priorityPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int minIndex = -1;
        int highestPriority = 1e9; // Start with a high priority for comparison

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted &&
                processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                minIndex = i;
            }
        }

        // If a valid process was found
        if (minIndex != -1) {
            // Execute one unit of the burst time
            processes[minIndex].remainingTime--;
            currentTime++;

            // If the process is completed, calculate its metrics
            if (processes[minIndex].remainingTime == 0) {
                processes[minIndex].finishTime = currentTime;
                processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
                processes[minIndex].isCompleted = true;
                completed++;  // Increase the count of completed processes
            }
        } else {
            currentTime++;  // If no process is available, increment time
        }
    }
}

// Function to display the results of scheduling
void displayResults(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tPriority\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].finishTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }

    // Calculate average turnaround and waiting times
    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n, choice;

    // Get the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Gather information for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", processes[i].pid);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;  // Initialize remaining time
        processes[i].isCompleted = false;  // Initially mark each process as incomplete
    }

    // Prompt user to choose between non-preemptive and preemptive priority scheduling
    printf("Choose Scheduling:\n1. Non-Preemptive Priority\n2. Preemptive Priority\n");
    scanf("%d", &choice);

    // Run the selected scheduling algorithm
    if (choice == 1) {
        priorityNonPreemptive(processes, n);
    } else if (choice == 2) {
        priorityPreemptive(processes, n);
    } else {
        printf("Invalid choice!\n");
        return 0;
    }

    // Display the results
    displayResults(processes, n);
    return 0;
}
