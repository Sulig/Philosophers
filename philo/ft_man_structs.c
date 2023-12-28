/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_man_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:43:12 by sadoming          #+#    #+#             */
/*   Updated: 2023/12/28 13:48:06 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_philo(t_philo *philo, char **args, int argc)
{
	if (argc == 6)
		philo->times_to_eat = ft_atoi(args[5]);
	else
		philo->times_to_eat = -1;
	philo->time_to_die = ft_atos(args[2]);
	philo->time_to_eat = ft_atos(args[3]);
	philo->time_to_sleep = ft_atos(args[4]);
	philo->eating = 0;
	philo->dead = 0;
	philo->activity = "\033[0;34mdoing nothing right now ⚐\n";
}

static void	ft_init_forks(t_fork *forks, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		forks[i].grabed = 0;
		forks[i].num = i + 1;
		i++;
	}
}

void	ft_init_prog(t_program *t_prog, char **args, int argc)
{
	size_t	philos;
	size_t	i;

	i = 0;
	philos = ft_atos(args[1]);
	t_prog->n_philos = philos;
	t_prog->t_philos = ft_calloc(sizeof(t_philo), philos);
	t_prog->t_forks = ft_calloc(sizeof(t_fork), philos);
	ft_init_forks(t_prog->t_forks, t_prog->n_philos);
	while (i < philos)
	{
		ft_init_philo(&t_prog->t_philos[i], args, argc);
		t_prog->t_philos[i].num = i + 1;
		t_prog->t_philos[i].l_fork = t_prog->t_forks[i];
		if (i + 1 == philos)
			t_prog->t_philos[i].r_fork = t_prog->t_forks[0];
		else
			t_prog->t_philos[i].r_fork = t_prog->t_forks[i + 1];
		i++;
	}
}
