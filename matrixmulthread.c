#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 3  // Define the size of the matrices (3x3)
#define NUM_THREADS MAX * MAX  // Define the total number of threads needed (9 in this case)

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX]; // Matrices A and B for input, and C for any future operations
int D[MAX][MAX]; // Matrix D to store results of addition
int E[MAX][MAX]; // Matrix E to store results of multiplication

// Structure to pass row and column indices to threads
typedef struct {
    int row;
    int col;
} ThreadData;

// Function for matrix addition; each thread will handle a single element in D
void *matrix_addition(void *arg) {
    ThreadData *data = (ThreadData *)arg;  // Cast argument to ThreadData pointer
    int row = data->row;  // Row index for the element
    int col = data->col;  // Column index for the element

    D[row][col] = A[row][col] + B[row][col];  // Perform addition of corresponding elements

    pthread_exit(0);  // Exit thread
}

// Function for matrix multiplication; each thread handles a single element in E
void *matrix_multiplication(void *arg) {
    ThreadData *data = (ThreadData *)arg;  // Cast argument to ThreadData pointer
    int row = data->row;  // Row index for the element
    int col = data->col;  // Column index for the element

    E[row][col] = 0;  // Initialize element at E[row][col] to 0
    // Calculate the element by multiplying and summing rows and columns
    for (int k = 0; k < MAX; k++) {
        E[row][col] += A[row][k] * B[k][col];
    }

    pthread_exit(0);  // Exit thread
}

int main() {
    pthread_t threads[NUM_THREADS];  // Array to hold thread identifiers
    ThreadData thread_data[NUM_THREADS];  // Array to hold row and column data for each thread

    // Initialize matrices A and B with random values and print them
    printf("Matrix A:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10;  // Fill matrix A with random values (0-9)
            B[i][j] = rand() % 10;  // Fill matrix B with random values (0-9)
            printf("%d ", A[i][j]);  // Print matrix A
        }
        printf("\n");
    }

    printf("Matrix B:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", B[i][j]);  // Print matrix B
        }
        printf("\n");
    }

    // Create threads for matrix addition, one for each element in the result matrix D
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            thread_data[i * MAX + j].row = i;  // Assign row index for the thread
            thread_data[i * MAX + j].col = j;  // Assign column index for the thread
            // Create a thread to handle addition of the element at (i, j)
            pthread_create(&threads[i * MAX + j], NULL, matrix_addition, (void *)&thread_data[i * MAX + j]);
        }
    }

    // Wait for all addition threads to finish
    for (int i = 0; i < MAX * MAX; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display result of matrix addition
    printf("Result of Matrix Addition (D = A + B):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", D[i][j]);  // Print each element in matrix D
        }
        printf("\n");
    }

    // Create threads for matrix multiplication, one for each element in the result matrix E
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            thread_data[i * MAX + j].row = i;  // Assign row index for the thread
            thread_data[i * MAX + j].col = j;  // Assign column index for the thread
            // Create a thread to handle multiplication of the element at (i, j)
            pthread_create(&threads[i * MAX + j], NULL, matrix_multiplication, (void *)&thread_data[i * MAX + j]);
        }
    }

    // Wait for all multiplication threads to finish
    for (int i = 0; i < MAX * MAX; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display result of matrix multiplication
    printf("Result of Matrix Multiplication (E = A * B):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", E[i][j]);  // Print each element in matrix E
        }
        printf("\n");
    }

    return 0;  // End the program
}
