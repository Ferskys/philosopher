# Philosophers

## Dining Philosophers Problem
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
- memset, printf, malloc, free, write, usleep
- gettimeofday, pthread_create, pthread_detach, pthread_join
- pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
- fork, kill, exit, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink

## Usage
To compile and run the programs, you can use the provided `Makefile`. Here are a few examples:

