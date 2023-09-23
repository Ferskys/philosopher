/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:27:47 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/23 18:13:36 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_args(t_arg *args, int argc, char **argv)
{

	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->dead = 0;
	if (argc == 6)
		args->nbr_of_meals = ft_atoi(argv[5]);
	else if (argc == 5)
		args->nbr_of_meals = -1;
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
}

int	ft_check_valid(int argc, char **argv)
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

int	main(int argc, char **argv)
{
	t_arg args;

	if (ft_check_valid(argc, argv))
		return (1);
	if (ft_init_args(&args, argc, argv) == 1)
		return (1);

	return (0);
}