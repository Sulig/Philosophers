/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_man_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:43:12 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/02 18:41:07 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_philo(t_prog *prog, t_philo *philo, char **args, int argc)
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
	philo->cron = 0;
	philo->cron_to_die = 0;
	philo->g_forks = 0;
	philo->action = "\033[0;34mis doing nothing right now ⚐";
	philo->prog_time = &prog->time;
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

int	ft_free_prog(t_prog *prog)
{
	if (prog->t_philos)
		free(prog->t_philos);
	if (prog->t_forks)
		free(prog->t_forks);
	prog->t_philos = NULL;
	prog->t_forks = NULL;
	return (prog->error);
}

int	ft_init_prog(t_prog *t_prog, char **args, int argc)
{
	size_t	philos;
	size_t	i;

	i = 0;
	philos = ft_atos(args[1]);
	t_prog->n_philos = philos;
	t_prog->t_philos = ft_calloc(sizeof(t_philo), philos);
	if (!t_prog->t_philos)
		return (0);
	t_prog->t_forks = ft_calloc(sizeof(t_fork), philos);
	if (!t_prog->t_forks)
		return (ft_free_prog(t_prog));
	ft_init_forks(t_prog->t_forks, t_prog->n_philos);
	while (i < philos)
	{
		ft_init_philo(t_prog, &t_prog->t_philos[i], args, argc);
		t_prog->t_philos[i].num = i + 1;
		t_prog->t_philos[i].l_fork = t_prog->t_forks[i];
		if (i + 1 == philos)
			t_prog->t_philos[i].r_fork = t_prog->t_forks[0];
		else
			t_prog->t_philos[i].r_fork = t_prog->t_forks[i + 1];
		i++;
	}
	return (1);
}
