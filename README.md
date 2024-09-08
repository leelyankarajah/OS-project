# This C program simulates a basic multi-core system where threads from multiple processes are executed on available cores using round-robin scheduling.

# 1. Structures Definition:
Thread: Represents a thread with a process_id, thread_id, and remaining_time (the time the thread needs to finish execution).
Core: Represents a CPU core, which can be either busy or idle. When busy, it holds a pointer to a currently running thread.
# 2. Main Parameters:
num_processes: The number of processes in the system (5 in this case).
max_threads_per_process: Maximum number of threads per process (3).
num_cores: Number of CPU cores (3).
time_quantum: The time slice for each thread before it is preempted (4 units of time).
# 3. Core Initialization:
Initializes num_cores (3 cores in this case), where all cores are set to idle (not busy) and not running any threads.
# 4. Thread Initialization:
Creates a 2D array threads representing the threads for each process.
Each thread is assigned a random remaining execution time between 1 and 10.
# 5. Simulation Loop:
Scheduler: The loop simulates the scheduling of threads on the cores.
For each process, if a thread has remaining execution time, it is assigned to an idle core.
Execution: The loop simulates thread execution on each core.
If a core is busy, the running thread's remaining time is reduced by the time quantum (4 units). If the remaining time becomes 0 or less, the thread is marked as complete, and the core is freed.
This continues until all threads are completed.
# 6. Core Assignment:
Threads are assigned to cores in a round-robin fashion. Each thread gets assigned to an available core, moving to the next core each time.
# 7. Execution Time:
For each time unit, the threads on the busy cores execute, reducing their remaining time by the time quantum.
If a thread finishes, a message is printed indicating that the thread has completed, and the core is freed for another thread.
# 8. Memory Cleanup:
After the simulation ends (when all threads have completed), the memory allocated for each thread is freed to prevent memory leaks.
