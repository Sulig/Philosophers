/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:04:14 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/16 20:20:40 by sadoming         ###   ########.fr       */
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
		if (!prog->philos[i].times_to_eat)
		{
			prog->end_eating++;
			break ;
		}
		i++;
	}
	if (prog->end_eating == prog->n_philos)
		prog->end_flag = 1;
	return (prog->end_flag);
}

int	ft_kill_philo(t_philo *philo)
{
	size_t	current_time;

	current_time = ft_gettime() - philo->start_time;;
	if (current_time - philo->last_eat >= philo->time_to_die)
		philo->dead = 1;
	return (philo->dead);
}

int	ft_check_if_philo_dead(t_prog *prog)
{
	size_t	i;

	i = 0;
	while (i < prog->n_philos)
	{
		prog->dead_flg = ft_kill_philo(&prog->philos[i]);
		if (prog->dead_flg)
			break ;
		i++;
	}
	return (prog->dead_flg);
}

void	*ft_observer(void *arg)
{
	t_prog	*prog;

	prog = arg;
	while (!prog->dead_flg && !prog->end_flag)
	{
		if (ft_check_eating_times(prog))
			return (NULL);
		if (ft_check_if_philo_dead(prog))
			return (NULL);
	}
	return (NULL);
}
