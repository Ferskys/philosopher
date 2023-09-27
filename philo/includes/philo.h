/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:48:59 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/27 16:37:06 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	_Atomic int			nbr_of_meals;
	_Atomic long int	last_meal;
	pthread_t			thread;
}					t_philo;

typedef struct s_config
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	long int		start_time;
	_Atomic int		dead;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead_mutex;
}					t_config;

void				print_def(t_philo *philo, char *str);
void				error_type(char *str, int error);
void				philo_threader(t_config *args);
void				clear_program(t_config *args);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
void				one_philo(t_config *args);
void				*philo_routine(void *arg);
void				philo_eat(t_philo *philo);
void				ft_usleep(long time);
int					init_args(t_config *args, int argc, char **argv);
int					validate_args(int argc, char **argv);
int					philo_check_death(t_philo *philo);
int					philo_check_meals(t_philo *philo);
int					ft_atoi(const char *str);
int					ft_is_digit(char *str);
long int			get_time(void);
t_config			*get_args(void);

#endif
