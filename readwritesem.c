#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5 // Number of reader threads
#define WRITERS 2 // Number of writer threads

// Shared resource
int shared_resource = 0; // This is the shared resource being read and written by readers and writers

// Semaphores
sem_t mutex;   // Semaphore for mutual exclusion to protect read_count
sem_t wrt;     // Semaphore for controlling writer access to the shared resource
int read_count = 0; // Number of active readers

// Reader function - Simulates reading the shared resource
void *reader(void *arg) {
    int reader_id = *((int *)arg); // Get the ID of the reader thread
    
    while (1) {
        // Wait for mutex to safely update read_count (number of readers)
        sem_wait(&mutex);
        read_count++; // Increment read_count as a new reader is starting to read

        // If this is the first reader, it should block writers (by acquiring wrt semaphore)
        if (read_count == 1) {
            sem_wait(&wrt); // First reader blocks writers to prevent write access
        }
        sem_post(&mutex); // Release mutex so other readers can proceed

        // Critical Section - Reading the shared resource
        printf("Reader %d is reading: %d\n", reader_id, shared_resource);
        sleep(1); // Simulate reading time

        // Decrease the read_count as this reader finishes
        sem_wait(&mutex);
        read_count--; // One less reader
        // If this is the last reader, release the wrt semaphore, allowing writers
        if (read_count == 0) {
            sem_post(&wrt); // Last reader allows writers to access the resource
        }
        sem_post(&mutex); // Release mutex after updating read_count

        sleep(rand() % 3); // Simulate thinking time before the next read
    }
    return NULL;
}

// Writer function - Simulates writing to the shared resource
void *writer(void *arg) {
    int writer_id = *((int *)arg); // Get the ID of the writer thread

    while (1) {
        // Wait for wrt semaphore to get exclusive access for writing
        sem_wait(&wrt); // Writer blocks other writers and readers

        // Critical Section - Writing to the shared resource
        shared_resource++; // Increment the shared resource as part of writing
        printf("Writer %d is writing: %d\n", writer_id, shared_resource);
        sleep(5); // Simulate writing time

        // After writing, release the wrt semaphore, allowing others to access the resource
        sem_post(&wrt); // Writer finishes, other writers or readers can proceed

        sleep(rand() % 3); // Simulate thinking time before the next write
    }
    return NULL;
}

int main() {
    pthread_t readers[READERS], writers[WRITERS]; // Arrays to hold reader and writer threads
    int reader_ids[READERS], writer_ids[WRITERS]; // Arrays to hold reader and writer IDs

    // Initialize semaphores
    sem_init(&mutex, 0, 1); // Binary semaphore for mutual exclusion (protecting read_count)
    sem_init(&wrt, 0, 1);   // Binary semaphore for writers to get exclusive access to the shared resource

    // Create reader threads
    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i + 1; // Assign IDs to readers (starting from 1)
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]); // Create each reader thread
    }

    // Create writer threads
    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i + 1; // Assign IDs to writers (starting from 1)
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]); // Create each writer thread
    }

    // Wait for threads to finish (in this case, they run indefinitely, so this part won't be reached)
    for (int i = 0; i < READERS; i++) {
        pthread_join(readers[i], NULL); // Wait for each reader thread to finish
    }
    for (int i = 0; i < WRITERS; i++) {
        pthread_join(writers[i], NULL); // Wait for each writer thread to finish
    }

    // Clean up semaphores after use
    sem_destroy(&mutex); // Destroy mutex semaphore
    sem_destroy(&wrt);   // Destroy writer semaphore

    return 0;
}

/*
Test Input:
Number of reader and writer threads is defined as READERS (5) and WRITERS (2).
*/

