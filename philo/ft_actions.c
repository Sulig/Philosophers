/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:29:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/18 14:22:16 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork.locker);
	if (!philo->lf_grab)
	{
		if (!philo->l_fork.grabed)
		{
			philo->l_fork.grabed = 1;
			philo->lf_grab = 1;
			philo->action = "\033[1;34mhas grabed the left fork 🍴";
			ft_print_action(philo);
		}
	}
	pthread_mutex_lock(&philo->r_fork.locker);
	if (!philo->rf_grab)
	{
		if (!philo->r_fork.grabed)
		{
			philo->r_fork.grabed = 1;
			philo->rf_grab = 1;
			philo->action = "\033[1;34mhas grabed the right fork 🍴";
			ft_print_action(philo);
		}
	}
}

static void	ft_release_forks(t_philo *philo, int print)
{
	if (philo->lf_grab)
	{
		if (philo->l_fork.grabed)
		{
			philo->l_fork.grabed = 0;
			philo->lf_grab = 0;
			philo->action = "\033[1;34mhas released the left fork 🍴";
			if (print)
				ft_print_action(philo);
			pthread_mutex_unlock(&philo->l_fork.locker);
		}
	}
	if (philo->rf_grab)
	{
		if (philo->r_fork.grabed)
		{
			philo->r_fork.grabed = 0;
			philo->rf_grab = 0;
			philo->action = "\033[1;34mhas released the right fork 🍴";
			if (print)
				ft_print_action(philo);
			pthread_mutex_unlock(&philo->r_fork.locker);
		}
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (!(philo->num % 2))
	{
		usleep(1000);
		philo->live_time = ft_gettime() - philo->start_time;
	}
	while (!philo->dead)
	{
		ft_grab_forks(philo);
		philo->dead = ft_kill_philo(philo);
	}
	philo->action = "\033[1;31mis DEAD ☠️";
	ft_print_action(philo);
	ft_release_forks(philo, 0);
	return (NULL);
}
