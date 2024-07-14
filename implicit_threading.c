#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>  // Include pthread.h for POSIX threads
#include <time.h>     // Include time.h for srand

#define NUM_THREADS 10

// Function that represents a process
void *process(void *thread_id) {
    int tid = *((int *) thread_id);
    printf("Thread %lu executing process %d\n", (unsigned long)pthread_self(), tid);
    
    // Simulate some work
    int work_duration = 2 + (rand() % 5); 
    sleep(work_duration);
    
    printf("Thread %lu finished process %d\n", (unsigned long)pthread_self(), tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    srand(time(NULL)); 

    printf("Creating %d threads to execute processes:\n", NUM_THREADS);
    
    // Create threads for each process
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, process, &thread_ids[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    printf("All processes completed.\n");

    return 0;
}
