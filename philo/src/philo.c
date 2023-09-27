/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:27:47 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/27 16:05:25 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_config	*args;

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
	args->start_time = get_time();
	philo_threader(args);
	usleep(500);
	clear_program(args);
	return (0);
}
