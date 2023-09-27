/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:24:36 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/27 15:46:42 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	one_philo(t_config *args)
{
	printf("%ld %d has taken left fork\n", get_time() - args->start_time,
		args->philo[0].id);
	ft_usleep(get_args()->time_to_die);
	printf("%ld %d dead\n", get_time() - args->start_time, args->philo[0].id);
}

int	init_args(t_config *args, int argc, char **argv)
{
	int	i;

	i = 0;
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nbr_of_meals = ft_atoi(argv[5]);
	else if (argc == 5)
		args->nbr_of_meals = -1;
	args->philo = malloc(sizeof(t_philo) * args->nbr_philo);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nbr_philo);
	if (!args->philo || !args->forks)
		return (1);
	while (i < args->nbr_philo)
	{
		args->philo[i].id = i + 1;
		args->philo[i].nbr_of_meals = 0;
		args->philo[i].left_fork = i;
		args->philo[i].right_fork = (i + 1) % args->nbr_philo;
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
	return (0);
}
