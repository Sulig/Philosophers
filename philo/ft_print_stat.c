/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:40:04 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/17 13:43:09 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(t_philo *philo)
{
	philo->live_time = ft_gettime() - philo->start_time;
	pthread_mutex_lock(philo->print);
	printf("\033[1;37m%zu %zu %s\n", philo->live_time, philo->num, philo->action);
	pthread_mutex_unlock(philo->print);
}

void	ft_print_forks_stat(t_fork *forks, size_t len)
{
	size_t	i;

	i = 0;
	printf(" ~ Forks ~\n Number of forks: %zu\n\n", len);
	while (i < len)
	{
		printf(" ~ Fork N.%zu\t", forks[i].num);
		if (forks[i].grabed)
			printf("🔴\n");
		else
			printf("🟢\n");
		i++;
	}
}

void	ft_print_philo_stat(t_philo *philo)
{
	size_t	fork;

	printf("\033[1;34m ~ Philosopher |%zu| ~ \t", philo->num);
	printf("\033[1;37mStatus:\t");
	if (philo->dead)
		printf("\033[1;31mDEAD\033[1;37m\n");
	else
		printf("\033[1;32mALIVE\033[0;37m\n");
	printf("\n Graved forks = %i\tForks ->\n", philo->g_forks);
	fork = philo->l_fork.num;
	printf(" On left, philo has N.%zu fork\n", fork);
	fork = philo->r_fork.num;
	printf(" On right, philo has N.%zu fork\n", fork);
	printf(" * Live time:   |%zu|\n", philo->live_time);
	printf("\n Philosopher must eat");
	printf(" |%ld| times\n", philo->times_to_eat);
	printf("\n Philosofer Action:\n");
	printf(" N.%zu %s\n", philo->num, philo->action);
}

void	ft_print_stat(t_prog *t_prog)
{
	size_t	i;
	int		deaths;	

	i = 0;
	deaths = 0;
	printf("\033[1;35m ~ Status ~\n\n");
	printf("\033[1;37m Number of philos: %zu\n", t_prog->n_philos);
	printf("~~~~~~~~~~~~~~~\n\n");
	while (i < t_prog->n_philos)
	{
		deaths += t_prog->philos[i].dead;
		ft_print_philo_stat(&t_prog->philos[i]);
		printf("\033[1;35m~~~~~~~~~~~~~~~~~\n\033[1;37m\n");
		i++;
	}
	printf("\033[1;34mFinal:\t");
	if (!deaths)
		printf("\033[1;32mNo one is dead :D\n");
	else if (deaths == 1)
		printf("\033[1;33mOne philo is DEAD\n");
	else
		printf("\033[1;31mMore than one philo is DEAD!\n");
	printf("\033[1;35m~~~~~~~~~~~~~\033[0;37m\n");
}
