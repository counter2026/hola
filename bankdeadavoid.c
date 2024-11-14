#include <stdio.h>
#include <stdbool.h>


#define MAX_PROCESSES 10  // Maximum number of processes
#define MAX_RESOURCES 10  // Maximum number of resources


int processes, resources;  // Number of processes and resources
int available[MAX_RESOURCES];  // Array to store available resources
int max[MAX_PROCESSES][MAX_RESOURCES];  // Matrix to store the maximum resources required by each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Matrix to store the currently allocated resources to each process
int need[MAX_PROCESSES][MAX_RESOURCES];  // Matrix to store the remaining resources required by each process


// Function to calculate the need matrix: Need = Max - Allocation
void calculateNeed() {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];  // Calculate need for each process and resource
        }
    }
}


// Function to check if the system is in a safe state
bool isSafeState() {
    int work[MAX_RESOURCES];  // Temporary array to store available resources during the safety check
    bool finish[MAX_PROCESSES] = {false};  // Array to track if a process has finished
    int safeSequence[MAX_PROCESSES];  // Array to store the safe sequence of processes
    int count = 0;  // Counter for the number of processes that are safely finished


    // Initialize work as a copy of available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];  // Copy available resources to work
    }


    // While there are unfinished processes
    while (count < processes) {
        bool found = false;  // Flag to check if any process can be allocated resources


        // Check each process to see if it can be allocated resources
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {  // If process i is not finished
                bool canAllocate = true;  // Flag to check if all resources can be allocated to process i


                // Check if process i needs more resources than currently available
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {  // If process i needs more resources than available
                        canAllocate = false;  // It cannot be allocated
                        break;  // No need to check further
                    }
                }


                // If process i can be allocated resources
                if (canAllocate) {
                    // Allocate resources by updating work
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];  // Add allocated resources to work
                    }
                    safeSequence[count++] = i;  // Add process i to the safe sequence
                    finish[i] = true;  // Mark process i as finished
                    found = true;  // Mark that a process was found to be safely finished
                }
            }
        }


        // If no process can be allocated resources, the system is not in a safe state
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;  // Return false indicating that the system is not in a safe state
        }
    }


    // If all processes are finished, print the safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSequence[i]);  // Print the safe sequence of processes
    }
    printf("\n");
    return true;  // Return true indicating that the system is in a safe state
}


int main() {
    // Take input for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &processes);


    // Take input for the number of resources
    printf("Enter the number of resources: ");
    scanf("%d", &resources);


    // Take input for the available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);  // Input available resources for each resource type
    }


    // Take input for the maximum resource matrix
    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);  // Input the maximum resources each process can request
        }
    }


    // Take input for the allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);  // Input the currently allocated resources for each process
        }
    }


    // Calculate the need matrix
    calculateNeed();


    // Check if the system is in a safe state
    isSafeState();


    return 0;  // Return 0 to indicate successful execution
}
