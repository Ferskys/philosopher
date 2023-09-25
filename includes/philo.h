/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:48:59 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/24 20:46:24 by fsuomins         ###   ########.fr       */
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
	int				id;
	int				nbr_of_meals;
	int				left_fork;
	int				right_fork;
	long int		last_meal;
	pthread_t		thread;
	pthread_t 		monitor;
}					t_philo;

typedef struct s_config
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	int				dead;
	t_philo			*philo;
	long int		start_time;
	pthread_mutex_t	*forks;
}					t_config;

int					ft_atoi(const char *str);
void				ft_check_args(void);
int					init_args(t_config *args, int argc, char **argv);
int					ft_is_digit(char *str);
void				clear_program(t_config *args);
long int			get_time(void);
void				*philo_routine(void *arg);

#endif
