/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:32:58 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/26 21:05:08 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_check_args(void)
{
	printf(" ____________________________________________________ \n");
	printf("|       Please enter 4 or 5 POSITIVE arguments       |\n");
	printf("|____________________________________________________|\n");
	printf("|             [1][Number of philosophers]            |\n");
	printf("|             [2][Time to die]                       |\n");
	printf("|             [3][Time to eat]                       |\n");
	printf("|             [4][Time to sleep]                     |\n");
	printf("|             [5][Number of meals]                   |\n");
	printf("|____________________________________________________|\n");
	exit(1);
}

void	error_type(char *str, int error)
{
	while (*str)
	{
		write(STDERR_FILENO, str++, 1);
	}
	ft_check_args();
	exit(error);
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
			error_type("         ❌ - Arguments must be numbers. - ❌\n", 2);
		i++;
	}
	return (0);
}
