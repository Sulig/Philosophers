/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:29:45 by sadoming          #+#    #+#             */
/*   Updated: 2024/02/01 20:31:24 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->locker);
	if (!philo->l_fork->grabed && !philo->lf_grab)
	{
		philo->l_fork->grabed = 1;
		philo->lf_grab = 1;
		ft_print_action(philo, "\033[1;36mhas taken a fork 🍴");
	}
	if (!philo->r_fork->grabed && !philo->rf_grab)
	{
		pthread_mutex_lock(&philo->r_fork->locker);
		philo->r_fork->grabed = 1;
		philo->rf_grab = 1;
		ft_print_action(philo, "\033[1;36mhas taken a fork 🍴");
	}
}

void	ft_release_forks(t_philo *philo, int print)
{
	if (philo->l_fork->grabed && philo->lf_grab)
	{
		philo->l_fork->grabed = 0;
		philo->lf_grab = 0;
		if (print == 1)
			ft_print_action(philo, "\033[1;34mhas released a fork");
		pthread_mutex_unlock(&philo->l_fork->locker);
	}
	if (philo->r_fork->grabed && philo->rf_grab)
	{
		philo->r_fork->grabed = 0;
		philo->rf_grab = 0;
		if (print == 1)
			ft_print_action(philo, "\033[1;34mhas released a fork");
		pthread_mutex_unlock(&philo->r_fork->locker);
	}
}

static void	ft_is_eating(t_philo *philo)
{
	philo->eating = 1;
	ft_print_action(philo, "\033[1;33mis eating 🍝");
	philo->last_eat = ft_gettime() - philo->start_time;
	philo->time_to_die += philo->last_eat;
	if (philo->times_to_eat > 0)
		philo->times_to_eat--;
	if (philo->times_to_eat == 0)
		philo->status = 2;
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
}

static void	ft_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_stat);
	if (philo->status == 1)
	{
		ft_print_action(philo, "\033[0;37mis sleeping 💤");
		ft_usleep(philo->time_to_sleep);
	}
	if (philo->status == 1)
	{
		ft_print_action(philo, "\033[1;37mis thinking 💭");
		while (philo->l_fork->grabed)
			ft_usleep(2);
	}
	pthread_mutex_unlock(&philo->m_stat);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->l_fork->num == philo->r_fork->num)
	{
		ft_grab_forks(philo);
		ft_usleep(philo->time_to_die);
		ft_release_forks(philo, 0);
	}
	//pthread_mutex_lock(&philo->m_stat);
	if (!(philo->num % 2))
		ft_usleep(philo->time_to_eat);
	while (philo->status == 1)
	{
		ft_grab_forks(philo);
		if (philo->lf_grab && philo->rf_grab)
		{
			ft_is_eating(philo);
			ft_release_forks(philo, philo->status);
			ft_sleep_think(philo);
		}
	}
	//pthread_mutex_unlock(&philo->m_stat);
	return (NULL);
}
