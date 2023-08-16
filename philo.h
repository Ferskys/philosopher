/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:40:37 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/16 11:22:25 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philo_H
# define philo_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

typedef struct {
    int philosopher_number;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_to_eat;
} Philosopher;

#endif