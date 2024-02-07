/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthreads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:28:03 by sadoming          #+#    #+#             */
/*   Updated: 2024/02/07 14:01:25 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_write_error(t_prog *prog, int num)
{
	prog->error = 1;
	printf("\033[1;31m\n");
	if (num == 0)
		write(2, "Couldn't create a thread!\n", 26);
	else if (num == 1)
		write(2, "Couldn't join the thread!\n", 26);
	else if (num == 2)
		write(2, "Couldn't initiate a mutex!\n", 27);
	else if (num == 3)
		write(2, "Error when destroy a mutex!\n", 28);
	else
		write(2, "An undefined error ocurred!\n", 28);
	return (0);
}

int	ft_init_mutex(t_prog *prog)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&prog->print, NULL) != 0)
		return (ft_write_error(prog, 2));
	while (i < prog->n_philos)
	{
		if (pthread_mutex_init(&prog->forks[i].locker, NULL) != 0)
			return (ft_write_error(prog, 2));
		if (pthread_mutex_init(&prog->philos[i].m_stat, NULL) != 0)
			return (ft_write_error(prog, 2));
		if (pthread_mutex_init(&prog->philos[i].m_ltime, NULL) != 0)
			return (ft_write_error(prog, 2));
		if (pthread_mutex_init(&prog->philos[i].m_dtime, NULL) != 0)
			return (ft_write_error(prog, 2));
		if (pthread_mutex_init(&prog->philos[i].m_eating, NULL) != 0)
			return (ft_write_error(prog, 2));
		if (pthread_mutex_init(&prog->philos[i].m_timeat, NULL) != 0)
			return (ft_write_error(prog, 2));
		i++;
	}
	return (1);
}

int	ft_destroy_mutex(t_prog *prog)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_destroy(&prog->print) != 0)
		return (ft_write_error(prog, 3));
	while (i < prog->n_philos)
	{
		if (pthread_mutex_destroy(&prog->forks[i].locker) != 0)
			return (ft_write_error(prog, 3));
		if (pthread_mutex_destroy(&prog->philos[i].m_stat) != 0)
			return (ft_write_error(prog, 3));
		if (pthread_mutex_destroy(&prog->philos[i].m_ltime) != 0)
			return (ft_write_error(prog, 3));
		if (pthread_mutex_destroy(&prog->philos[i].m_dtime) != 0)
			return (ft_write_error(prog, 3));
		if (pthread_mutex_destroy(&prog->philos[i].m_eating) != 0)
			return (ft_write_error(prog, 3));
		if (pthread_mutex_destroy(&prog->philos[i].m_timeat) != 0)
			return (ft_write_error(prog, 3));
		i++;
	}
	return (1);
}

int	ft_start_pthreads(t_prog *prog)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	if (pthread_create(&prog->monitor, NULL, &ft_observer, prog))
		return (ft_write_error(prog, 0));
	while (i < prog->n_philos)
	{
		philo = &prog->philos[i];
		if (pthread_create(&philo->p_live, NULL, &ft_routine, philo))
			return (ft_write_error(prog, 0));
		i++;
	}
	return (1);
}

int	ft_join_pthreads(t_prog *prog)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	prog->error = pthread_join(prog->monitor, NULL);
	if (prog->error)
		return (ft_write_error(prog, 1));
	while (i < prog->n_philos)
	{
		philo = &prog->philos[i];
		if (pthread_join(philo->p_live, NULL))
			return (ft_write_error(prog, 1));
		i++;
	}
	return (1);
}
