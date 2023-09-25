/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:27:47 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/25 18:36:53 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_config	*get_args(void)
{
	static t_config	args;

	return (&args);
}

void clear_program(t_config *args)
{
    // Free philo array
    free(args->philo);
    
    // Destroy and free mutexes for forks
    for (int i = 0; i < args->nbr_philo; i++)
    {
        pthread_mutex_destroy(&args->forks[i]);
    }
    
    // Free forks array
    free(args->forks);
}


int	init_args(t_config *args, int argc, char **argv)
{
	int	i;

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
	i = 0;
	while (i < args->nbr_philo)
	{
        args->philo[i] = (t_philo){0};  // Initialize with 0 or appropriate values
		args->philo[i].id = i + 1;
		args->philo[i].nbr_of_meals = 0;
		args->philo[i].left_fork = i;
		args->philo[i].right_fork = (i + 1) % args->nbr_philo;
		pthread_mutex_init(&args->forks[i], NULL);
		i++;
	}
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

void	philo_eat(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (args->dead == 1)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&args->forks[philo->left_fork]);
		printf("%ld %d has taken left fork\n", get_time() - args->start_time,
			philo->id);
		if (&args->forks[philo->right_fork] != &args->forks[philo->left_fork])
		{
			pthread_mutex_lock(&args->forks[philo->right_fork]);
			if (get_args()->dead == 1)
				return ;
			printf("%ld %d has taken right fork\n", get_time()
				- args->start_time, philo->id);
			philo->nbr_of_meals++;
			philo->last_meal = get_time();
			usleep(1000 * args->time_to_eat);
			if (get_args()->dead == 1)
				return ;
			printf("%ld %d is eating\n", get_time() - args->start_time,
				philo->id);
			pthread_mutex_unlock(&args->forks[philo->left_fork]);
			pthread_mutex_unlock(&args->forks[philo->right_fork]);
		}
	}
	else
	{
		pthread_mutex_lock(&args->forks[philo->right_fork]);
		printf("%ld %d has taken right fork\n", get_time() - args->start_time,
			philo->id);
		if (&args->forks[philo->right_fork] != &args->forks[philo->left_fork])
		{
			pthread_mutex_lock(&args->forks[philo->left_fork]);
			if (get_args()->dead == 1)
				return ;
			printf("%ld %d has taken left fork\n", get_time()
				- args->start_time, philo->id);
			philo->nbr_of_meals++;
			philo->last_meal = get_time();
			if (args->dead == 1)
				return ;
			usleep(1000 * args->time_to_eat);
			if (get_args()->dead == 1)
				return ;
			printf("%ld %d is eating\n", get_time() - args->start_time,
				philo->id);
			pthread_mutex_unlock(&args->forks[philo->right_fork]);
			pthread_mutex_unlock(&args->forks[philo->left_fork]);
		}
	}
}

void	philo_sleep(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (args->dead == 1)
		return ;
	usleep(1000 * args->time_to_sleep);
	if (get_args()->dead == 1)
		return ;
	printf("%ld %d is sleeping\n", get_time() - args->start_time, philo->id);
}

void	philo_think(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (get_args()->dead == 1)
		return ;
	printf("%ld %d is thinking\n", get_time() - args->start_time, philo->id);
}

void	philo_check_meals(t_philo *philo)
{
	t_config	*args;

	args = get_args();
	if (args->nbr_of_meals != 0)
	{
		if (philo->nbr_of_meals == args->nbr_of_meals)
			exit(1);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_args()->dead == 0)
	{
		if (get_args()->dead == 1)
			break ;
		philo_think(philo);
		if (get_args()->dead == 1)
			break ;
		philo_eat(philo);
		if (get_args()->dead == 1)
			break ;
		philo_check_meals(philo);
		if (get_args()->dead == 1)
			break ;
		philo_sleep(philo);
		if (get_args()->dead == 1)
			break ;
	}
	return (NULL);
}

void	*check_death(void *arg)
{
	t_philo		*philo;
	t_config	*args;

	philo = (t_philo *)arg;
	args = get_args();
	while (1)
	{
		if (args->dead == 1)
		{
			return (NULL);
		}
		if (get_time() - philo->last_meal - 1 > args->time_to_die + 1)
		{
			args->dead = 1;
			printf("%ld %d died of starvation\n", get_time() - args->start_time,
				philo->id);
			return (NULL);
		}
		usleep(1000);
	}
}

void	philo_threader(t_config *args)
{
	int	i;

	i = 0;
	args->start_time = get_time();
	while (i < args->nbr_philo)
	{
		args->philo[i].last_meal = args->start_time;
		pthread_create(&args->philo[i].thread, NULL, philo_routine,
			&args->philo[i]);
		pthread_create(&args->philo[i].monitor, NULL, check_death,
			&args->philo[i]);
		i++;
	}
	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_join(args->philo[i].thread, NULL);
		pthread_join(args->philo[i].monitor, NULL);
		i++;
	}	
}

int	main(int argc, char **argv)
{
	t_config *args;

	args = get_args();
	if (validate_args(argc, argv))
		return (1);
	if (init_args(args, argc, argv) == 1)
		return (1);
	philo_threader(args);
	clear_program(args);
	return (0);
}