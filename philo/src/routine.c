/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:37:47 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/27 15:57:59 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_check_death(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	pthread_mutex_lock(args->dead_mutex);
	if (args->dead == 1 || get_time() - philo->last_meal > args->time_to_die)
	{
		print_def(philo, "died");
		args->dead = 1;
		pthread_mutex_unlock(args->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(args->dead_mutex);
	return (0);
}

void	print_def(t_philo *philo, char *str)
{
	t_config	*args;

	args = get_args();
	pthread_mutex_lock(args->print);
	if (args->dead == 0)
		printf("%ld %d %s\n", get_time() - args->start_time, philo->id, str);
	pthread_mutex_unlock(args->print);
}

void	philo_threader(t_config *args)
{
	int	i;

	i = 0;
	args->print = malloc(sizeof(pthread_mutex_t));
	args->dead_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(args->print, NULL);
	pthread_mutex_init(args->dead_mutex, NULL);
	while (i < args->nbr_philo)
	{
		pthread_create(&args->philo[i].thread, NULL, &philo_routine,
			&args->philo[i]);
		i++;
	}
	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_join(args->philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(args->print);
	pthread_mutex_destroy(args->dead_mutex);
	free(args->print);
	free(args->dead_mutex);
}

int	philo_check_meals(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (args->nbr_of_meals != -1 && philo->nbr_of_meals >= args->nbr_of_meals)
		return (1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if (philo->id % 2 != 0)
		philo_think(philo);
	while (!philo_check_death(philo) && !philo_check_meals(philo))
	{
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
