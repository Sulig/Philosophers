/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:04:14 by sadoming          #+#    #+#             */
/*   Updated: 2024/02/01 20:31:35 by sadoming         ###   ########.fr       */
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
		if (prog->philos[i].times_to_eat == 0)
			prog->end_eating++;
		i++;
	}
	if (prog->end_eating == prog->n_philos)
		prog->flag = 2;
	return (prog->flag);
}

int	ft_kill_philo(t_philo *philo)
{
	size_t	for_die;

	pthread_mutex_lock(&philo->m_ltime);
	pthread_mutex_lock(&philo->m_stat);
	for_die = 0;
	philo->live_time = ft_gettime() - philo->start_time;
	if (philo->live_time < philo->time_to_die)
		for_die = philo->time_to_die - philo->live_time;
	else
		for_die = philo->live_time - philo->time_to_die;
	if (!philo->eating)
		if (!for_die)
			philo->status = 0;
	pthread_mutex_unlock(&philo->m_stat);
	pthread_mutex_unlock(&philo->m_ltime);
	return (philo->status);
}

static int	ft_is_philo_dead(t_prog *prog)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < prog->n_philos)
	{
		prog->flag = ft_kill_philo(&prog->philos[i]);
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
	pthread_mutex_lock(&prog->philos[prog->dp].m_stat);
	if (!prog->flag)
	{
		prog->philos[prog->dp].status = 0;
		ft_print_action(&prog->philos[prog->dp], "\033[1;31mdied");
	}
	pthread_mutex_unlock(&prog->philos[prog->dp].m_stat);
	return (NULL);
}
