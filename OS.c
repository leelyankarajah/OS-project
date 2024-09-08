#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Thread structure
typedef struct {
    int process_id;
    int thread_id;
    int remaining_time;
} Thread;

// Core structure
typedef struct {
    bool busy;
    Thread* running_thread;
} Core;

int main() {

    // Define parameters
    const int num_processes = 5;
    const int max_threads_per_process = 3;
    const int num_cores = 3;
    const int time_quantum = 4;

    // Create cores
    Core cores[num_cores];
    for (int i = 0; i < num_cores; ++i) {
        cores[i].busy = false;
        cores[i].running_thread = NULL;
    }

    // Create and initialize threads
    Thread* threads[num_processes][max_threads_per_process];
    for (int i = 0; i < num_processes; ++i) {
        for (int j = 0; j < max_threads_per_process; ++j) {
            threads[i][j] = (Thread*)malloc(sizeof(Thread));
            threads[i][j]->process_id = i;
            threads[i][j]->thread_id = j;
            threads[i][j]->remaining_time = rand() % 10 + 1; // Random execution time (1-10)
        }
    }

    // Simulation loop
    int current_time = 0;
    int current_core = 0;
    int total_remaining_threads = num_processes * max_threads_per_process;

    while (total_remaining_threads > 0) {
        // Schedule threads on cores
        for (int i = 0; i < num_processes; ++i) {
            for (int j = 0; j < max_threads_per_process; ++j) {
                Thread* thread = threads[i][j];
                if (thread->remaining_time > 0) {
                    if (!cores[current_core].busy) {
                        cores[current_core].busy = true;
                        cores[current_core].running_thread = thread;
                        current_core = (current_core + 1) % num_cores;
                    }
                }
            }
        }

        // Execute threads on cores
        for (int i = 0; i < num_cores; ++i) {
            if (cores[i].busy) {
                Thread* running_thread = cores[i].running_thread;
                printf("Time %d: Executing Process %d Thread %d\n", current_time,
                       running_thread->process_id, running_thread->thread_id);
                running_thread->remaining_time -= time_quantum;

                if (running_thread->remaining_time <= 0) {
                    printf("Time %d: Process %d Thread %d completed\n\n", current_time,
                           running_thread->process_id, running_thread->thread_id);
                    cores[i].busy = false;
                    cores[i].running_thread = NULL;
                    total_remaining_threads--;
                }
            }
        }

        current_time += time_quantum;
    }

    // Clean up allocated memory
    for (int i = 0; i < num_processes; ++i) {
        for (int j = 0; j < max_threads_per_process; ++j) {
            free(threads[i][j]);
        }
    }

    return 0;
}
