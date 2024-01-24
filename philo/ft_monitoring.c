/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:04:14 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/24 17:34:44 by sadoming         ###   ########.fr       */
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
		prog->end_flag = 1;
	return (prog->end_flag);
}

int	ft_kill_philo(t_philo *philo)
{
	size_t	for_die;

	for_die = 0;
	philo->dead = 0;
	philo->live_time = ft_gettime() - philo->start_time;
	if (philo->live_time < philo->time_to_die)
		for_die = philo->time_to_die - philo->live_time;
	else
		for_die = philo->live_time - philo->time_to_die;
	if (!philo->eating)
		if (!for_die)
			philo->dead = 1;
	if (philo->dead)
		philo->action = "\033[1;31mis DEAD ☠️";
	return (philo->dead);
}

void	*ft_observer(void *arg)
{
	t_prog	*prog;
	size_t	i;

	prog = arg;
	while (!prog->dead_flg && !prog->end_flag)
	{
		i = 0;
		prog->end_flag = ft_check_eating_times(prog);
		if (prog->end_flag)
			return (NULL);
		while (i < prog->n_philos)
		{
			prog->dead_flg = ft_kill_philo(&prog->philos[i]);
			if (prog->dead_flg)
			{
				ft_print_action(&prog->philos[i]);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
