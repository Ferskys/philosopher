/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy..c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:22:29 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/26 23:46:31 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
