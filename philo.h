/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:48:59 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/23 18:06:28 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philosopher_id;
	int				num_philosophers;
	int				num_times_to_eat;
	struct timeval	last_meal_time;
}					t_philo;

typedef struct s_threads
{
	pthread_t		thread;

}					t_treades;

typedef struct s_arg
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	int				nbr_of_meals;
	// time_t			start_time;
	// pthread_mutex_t	*forks;
	// pthread_t		*tids;
	// pthread_mutex_t	lock_print;
	// t_philo			*all_philos;
}					t_arg;


// Function to convert a string to an integer
int					ft_atoi(const char *str);

// Function to print instructions for providing correct arguments
void				ft_check_args(void);

// Function to initialize the t_philo structure based on the provided arguments
int					ft_init_args(t_arg *args, int argc, char **argv);

int					ft_is_digit(char *str);

#endif
