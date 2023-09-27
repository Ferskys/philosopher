/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:41:18 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/27 16:04:57 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	drop_forks(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	pthread_mutex_unlock(&args->forks[philo->right_fork]);
	pthread_mutex_unlock(&args->forks[philo->left_fork]);
}

void	take_forks(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (philo_check_death(philo) || philo_check_meals(philo))
		return ;
	if (philo->id % 2 != 0 && philo->id != args->nbr_philo)
	{
		pthread_mutex_lock(&args->forks[philo->left_fork]);
		print_def(philo, "has taken left fork");
		pthread_mutex_lock(&args->forks[philo->right_fork]);
		print_def(philo, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(&args->forks[philo->right_fork]);
		print_def(philo, "has taken right fork");
		pthread_mutex_lock(&args->forks[philo->left_fork]);
		print_def(philo, "has taken left fork");
	}
}

void	philo_eat(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (philo_check_death(philo) || philo_check_meals(philo))
		return ;
	philo->last_meal = get_time();
	philo->nbr_of_meals++;
	print_def(philo, "is eating");
	ft_usleep(args->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (philo_check_death(philo) || philo_check_meals(philo))
		return ;
	print_def(philo, "is sleeping");
	ft_usleep(args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (philo_check_death(philo) || philo_check_meals(philo))
		return ;
	print_def(philo, "is thinking");
	usleep(500);
}
