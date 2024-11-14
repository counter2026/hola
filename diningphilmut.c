#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PHILOSOPHERS 5  // Number of philosophers (and forks)

// Mutexes for each fork to ensure mutual exclusion
pthread_mutex_t forks[PHILOSOPHERS]; // Array of mutexes, one for each fork

// Philosopher function: simulates thinking, picking up forks, eating, and putting down forks
void* philosopher(void* num) {
    int id = *((int*)num);  // Convert the void pointer to philosopher ID (index)

    while (1) {  // Infinite loop simulating the philosopher's life cycle
        printf("Philosopher %d is thinking...\n", id);  // Philosopher is thinking
        sleep(rand() % 3);  // Simulate the philosopher thinking for 0-2 seconds

        // Pick up both forks
        // To avoid deadlock, always pick up the lower-numbered fork first
        if (id % 2 == 0) {  // Even numbered philosophers pick up the left fork first
            pthread_mutex_lock(&forks[id]);  // Lock the left fork (mutex for fork at index 'id')
            pthread_mutex_lock(&forks[(id + 1) % PHILOSOPHERS]);  // Lock the right fork (next philosopher's fork)
        } else {  // Odd numbered philosophers pick up the right fork first
            pthread_mutex_lock(&forks[(id + 1) % PHILOSOPHERS]);  // Lock the right fork (next philosopher's fork)
            pthread_mutex_lock(&forks[id]);  // Lock the left fork (mutex for fork at index 'id')
        }

        // Eating
        printf("Philosopher %d is eating...\n", id);  // Philosopher is eating
        sleep(rand() % 3);  // Simulate the philosopher eating for 0-2 seconds

        // Put down both forks (unlock the mutexes)
        pthread_mutex_unlock(&forks[(id + 1) % PHILOSOPHERS]);  // Unlock the right fork
        pthread_mutex_unlock(&forks[id]);  // Unlock the left fork
    }
}

int main() {
    pthread_t philosophers[PHILOSOPHERS];  // Array to hold threads for each philosopher
    int ids[PHILOSOPHERS];  // Array to hold philosopher IDs (for passing to threads)

    // Initialize mutexes for each fork (each fork is initially available)
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);  // Initialize mutex for each fork
    }

    // Create philosopher threads
    for (int i = 0; i < PHILOSOPHERS; i++) {
        ids[i] = i;  // Assign philosopher ID
        pthread_create(&philosophers[i], NULL, philosopher, (void*)&ids[i]);  // Create philosopher thread and pass its ID
    }

    // Wait for philosopher threads to finish execution (they won't terminate due to infinite loop)
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);  // Wait for each philosopher thread to finish
    }

    // Clean up (this code will never be reached due to the infinite loop)
    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);  // Destroy mutexes for each fork (clean-up)
    }

    return 0;  // Return 0 to indicate successful program execution
}
