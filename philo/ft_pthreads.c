/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthreads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:28:03 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/16 20:20:44 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_write_error(t_prog *prog, int num)
{
	prog->error = 1;
	if (num == 0)
		write(2, "Couldn't create a thread!\n", 26);
	if (num == 1)
		write(2, "Couldn't join the thread!\n", 26);
	return (0);
}

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
	philo->action = "\033[1;31mis DEAD ☠️  ";
	ft_print_action(philo);
	//unlock mutex?
	//unlock forks?
	return (NULL);
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
