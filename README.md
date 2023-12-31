# Philosophers - Dining Philosophers Problem

![image](https://github.com/Ferskys/philosopher/assets/82189986/522f8c87-d79b-4395-ba5e-9d01a5300594)

## Overview
The Dining Philosophers Problem is a classic concurrency problem in computer science. This code provides an alternative implementation of the problem using pthreads in C.

- One or more philosophers sit at a round table.
- The philosophers alternatively eat, think, or sleep.
- There are forks on the table, one for each philosopher.
- Each philosopher takes their left and right forks to eat.
- When a philosopher finishes eating, they put their forks back on the table and start sleeping.

## Global Rules
- You have to write two programs: `philo` and `philo_bonus` (for the bonus part).
- Global variables are forbidden.
- The programs should take the following arguments:
  - `number_of_philosophers`: The number of philosophers and forks.
  - `time_to_die`: If a philosopher doesn't start eating within this time, they die.
  - `time_to_eat`: The time it takes for a philosopher to eat.
  - `time_to_sleep`: The time a philosopher spends sleeping.
  - `[number_of_times_each_philosopher_must_eat]`: Optional argument to stop the simulation after all philosophers have eaten a certain number of times.

## Mandatory Part (philo)
- Each philosopher is a thread.
- There is one fork between each pair of philosophers.
- Protect the forks' state with a mutex.

## Bonus Part (philo_bonus)
- All the forks are put in the middle of the table, represented by a semaphore.
- Each philosopher is a process.
- The main process is not a philosopher.

## Logs Format
- All state changes of a philosopher should be formatted as follows:
  - `{timestamp} {philosopher_number} has taken a fork`
  - `{timestamp} {philosopher_number} is eating`
  - `{timestamp} {philosopher_number} is sleeping`
  - `{timestamp} {philosopher_number} is thinking`
  - `{timestamp} {philosopher_number} died`
- Timestamps are in milliseconds.

## Requirements and External Functions
The programs should comply with the specified requirements.
Some of the external functions that can be used are:
- memset, printf, malloc, free, write, ft_usleep
- gettimeofday, pthread_create, pthread_detach, pthread_join
- pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
- fork, kill, exit, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink

## Usage
To compile and run the programs, you can use the provided `Makefile`. Here are a few examples:
------------------------------------------------------------------------------------------------------
```
#include <string.h>

int main() {
    char arr[10];
    memset(arr, 'A', 10);  // Fill the array with 'A' 10 times
    return 0;
}
```
```
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```
``` 
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(10 * sizeof(int));  // Allocate memory for 10 integers
    // Use the allocated memory
    free(ptr);  // Free the allocated memory when done using it
    return 0;
}
```
```
#include <unistd.h>

int main() {
    char buffer[] = "Hello, World!\n";
    write(STDOUT_FILENO, buffer, sizeof(buffer) - 1);  // Write to standard output
    return 0;
}
```
```
#include <unistd.h>

int main() {
    ft_usleep(1000000);  // Sleep for 1 second (1,000,000 microseconds)
    return 0;
}
```
```
#include <sys/time.h>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("Seconds: %ld, Microseconds: %ld\n", tv.tv_sec, tv.tv_usec);
    return 0;
}
```
```
#include <pthread.h>
#include <stdio.h>

void *thread_function(void *arg) {
    printf("Thread is running\n");
    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_function, NULL);
    pthread_join(thread_id, NULL);  // Wait for the thread to finish
    return 0;
}
```
```
#include <pthread.h>

pthread_mutex_t mutex;

void *thread_function(void *arg) {
    pthread_mutex_lock(&mutex);
    // Critical section
    printf("Thread is in the critical section\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_function, NULL);
    pthread_join(thread_id, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
```


8818 3 is eating
8918 4 is thinking
8918 2 is thinking
9018 1 is sleeping
9018 3 is sleeping
9018 4 has taken a fork
9018 4 has taken a fork
9018 4 is eating
9018 2 has taken a fork
9018 2 has taken a fork
9018 2 is eating
9118 1 is thinking
9118 3 is thinking
9218 2 is sleeping
9218 3 has taken a fork
9218 3 has taken a fork
9218 3 is eating
9218 1 has taken a fork
9218 1 has taken a fork
9218 1 is eating
9218 4 is sleeping
9319 2 is thinking
9319 4 is thinking