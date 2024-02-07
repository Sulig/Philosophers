/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:04:14 by sadoming          #+#    #+#             */
/*   Updated: 2024/02/07 14:01:01 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_eating_times(t_prog *prog)
{
	size_t	i;

	i = 0;
	prog->end_eating = 0;
	while (i < prog->n_philos)
	{
		pthread_mutex_lock(&prog->philos[i].m_timeat);
		if (!prog->philos[i].times_to_eat)
			prog->end_eating++;
		pthread_mutex_unlock(&prog->philos[i].m_timeat);
		i++;
	}
	if (prog->end_eating == prog->n_philos)
	{
		i = 0;
		prog->flag = 2;
		while (i < prog->n_philos)
		{
			pthread_mutex_lock(&prog->philos[i].m_stat);
			prog->philos[i].status = 2;
			pthread_mutex_unlock(&prog->philos[i].m_stat);
			i++;
		}
	}
	return (prog->flag);
}

int	ft_status_philo(t_philo *philo)
{
	size_t	for_die;
	size_t	status;

	for_die = 0;
	pthread_mutex_lock(&philo->m_stat);
	status = philo->status;
	pthread_mutex_unlock(&philo->m_stat);
	if (status == 2)
		return (status);
	pthread_mutex_lock(&philo->m_ltime);
	philo->live_time = ft_gettime() - philo->start_time;
	pthread_mutex_lock(&philo->m_dtime);
	if (philo->live_time < philo->time_to_die)
		for_die = philo->time_to_die - philo->live_time;
	else
		for_die = philo->live_time - philo->time_to_die;
	pthread_mutex_unlock(&philo->m_ltime);
	pthread_mutex_unlock(&philo->m_dtime);
	pthread_mutex_lock(&philo->m_eating);
	if (!for_die && !philo->eating && status == 1)
		status = 0;
	pthread_mutex_unlock(&philo->m_eating);
	return (status);
}

static int	ft_is_philo_dead(t_prog *prog)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < prog->n_philos)
	{
		prog->flag = ft_status_philo(&prog->philos[i]);
		if (!prog->flag)
			break ;
		i++;
	}
	if (!prog->flag)
	{
		prog->dp = i;
		while (j < prog->n_philos)
		{
			pthread_mutex_lock(&prog->philos[j].m_stat);
			prog->philos[j].status = 2;
			pthread_mutex_unlock(&prog->philos[j].m_stat);
			j++;
		}
	}
	return (prog->flag);
}

void	*ft_observer(void *arg)
{
	t_prog	*prog;

	prog = arg;
	while (prog->flag == 1)
	{
		prog->flag = ft_check_eating_times(prog);
		if (prog->flag == 2)
			break ;
		prog->flag = ft_is_philo_dead(prog);
	}
	if (!prog->flag)
	{
		pthread_mutex_lock(&prog->philos[prog->dp].m_stat);
		prog->philos[prog->dp].status = 0;
		ft_print_action(&prog->philos[prog->dp], "\033[1;31mdied");
		pthread_mutex_unlock(&prog->philos[prog->dp].m_stat);
	}
	return (NULL);
}
