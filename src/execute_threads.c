/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:41:18 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/26 23:35:16 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (philo_check_death(philo))
		return ;
	if (philo->id % 2 != 0 && philo->id != args->nbr_philo)
	{
		pthread_mutex_lock(&args->forks[philo->left_fork]);
		print_def(philo, "has taken left fork");
		pthread_mutex_lock(&args->forks[philo->right_fork]);
		print_def(philo, "has taken right fork");
		philo->last_meal = get_time();
		philo->nbr_of_meals++;
		print_def(philo, "is eating");
		usleep(1000 * args->time_to_eat);
	}
	else
	{
		pthread_mutex_lock(&args->forks[philo->right_fork]);
		print_def(philo, "has taken right fork");
		pthread_mutex_lock(&args->forks[philo->left_fork]);
		print_def(philo, "has taken left fork");
		philo->last_meal = get_time();
		philo->nbr_of_meals++;
		print_def(philo, "is eating");
		usleep(1000 * args->time_to_eat);
	}
	pthread_mutex_unlock(&args->forks[philo->right_fork]);
	pthread_mutex_unlock(&args->forks[philo->left_fork]);
}

void	philo_sleep(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (philo_check_death(philo))
		return ;
	print_def(philo, "is sleeping");
	usleep(1000 * args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (philo_check_death(philo))
		return ;
	print_def(philo, "is thinking");
	usleep(1000);
}

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
