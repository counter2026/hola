#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Shared resource
int shared_data = 0;  // Shared data that readers read and writers modify

// Counter for readers
int readcnt = 0;  // Keeps track of the number of active readers

// Mutexes for controlling access
pthread_mutex_t mutex;  // Protects the readcnt (number of active readers)
pthread_mutex_t wrt;    // Controls exclusive access to the shared data for writers

// Max iterations for readers and writers to simulate repeated operations
int MAX_ITERATIONS = 5;

// Reader function
void* reader(void* arg) {
    int id = *((int*)arg);  // Reader ID (unique for each reader thread)
    free(arg);  // Freeing the dynamically allocated memory for reader ID

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // Reader wants to enter the critical section, so it locks mutex to update readcnt
        pthread_mutex_lock(&mutex);  // Equivalent to wait(mutex)
        readcnt++;  // Increment the count of active readers
        if (readcnt == 1) {
            // If this is the first reader, it locks wrt to block writers from writing
            pthread_mutex_lock(&wrt);  // Equivalent to wait(wrt)
        }
        pthread_mutex_unlock(&mutex);  // Unlock mutex after updating readcnt, allowing other readers to enter

        // Critical Section - Reader reads the shared resource
        printf("Reader %d is reading shared data: %d\n", id, shared_data);
        sleep(1);  // Simulate reading time (sleep for 1 second)

        // Reader finished reading, now it updates readcnt
        pthread_mutex_lock(&mutex);  // Lock to safely update readcnt
        readcnt--;  // Decrement the count of active readers
        if (readcnt == 0) {
            // If this is the last reader, it unlocks wrt to allow writers to write
            pthread_mutex_unlock(&wrt);  // Equivalent to signal(wrt)
        }
        pthread_mutex_unlock(&mutex);  // Unlock mutex after updating readcnt

        sleep(1);  // Simulate delay between reads (thinking time for the reader)
    }

    return NULL;
}

// Writer function
void* writer(void* arg) {
    int id = *((int*)arg);  // Writer ID (unique for each writer thread)
    free(arg);  // Freeing the dynamically allocated memory for writer ID

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // Writer wants to write to the shared resource, so it locks wrt
        pthread_mutex_lock(&wrt);  // Equivalent to wait(wrt) for writers

        // Critical Section - Writer modifies the shared resource
        shared_data += 10;  // Writer modifies the shared data (incrementing by 10)
        printf("Writer %d is writing new shared data: %d\n", id, shared_data);

        pthread_mutex_unlock(&wrt);  // Release wrt, allowing other readers/writers to access the shared data
        sleep(2);  // Simulate writing time (sleep for 2 seconds)
    }

    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];  // Arrays to hold reader and writer threads

    // Initialize mutexes
    pthread_mutex_init(&mutex, NULL);  // Initialize mutex for protecting readcnt (number of readers)
    pthread_mutex_init(&wrt, NULL);    // Initialize mutex for controlling writers' access to the shared resource

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        int* id = malloc(sizeof(int));  // Dynamically allocate memory for reader ID
        *id = i + 1;  // Assign a unique ID to each reader
        pthread_create(&readers[i], NULL, reader, id);  // Create the reader thread
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        int* id = malloc(sizeof(int));  // Dynamically allocate memory for writer ID
        *id = i + 1;  // Assign a unique ID to each writer
        pthread_create(&writers[i], NULL, writer, id);  // Create the writer thread
    }

    // Wait for all reader threads to complete their execution
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);  // Wait for each reader thread to finish
    }

    // Wait for all writer threads to complete their execution
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);  // Wait for each writer thread to finish
    }

    // Destroy mutexes after use
    pthread_mutex_destroy(&mutex);  // Destroy the mutex protecting readcnt
    pthread_mutex_destroy(&wrt);    // Destroy the mutex controlling writers

    printf("All readers and writers have finished their operations.\n");

    return 0;
}

/*
Test Input:
- 5 readers and 2 writers, each performing 5 iterations of reading or writing.
*/

/*
Key Concepts:
1. **Shared Resource**: The variable `shared_data` is being accessed by both readers (who only read) and writers (who modify the data).
   
2. **Mutexes**:
   - `mutex`: This mutex is used to protect the `readcnt` variable, which keeps track of the number of active readers. It ensures that updates to `readcnt` are thread-safe.
   - `wrt`: This mutex controls access to the shared resource. When it's locked by a writer, no readers or other writers can access the resource.

3. **Reader Function**:
   - Each reader locks the `mutex` to update the `readcnt`. If it's the first reader, it locks the `wrt` mutex to block writers from accessing the shared resource.
   - Once a reader finishes reading, it decrements `readcnt` and, if it's the last reader, unlocks the `wrt` mutex, allowing writers to access the shared resource.
   - Readers execute the reading process in a loop, sleeping after each read to simulate thinking time.

4. **Writer Function**:
   - Each writer locks the `wrt` mutex to ensure exclusive access to the shared resource.
   - After modifying the shared resource (increasing its value), it unlocks `wrt` so other threads can access the resource.
   - Writers perform their operation in a loop, simulating writing time with `sleep()`.

5. **Thread Creation**:
   - Reader and writer threads are created dynamically using `pthread_create`. Each thread is assigned a unique ID to distinguish it when outputting messages.

6. **Thread Joining**:
   - After the threads are created, `pthread_join` is used to ensure that the main thread waits for all reader and writer threads to complete before exiting the program.

7. **Mutex Destruction**:
   - After all threads have finished, the mutexes are destroyed using `pthread_mutex_destroy` to clean up resources.

This program simulates the classic "readers-writers" problem where multiple readers can access the shared resource concurrently, but writers require exclusive access. The mutexes help manage synchronization between threads to ensure that data is accessed safely.
*/
