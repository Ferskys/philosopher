/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:37:47 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/27 00:03:38 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	while (i < args->nbr_philo)
	{
		args->philo[i].last_meal = get_time();
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
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		philo_think(philo);
	while (!philo_check_death(philo)
		|| (philo->nbr_of_meals < get_args()->nbr_of_meals
			&& get_args()->nbr_of_meals != -1))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}