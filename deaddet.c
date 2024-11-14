#include <stdio.h>
#include <stdbool.h>


#define MAX_PROCESSES 10  // Maximum number of processes
#define MAX_RESOURCES 10  // Maximum number of resources


int processes, resources;  // Number of processes and resources
int available[MAX_RESOURCES];  // Array to store the available resources
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Matrix to store the allocation of resources for each process
int request[MAX_PROCESSES][MAX_RESOURCES];  // Matrix to store the resource requests for each process


// Function to perform deadlock detection
void deadlockDetection() {
    bool finish[MAX_PROCESSES] = {false};  // Array to mark which processes have finished (no deadlock)
    int work[MAX_RESOURCES];  // Temporary array to simulate the available resources


    // Initialize work as a copy of available resources (work will keep track of available resources)
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }


    bool deadlock = false;  // Flag to indicate if there's a deadlock
    int deadlockedProcesses[MAX_PROCESSES];  // Array to store the processes involved in the deadlock
    int deadlockedCount = 0;  // Counter for the deadlocked processes


    // Try to find a process that can finish (request can be fulfilled)
    for (int count = 0; count < processes; count++) {  // Loop for the total number of processes
        bool found = false;  // Flag to indicate if a process is found to proceed


        for (int i = 0; i < processes; i++) {  // Check each process
            if (!finish[i]) {  // Process hasn't finished yet
                bool canProceed = true;  // Assume this process can proceed


                // Check if the request can be satisfied with available resources
                for (int j = 0; j < resources; j++) {  // Check each resource type
                    if (request[i][j] > work[j]) {  // If the request is greater than available resources
                        canProceed = false;  // Cannot proceed with this process
                        break;  // Break out of the loop if request can't be fulfilled
                    }
                }


                // If the request can be satisfied, allocate resources temporarily
                if (canProceed) {
                    for (int j = 0; j < resources; j++) {  // Allocate the resources
                        work[j] += allocation[i][j];  // Add allocated resources back to work
                    }
                    finish[i] = true;  // Mark the process as finished
                    found = true;  // A process is found to proceed
                }
            }
        }


        // If no process could proceed in this round, break out of the loop
        if (!found) {
            break;
        }
    }


    // After trying to process all, check for any unfinished processes (deadlocked)
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {  // If a process is not finished, it is deadlocked
            deadlockedProcesses[deadlockedCount++] = i;  // Add this process to the deadlock list
            deadlock = true;  // Mark deadlock as true
        }
    }


    // Output the result based on the deadlock status
    if (deadlock) {
        printf("System is in a deadlock state.\n");
        printf("Deadlocked processes: ");
        for (int i = 0; i < deadlockedCount; i++) {
            printf("P%d ", deadlockedProcesses[i]);  // Print the deadlocked processes
        }
        printf("\n");
    } else {
        printf("System is not in a deadlock state.\n");  // If no deadlock, print system is safe
    }
}


int main() {
    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Input the available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);  // Store available resources
    }

    // Input the allocation matrix (resources allocated to processes)
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);  // Store resource allocation for each process
        }
    }

    // Input the request matrix (resources requested by processes)
    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &request[i][j]);  // Store resource requests for each process
        }
    }

    // Perform deadlock detection
    deadlockDetection();

    return 0;  // End the program
}
