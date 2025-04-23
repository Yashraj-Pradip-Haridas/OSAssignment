#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define MAX_READERS 5
#define MAX_WRITERS 2
#define MAX_THREADS (MAX_READERS + MAX_WRITERS)

volatile int shared_data = 0;
volatile int read_count = 0;

int use_sync = 1;

pthread_mutex_t read_mutex;
sem_t write_sem;

void* reader(void* arg) {
    int id = *((int*)arg);

    if (use_sync) {
        pthread_mutex_lock(&read_mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&write_sem);
        }
        pthread_mutex_unlock(&read_mutex);
    }

    // Simulate potential race condition
    printf("Reader %d: (before read) shared_data = %d\n", id, shared_data);
    usleep(100); // Intentional delay
    printf("Reader %d: (after read) shared_data = %d\n", id, shared_data);

    if (use_sync) {
        pthread_mutex_lock(&read_mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&write_sem);
        }
        pthread_mutex_unlock(&read_mutex);
    }

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *((int*)arg);

    if (use_sync) {
        sem_wait(&write_sem);
    }

    int temp = shared_data;
    usleep(100); // Intentional delay to simulate race
    shared_data = temp + 10;
    printf("Writer %d: wrote shared_data = %d\n", id, shared_data);

    if (use_sync) {
        sem_post(&write_sem);
    }

    pthread_exit(NULL);
}

int main() {
    printf("Do you want to run in synchronized mode? (1 = Yes, 0 = No): ");
    scanf("%d", &use_sync);

    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];
    char thread_types[MAX_THREADS]; // 'r' for reader, 'w' for writer

    if (use_sync) {
        pthread_mutex_init(&read_mutex, NULL);
        sem_init(&write_sem, 0, 1);
    }

    // Create a randomized mix of reader and writer threads
    srand(time(NULL));
    int r = 0, w = 0;
    for (int i = 0; i < MAX_THREADS; i++) {
        int choose_reader = rand() % 2;

        if ((choose_reader && r < MAX_READERS) || w >= MAX_WRITERS) {
            thread_ids[i] = r + 1;
            thread_types[i] = 'r';
            pthread_create(&threads[i], NULL, reader, &thread_ids[i]);
            r++;
        } else if (w < MAX_WRITERS) {
            thread_ids[i] = w + 1;
            thread_types[i] = 'w';
            pthread_create(&threads[i], NULL, writer, &thread_ids[i]);
            w++;
        }

        usleep(100); // Add slight delay between thread spawns for more randomness
    }

    // Join all threads
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (use_sync) {
        pthread_mutex_destroy(&read_mutex);
        sem_destroy(&write_sem);
    }

    printf("Final value of shared_data = %d\n", shared_data);
    return 0;
}
