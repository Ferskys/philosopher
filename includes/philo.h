/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:48:59 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/26 23:40:19 by fsuomins         ###   ########.fr       */
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
}					t_philo;

typedef struct s_config
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	t_philo			*philo;
	_Atomic int dead;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead_mutex;
}					t_config;

int					ft_atoi(const char *str);
void				print_def(t_philo *philo, char *str);
t_config			*get_args(void);
int					validate_args(int argc, char **argv);
void				one_philo(t_config *args);
void				philo_threader(t_config *args);
int					init_args(t_config *args, int argc, char **argv);
int					ft_is_digit(char *str);
long int			get_time(void);
void				*philo_routine(void *arg);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
int					philo_check_death(t_philo *philo);
int					philo_check_meals(t_philo *philo);
void				print_dead(t_philo *philo, char *str);
void				clear_program(t_config *args);
void				error_type(char *str, int error);

#endif
