#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Define the maximum buffer size

// Shared buffer, counter, mutex, and condition variables
int buffer[BUFFER_SIZE];  
int count = 0;  // Keeps track of the current number of items in the buffer
pthread_mutex_t mutex;  // Mutex to synchronize access to the buffer
pthread_cond_t not_full, not_empty;  // Condition variables to manage buffer states

// Producer thread function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Each producer generates 10 items
        item = rand() % 100;  // Produce a random item

        // Acquire the mutex lock to access the buffer safely
        pthread_mutex_lock(&mutex);

        // If the buffer is full, wait until not_full is signaled
        while (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        // Add item to the buffer
        buffer[count++] = item;  
        printf("Producer produced: %d\n", item);

        // Signal that the buffer is no longer empty
        pthread_cond_signal(&not_empty);  

        // Release the mutex lock after adding the item
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Simulate production time
    }
    return NULL;  // End of producer thread
}

// Consumer thread function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Each consumer consumes 10 items
        // Acquire the mutex lock to access the buffer safely
        pthread_mutex_lock(&mutex);

        // If the buffer is empty, wait until not_empty is signaled
        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        // Consume an item from the buffer
        item = buffer[--count];  
        printf("Consumer consumed: %d\n", item);

        // Signal that the buffer is no longer full
        pthread_cond_signal(&not_full);  

        // Release the mutex lock after consuming the item
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Simulate consumption time
    }
    return NULL;  // End of consumer thread
}

int main() {
    pthread_t prod_thread, cons_thread;  // Thread identifiers for producer and consumer

    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for both threads to finish execution
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up: destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;  // End of the program
}
