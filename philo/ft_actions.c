/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:29:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/17 13:00:25 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!philo->dead)
	{
		ft_print_action(philo);
		philo->dead = ft_kill_philo(philo);
		//Routine
	}
	philo->action = "\033[1;31mis DEAD ☠️";
	ft_print_action(philo);
	//unlock mutex?
	//unlock forks?
	return (NULL);
}
