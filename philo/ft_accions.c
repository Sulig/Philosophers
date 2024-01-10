/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_accions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:32:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/10 14:25:34 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_loop_time(void *arg)
{
	t_prog	*prog;

	prog = arg;
	while (prog->time < 10)
	{
		usleep(1);
		prog->time++;
	}
	prog->time = -1;
	return (NULL);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	philo;

	philo = arg;
	while (!philo.dead)
	{
		//acctions
		usleep(3000);
	}
}
