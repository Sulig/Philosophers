/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_accions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:32:16 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/11 20:20:23 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_kill_philo(t_philo *philo)
{
	philo->dead = 1;
	philo->action = "\033[1;31mRIP ☠️  \n";
	ft_print_action(philo);
	return (NULL);
}

/*
static void	ft_grab_forks(t_philo *philo)
{
	while (philo->g_forks != 2)
	{

		usleep(1);
	}
}
*/

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!philo->dead)
	{
		if (!philo->dead)
			philo->cron_to_die++;
		if (philo->cron_to_die == philo->time_to_die)
			return (ft_kill_philo(philo));
		usleep(1);
	}
	return (NULL);
}
