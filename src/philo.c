/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:27:47 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/26 12:11:20 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_config	*get_args(void)
{
	static t_config	args;

	return (&args);
}

void	clear_program(t_config *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	free(args->forks);
	free(args->philo);
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
		args->nbr_of_meals = 0;
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
	args->start_time = get_time();
	return (0);
}

void	error_type(char *str, int error)
{
	while (*str)
	{
		write(STDERR_FILENO, str++, 1);
	}
	exit(error);
}

void	ft_check_args(void)
{
	printf(" ____________________________________________________ \n");
	printf("|            Please enter 4 or 5 arguments           |\n");
	printf("|____________________________________________________|\n");
	printf("|             [1][Number of philosophers]            |\n");
	printf("|             [2][Time to die]                       |\n");
	printf("|             [3][Time to eat]                       |\n");
	printf("|             [4][Time to sleep]                     |\n");
	printf("|             [5][Number of meals]                   |\n");
	printf("|____________________________________________________|\n");
	exit(1);
}

int	validate_args(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
		ft_check_args();
	i = 1;
	while (argv[i])
	{
		if (!ft_is_digit(argv[i]) || (!ft_atoi(argv[i])))
			error_type(argv[i], 2);
		i++;
	}
	return (0);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_def(t_philo *philo, char *str)
{
	t_config	*args;

	args = get_args();
	pthread_mutex_lock(args->print);
	pthread_mutex_lock(args->dead_mutex);
	if (args->dead == 0)
		printf("%ld %d %s\n", get_time() - args->start_time, philo->id, str);
	pthread_mutex_unlock(args->dead_mutex);
	pthread_mutex_unlock(args->print);
}



void	philo_eat(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (philo->id % 2 != 0)
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
	print_def(philo, "is sleeping");
	usleep(1000 * args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	print_def(philo, "is thinking");
	usleep(1000);
}

int	philo_check_death(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	pthread_mutex_lock(args->dead_mutex);
	if (args->dead == 1 || philo->last_meal + args->time_to_die < get_time())
	{
		print_def(philo, "died");
		args->dead = 1;
		pthread_mutex_unlock(args->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(args->dead_mutex);
	return (0);
}

int	philo_check_meals(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (args->nbr_of_meals != 0)
		if (philo->nbr_of_meals == args->nbr_of_meals)
		{
			print_def(philo, "is full");
			return (1);
		}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_eat(philo);
		if (philo_check_death(philo) || philo_check_meals(philo))
			return (NULL);
		philo_sleep(philo);
		if (philo_check_death(philo))
			return (NULL);
		philo_think(philo);
		if (philo_check_death(philo))
			return (NULL);
	}
	return (NULL);
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
void	one_philo(t_config *args)
{
	printf("%ld %d has taken left fork\n", get_time() - args->start_time,
		args->philo[0].id);
	printf("%ld %d dead\n", get_time() - args->start_time, args->philo[0].id);
}

int	main(int argc, char **argv)
{
	t_config *args;

	args = get_args();
	if (validate_args(argc, argv))
		return (1);
	if (init_args(args, argc, argv) == 1)
		return (1);
	if (args->nbr_philo == 1)
	{
		one_philo(args);
		clear_program(args);
		return (0);
	}
	philo_threader(args);
	clear_program(args);
	return (0);
}
