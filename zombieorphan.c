#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to create a Zombie process
void createZombieProcess() {
    pid_t pid = fork();  // Create a new process (fork)

    if (pid < 0) {  // Error handling for fork failure
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process (after fork)
        printf("Parent process: Zombie process created. PID = %d\n", pid); 
        sleep(10);  // Sleep for 10 seconds, allowing the child to exit first, creating a zombie process
    } 
    else {  // Child process
        printf("Child process exiting to become zombie.\n");
        exit(0);  // Exit child process; parent hasn't reaped it yet, so it becomes a zombie
    }
}

// Function to create an Orphan process
void createOrphanProcess() {
    pid_t pid = fork();  // Create a new process (fork)
    
    if (pid < 0) {  // Error handling for fork failure
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process (after fork)
        printf("Parent process exiting to create orphan process.\n");
        exit(0);  // Parent exits, making the child process an orphan
    } 
    else {  // Child process
        sleep(5);  // Sleep to allow the parent to exit first, making this process an orphan
        printf("Child process (orphan) continuing after parent termination. PID = %d\n", getpid());
    }
}

// Function to calculate sum of even and odd numbers
void sumEvenOdd(int arr[], int size) {
    pid_t pid = fork();  // Create a new process (fork)

    if (pid < 0) {  // Error handling for fork failure
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process (after fork)
        int evenSum = 0;
        // Sum even numbers in the array
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 == 0) {
                evenSum += arr[i];
            }
        }
        printf("Parent process: Sum of even numbers = %d\n", evenSum);
        wait(NULL);  // Wait for child process to finish
    } 
    else {  // Child process
        int oddSum = 0;
        // Sum odd numbers in the array
        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 != 0) {
                oddSum += arr[i];
            }
        }
        printf("Child process: Sum of odd numbers = %d\n", oddSum);
        exit(0);  // Exit child process after completing the task
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Array for the sum calculation
    int size = sizeof(arr) / sizeof(arr[0]);  // Calculate the size of the array

    printf("Calculating sum of even and odd numbers:\n");
    sumEvenOdd(arr, size);  // Call function to calculate sums of even and odd numbers

    printf("\nCreating a zombie process:\n");
    createZombieProcess();  // Call function to create a zombie process
    sleep(5);   // Sleep to allow the child process to be a zombie for a while

    printf("\nCreating an orphan process:\n");
    createOrphanProcess();  // Call function to create an orphan process

    return 0;  // Return 0 to indicate successful execution
}
