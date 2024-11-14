#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// Function prototypes to define functions later
void process_related_calls();
void file_related_calls();
void communication_related_calls();
void information_related_calls();

int main() {
    int choice;

    // Main loop showing the menu for the system call demonstration
    while (1) {
        // Display menu options
        printf("\nMenu Driven System Call Demonstration\n");
        printf("1. Process Related System Calls\n");
        printf("2. File Related System Calls\n");
        printf("3. Communication Related System Calls\n");
        printf("4. Information Related System Calls\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform action based on user input
        switch (choice) {
            case 1:
                process_related_calls(); // Call function for process-related system calls
                break;
            case 2:
                file_related_calls(); // Call function for file-related system calls
                break;
            case 3:
                communication_related_calls(); // Call function for communication-related system calls
                break;
            case 4:
                information_related_calls(); // Call function for information-related system calls
                break;
            case 5:
                exit(0); // Exit the program
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

// Function for process-related system calls
void process_related_calls() {
    pid_t pid; // Declare variable to store process ID
    int status; // Declare variable to store child process status

    printf("\nProcess Related System Calls\n");

    pid = fork(); // Create a new process (fork system call)
    if (pid < 0) {
        perror("Fork failed"); // Handle error if fork fails
        exit(1);
    } else if (pid == 0) { // Child process
        printf("Child Process ID: %d\n", getpid()); // Get the child process ID
        execlp("/bin/ls", "ls", NULL); // Execute the "ls" command using exec system call
        exit(0); // Exit child process
    } else { // Parent process
        printf("Parent Process ID: %d\n", getpid()); // Get the parent process ID
        wait(&status); // Wait for the child process to finish (wait system call)
        printf("Child process completed with status: %d\n", status); // Print status of the child process
    }
}

// Function for file-related system calls
void file_related_calls() {
    int fd; // Declare file descriptor variable
    char buffer[100]; // Declare a buffer to hold data read from the file
    ssize_t bytes_read; // Variable to store the number of bytes read

    printf("\nFile Related System Calls\n");

    // Open a file "testfile.txt", create it if it doesn't exist, with read-write permissions
    fd = open("testfile.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Open failed"); // Handle error if opening file fails
        return;
    }

    // Write "Hello, World!" into the file
    write(fd, "Hello, World!\n", 14); 

    // Reposition the file offset to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Read data from the file into the buffer
    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the string
        printf("Read from file: %s", buffer); // Print the content read from the file
    }

    close(fd); // Close the file (close system call)
    unlink("testfile.txt"); // Delete the file (unlink system call)
}

// Function for communication-related system calls
void communication_related_calls() {
    int fd[2]; // Array to hold pipe file descriptors
    pid_t pid; // Declare process ID variable
    char write_msg[] = "Hello from parent!\n"; // Message to be written to the pipe
    char read_msg[100]; // Buffer to hold the message read from the pipe

    printf("\nCommunication Related System Calls\n");

    // Create a pipe (pipe system call)
    if (pipe(fd) == -1) {
        perror("Pipe failed"); // Handle error if pipe creation fails
        return;
    }

    pid = fork(); // Create a new process using fork
    if (pid < 0) {
        perror("Fork failed"); // Handle error if fork fails
        exit(1);
    } else if (pid == 0) { // Child process
        close(fd[1]); // Close the write end of the pipe in the child process
        read(fd[0], read_msg, sizeof(read_msg)); // Read the message from the pipe
        printf("Child received: %s", read_msg); // Print the received message
        close(fd[0]); // Close the read end of the pipe
    } else { // Parent process
        close(fd[0]); // Close the read end of the pipe in the parent process
        write(fd[1], write_msg, strlen(write_msg)); // Write the message to the pipe
        close(fd[1]); // Close the write end of the pipe
        wait(NULL); // Wait for the child process to finish
    }
}

// Function for information-related system calls
void information_related_calls() {
    printf("\nInformation Related System Calls\n");

    printf("Sleeping for 2 seconds...\n");
    sleep(2); // Sleep for 2 seconds (sleep system call)

    printf("Setting an alarm for 3 seconds...\n");
    alarm(3); // Set an alarm to go off after 3 seconds (alarm system call)

    printf("You will see this message before the alarm goes off.\n");

    // Delay for 4 seconds to let the alarm go off before program ends
    sleep(4);
}
