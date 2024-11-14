#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Define the size of the buffer (circular queue)

// Declare semaphores for managing the buffer
sem_t empty, full;  // `empty` tracks empty slots, `full` tracks filled slots

// Declare a mutex for synchronizing access to the buffer
pthread_mutex_t mutex; 

// Declare the buffer array and pointers for the producer and consumer
int buffer[BUFFER_SIZE];  
int in = 0, out = 0;  // `in` for producer (index to insert), `out` for consumer (index to remove)

// Producer thread function
void *producer(void *arg) {
    int producer_id = *((int *)arg);  // Get the producer ID passed as argument
    for (int i = 0; i < 10; i++) {  // Each producer produces 10 items
        sem_wait(&empty);  // Wait if there are no empty slots (buffer is full)
        pthread_mutex_lock(&mutex);  // Lock mutex to safely access shared buffer

        // Produce an item and add it to the buffer
        buffer[in] = i;  
        printf("Producer %d: produced item %d\n", producer_id, i);
        in = (in + 1) % BUFFER_SIZE;  // Move the producer index in a circular way
        usleep(100000);  // Simulate production time

        pthread_mutex_unlock(&mutex);  // Unlock mutex after modifying the buffer
        sem_post(&full);  // Signal that there is a new item in the buffer
    }
    return NULL;  // End of producer thread
}

// Consumer thread function
void *consumer(void *arg) {
    int consumer_id = *((int *)arg);  // Get the consumer ID passed as argument
    for (int i = 0; i < 10; i++) {  // Each consumer consumes 10 items
        sem_wait(&full);  // Wait if there are no items in the buffer (buffer is empty)
        pthread_mutex_lock(&mutex);  // Lock mutex to safely access shared buffer

        // Consume an item from the buffer
        int item = buffer[out];  
        printf("Consumer %d: consumed item %d\n", consumer_id, item);
        out = (out + 1) % BUFFER_SIZE;  // Move the consumer index in a circular way
        usleep(150000);  // Simulate consumption time

        pthread_mutex_unlock(&mutex);  // Unlock mutex after modifying the buffer
        sem_post(&empty);  // Signal that there is space for a new item in the buffer
    }
    return NULL;  // End of consumer thread
}

int main() {
    int num_producers = 2, num_consumers = 2;  // Number of producer and consumer threads
    pthread_t producers[num_producers], consumers[num_consumers];  // Arrays for thread identifiers
    int producer_ids[num_producers], consumer_ids[num_consumers];  // Arrays to pass producer and consumer IDs

    // Initialize semaphores:
    sem_init(&empty, 0, BUFFER_SIZE);  // 'empty' semaphore initialized to BUFFER_SIZE (all slots are empty)
    sem_init(&full, 0, 0);  // 'full' semaphore initialized to 0 (no items in the buffer initially)
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    // Create producer threads
    for (int i = 0; i < num_producers; i++) {
        producer_ids[i] = i + 1;  // Assign producer ID (1-based)
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);  // Create the producer thread
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; i++) {
        consumer_ids[i] = i + 1;  // Assign consumer ID (1-based)
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);  // Create the consumer thread
    }

    // Wait for all producer threads to finish
    for (int i = 0; i < num_producers; i++) 
        pthread_join(producers[i], NULL);  

    // Wait for all consumer threads to finish
    for (int i = 0; i < num_consumers; i++) 
        pthread_join(consumers[i], NULL);  

    // Clean up: destroy semaphores and mutex
    sem_destroy(&empty);  
    sem_destroy(&full);  
    pthread_mutex_destroy(&mutex);  

    return 0;  // End of the program
}
