/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:29:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/24 17:37:34 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_grab_forks(t_philo *philo)
{
	if (!philo->forks[philo->lf_num].grabed && !philo->lf_grab)
	{
		pthread_mutex_lock(&philo->forks[philo->lf_num].locker);
		philo->forks[philo->lf_num].grabed = 1;
		philo->lf_grab = 1;
		philo->action = "\033[1;36mhas grabed the left fork 🍴";
		ft_print_action(philo);
	}
	if (!philo->forks[philo->rf_num].grabed && !philo->rf_grab)
	{
		pthread_mutex_lock(&philo->forks[philo->rf_num].locker);
		philo->forks[philo->rf_num].grabed = 1;
		philo->rf_grab = 1;
		philo->action = "\033[1;36mhas grabed the right fork 🍴";
		ft_print_action(philo);
	}
}

void	ft_release_forks(t_philo *philo, int print)
{
	if (philo->lf_grab)
	{
		if (philo->forks[philo->lf_num].grabed)
		{
			philo->forks[philo->lf_num].grabed = 0;
			philo->lf_grab = 0;
			philo->action = "\033[1;34mhas released the left fork 🍴";
			if (print)
				ft_print_action(philo);
			pthread_mutex_unlock(&philo->forks[philo->lf_num].locker);
		}
	}
	if (philo->rf_grab)
	{
		if (philo->forks[philo->rf_num].grabed)
		{
			philo->forks[philo->rf_num].grabed = 0;
			philo->rf_grab = 0;
			philo->action = "\033[1;34mhas released the right fork 🍴";
			if (print)
				ft_print_action(philo);
			pthread_mutex_unlock(&philo->forks[philo->rf_num].locker);
		}
	}
}

static void	ft_is_eating(t_philo *philo)
{
	philo->eating = 1;
	philo->action = "\033[1;33mis eating 🍝";
	ft_print_action(philo);
	philo->last_eat = ft_gettime() - philo->start_time;
	philo->time_to_die += philo->last_eat;
	if (philo->times_to_eat > 0)
		philo->times_to_eat--;
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
}

static void	ft_sleep_think(t_philo *philo)
{
	philo->action = "\033[0;37mis sleeping 💤";
	ft_print_action(philo);
	ft_usleep(philo->time_to_sleep);
	philo->action = "\033[1;37mis thinking 💭";
	ft_print_action(philo);
	ft_usleep(philo->time_to_think);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->time_to_think = philo->time_to_eat + philo->time_to_sleep;
	if (philo->time_to_think > philo->time_to_die)
		philo->time_to_think -= philo->time_to_die;
	else
		philo->time_to_think = philo->time_to_die - philo->time_to_think;
	if (philo->time_to_think - 2 > 0)
		philo->time_to_think -= 2;
	if (!(philo->num % 2))
		ft_usleep(philo->time_to_think);
	while (!philo->dead)
	{
		ft_grab_forks(philo);
		if (philo->lf_grab && philo->rf_grab)
		{
			ft_is_eating(philo);
			ft_release_forks(philo, 1);
			ft_sleep_think(philo);
		}
		philo->dead = ft_kill_philo(philo);
	}
	return (NULL);
}
