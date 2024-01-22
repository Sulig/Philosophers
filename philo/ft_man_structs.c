/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_man_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:10:32 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/22 20:59:48 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_prog(t_prog *prog, int error)
{
	size_t	i;

	i = 0;
	if (prog->philos)
	{
		while (i < prog->n_philos)
		{
			ft_release_forks(&prog->philos[i], 0);
			i++;
		}
		if (!ft_destroy_mutex(prog))
			error = 1;
		free(prog->philos);
	}
	if (prog->forks)
		free(prog->forks);
	if (prog->values)
		free(prog->values);
	prog->philos = NULL;
	prog->forks = NULL;
	prog->values = NULL;
	prog->error = error;
	return (prog->error);
}

static int	ft_init_callocs(t_prog *prog, char **args, int argc)
{
	int		i;

	i = -1;
	prog->values = ft_calloc(sizeof(size_t), argc);
	if (!prog->values)
		return (ft_free_prog(prog, 1));
	while (++i < argc - 1)
		prog->values[i] = ft_atos(args[i + 1]);
	prog->philos = ft_calloc(sizeof(t_philo), prog->values[0]);
	if (!prog->philos)
		return (ft_free_prog(prog, 1));
	prog->forks = ft_calloc(sizeof(t_fork), prog->values[0]);
	if (!prog->forks)
		return (ft_free_prog(prog, 1));
	prog->error = 0;
	prog->dead_flg = 0;
	prog->end_flag = 0;
	prog->n_philos = prog->values[0];
	return (1);
}

static void	ft_init_all(t_prog *prog)
{
	size_t	i;
	char	*acction;

	i = 0;
	acction = "\033[0;34mis doing nothing right now ⚐";
	while (i < prog->n_philos)
	{
		prog->forks[i].grabed = 0;
		prog->philos[i].dead = 0;
		prog->philos[i].eating = 0;
		prog->philos[i].lf_grab = 0;
		prog->philos[i].rf_grab = 0;
		prog->philos[i].action = acction;
		prog->philos[i].print = &prog->print;
		prog->philos[i].start_time = ft_gettime();
		prog->philos[i].live_time = ft_gettime() - prog->philos[i].start_time;
		prog->philos[i].last_eat = prog->philos[i].live_time;
		prog->philos[i].forks = prog->forks;
		prog->philos[i].lf_num = i;
		if (i + 1 == prog->n_philos)
			prog->philos[i].rf_num = 0;
		else
			prog->philos[i].rf_num = i + 1;
		i++;
	}
}

int	ft_init_prog(t_prog *prog, char **args, int argc)
{
	size_t	i;

	i = 0;
	if (!ft_init_callocs(prog, args, argc))
		return (ft_free_prog(prog, 1));
	while (i < prog->n_philos)
	{
		prog->philos[i].num = i + 1;
		prog->forks[i].num = prog->philos[i].num;
		if (argc == 6)
			prog->philos[i].times_to_eat = prog->values[4];
		else
			prog->philos[i].times_to_eat = -1;
		prog->philos[i].time_to_die = prog->values[1];
		prog->philos[i].time_to_eat = prog->values[2];
		prog->philos[i].time_to_sleep = prog->values[3];
		if (prog->values[1] > prog->values[3])
			prog->philos[i].time_to_think = prog->values[3] - prog->values[1];
		if (prog->values[1] < prog->values[3])
			prog->philos[i].time_to_think = prog->values[1] - prog->values[3];
		i++;
	}
	ft_init_all(prog);
	return (ft_init_mutex(prog));
}
