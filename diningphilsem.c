#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5  // Number of philosophers (and also the number of forks)

// Semaphores for each fork
sem_t forks[NUM_PHILOSOPHERS];  // Array of semaphores, one for each fork

// Philosopher function
void* philosopher(void* num) {
    int i = *(int*)num;  // Convert the void pointer to the philosopher's ID (index)

    while (1) {  // Infinite loop simulating the philosopher's thinking and eating cycle
        printf("Philosopher %d is thinking...\n", i);  // Print thinking message
        //sleep(1);  // Simulate thinking (commented out to avoid unnecessary delays)

        // Asymmetry: Philosopher 0 picks up the right fork first, others pick up the left fork first
        if (i == 0) {
            // Philosopher 0 picks up the right fork first (next philosopher's fork)
            sem_wait(&forks[(i + 1) % NUM_PHILOSOPHERS]);  // Wait for the right fork (index = (i+1)%5)
            printf("Philosopher %d picked up right fork %d\n", i, (i + 1) % NUM_PHILOSOPHERS);
            
            // Then pick up the left fork (current philosopher's fork)
            sem_wait(&forks[i]);  // Wait for the left fork (index = i)
            printf("Philosopher %d picked up left fork %d\n", i, i);
        } else {
            // For other philosophers, pick up the left fork first
            sem_wait(&forks[i]);  // Wait for the left fork (index = i)
            printf("Philosopher %d picked up left fork %d\n", i, i);
            
            // Then pick up the right fork (next philosopher's fork)
            sem_wait(&forks[(i + 1) % NUM_PHILOSOPHERS]);  // Wait for the right fork (index = (i+1)%5)
            printf("Philosopher %d picked up right fork %d\n", i, (i + 1) % NUM_PHILOSOPHERS);
        }

        // Eating: Once both forks are picked up, philosopher starts eating
        printf("Philosopher %d is eating...\n", i);
        //sleep(1);  // Simulate eating (commented out to avoid unnecessary delays)

        // After eating, philosopher puts down the forks
        sem_post(&forks[i]);  // Release the left fork (index = i)
        printf("Philosopher %d put down left fork %d\n", i, i);
        
        // Release the right fork (index = (i + 1) % NUM_PHILOSOPHERS)
        sem_post(&forks[(i + 1) % NUM_PHILOSOPHERS]);  // Release the right fork
        printf("Philosopher %d put down right fork %d\n", i, (i + 1) % NUM_PHILOSOPHERS);

        // Back to thinking
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];  // Array to hold threads for each philosopher
    int philosopher_ids[NUM_PHILOSOPHERS];  // Array to hold philosopher IDs (for passing to threads)

    // Initialize semaphores for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);  // Initialize semaphores for each fork; value = 1 (fork is available)
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;  // Assign philosopher ID
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);  // Create each philosopher thread
    }

    // Join the threads (this waits for threads to finish execution, which will never happen due to the infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);  // Wait for each philosopher thread to finish
    }

    // Destroy semaphores (this is never reached because of the infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);  // Clean up semaphores (this is redundant since the program never ends)
    }

    return 0;  // Return 0 to indicate successful program execution
}
