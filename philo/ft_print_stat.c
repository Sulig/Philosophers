/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:40:04 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/19 19:10:30 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	philo->live_time = ft_gettime() - philo->start_time;
	printf("\033[1;37m%zu ", philo->live_time);
	printf("\033[38;5;%zum%zu %s\n", philo->num, philo->num, philo->action);
	pthread_mutex_unlock(philo->print);
}

void	ft_print_forks_stat(t_fork *forks, size_t len)
{
	size_t	i;

	i = 0;
	if (len > 1)
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
	printf("\033[1;34m\n~ Philosopher |%zu| ~ \t", philo->num);
	printf("\033[1;37mStatus:\t");
	if (philo->dead)
		printf("\033[1;31mDEAD\033[1;37m\n");
	else
		printf("\033[1;32mALIVE\033[0;37m\n");
	printf("\n Live time:   |%Zu|\n", philo->live_time);
	printf("~ %zu Sice last eating...\n", philo->last_eat);
	printf(" Philosopher must eat");
	printf(" |%ld| times\n\n", philo->times_to_eat);
	ft_print_forks_stat(&philo->forks[philo->lf_num], 1);
	ft_print_forks_stat(&philo->forks[philo->rf_num], 1);
	if (philo->lf_grab && philo->rf_grab)
		printf("\033[1;32m Ready to eat some 🍝 \033[1;37m\n");
	ft_print_action(philo);
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
