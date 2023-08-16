/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:16:41 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/16 11:22:17 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>


long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
    return milliseconds;
}

void eat(Philosopher* philosopher) {
    printf("%lld %d is eating\n", current_timestamp(), philosopher->philosopher_number);
    usleep(philosopher->time_to_eat * 1000);
}

void sleep_philosopher(Philosopher* philosopher) {
    printf("%lld %d is sleeping\n", current_timestamp(), philosopher->philosopher_number);
    usleep(philosopher->time_to_sleep * 1000);
}

void think(Philosopher* philosopher) {
    printf("%lld %d is thinking\n", current_timestamp(), philosopher->philosopher_number);
}

void die(Philosopher* philosopher) {
    printf("%lld %d died\n", current_timestamp(), philosopher->philosopher_number);
}

void take_left_fork(Philosopher* philosopher) {
    pthread_mutex_lock(&philosopher->left_fork);
    printf("%lld %d has taken a fork\n", current_timestamp(), philosopher->philosopher_number);
}

void take_right_fork(Philosopher* philosopher) {
    pthread_mutex_lock(&philosopher->right_fork);
    printf("%lld %d has taken a fork\n", current_timestamp(), philosopher->philosopher_number);
}

void release_left_fork(Philosopher* philosopher) {
    pthread_mutex_unlock(&philosopher->left_fork);
}

void release_right_fork(Philosopher* philosopher) {
    pthread_mutex_unlock(&philosopher->right_fork);
}

void* philosopher_behavior(void* arg) {
    Philosopher* philosopher = (Philosopher*)arg;
    int eat_count = 0;
    
    while (1) {
        take_left_fork(philosopher);
        take_right_fork(philosopher);
        
        eat(philosopher);
        eat_count++;
        
        release_left_fork(philosopher);
        release_right_fork(philosopher);
        
        if (philosopher->number_of_times_to_eat > 0 && eat_count >= philosopher->number_of_times_to_eat) {
            break;
        }
        
        sleep_philosopher(philosopher);
        think(philosopher);
    }
    
    die(philosopher);
    
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }
    
    int number_of_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);
    int number_of_times_each_philosopher_must_eat = (argc == 5) ? atoi(argv[5]) : -1;
    
    pthread_t* philosophers = (pthread_t*) malloc(number_of_philosophers * sizeof(pthread_t));
    Philosopher* philosophers_data = (Philosopher*) malloc(number_of_philosophers * sizeof(Philosopher));
    
    memset(philosophers_data, 0, number_of_philosophers * sizeof(Philosopher));
    
    pthread_mutex_t* forks = (pthread_mutex_t*) malloc(number_of_philosophers * sizeof(pthread_mutex_t));
    
    int i = 0;
    while (i < number_of_philosophers) {
        pthread_mutex_init(&forks[i], NULL);
        
        philosophers_data[i].philosopher_number = i + 1;
        philosophers_data[i].left_fork = forks[i];
        philosophers_data[i].right_fork = forks[(i + 1) % number_of_philosophers];
        philosophers_data[i].time_to_die = time_to_die;
        philosophers_data[i].time_to_eat = time_to_eat;
        philosophers_data[i].time_to_sleep = time_to_sleep;
        philosophers_data[i].number_of_times_to_eat = number_of_times_each_philosopher_must_eat;
        
        pthread_create(&philosophers[i], NULL, philosopher_behavior, &philosophers_data[i]);
        pthread_detach(philosophers[i]);
        
        i++;
    }
    
    usleep(time_to_die * 1000); // Wait for the specified time to check if any philosopher died
    
    i = 0;
    while (i < number_of_philosophers) {
        pthread_cancel(philosophers[i]);
        pthread_mutex_destroy(&forks[i]);
        
        i++;
    }
    
    free(philosophers);
    free(philosophers_data);
    free(forks);
    
    return 0;
}
