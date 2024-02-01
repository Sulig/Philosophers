/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:40:04 by sadoming          #+#    #+#             */
/*   Updated: 2024/02/01 20:00:33 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->m_ltime);
	philo->live_time = ft_gettime() - philo->start_time;
	pthread_mutex_lock(philo->print);
	printf("\033[1;37m%zu ", philo->live_time);
	printf("\033[38;5;%zum%zu %s\n", philo->num, philo->num, action);
	pthread_mutex_unlock(&philo->m_ltime);
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
	size_t	for_die;

	pthread_mutex_lock(philo->print);
	printf("\033[1;34m\n~ Philosopher |%zu| ~ \t", philo->num);
	printf("\033[1;37mStatus:\t");
	if (!philo->status)
		printf("\033[1;31mDEAD\033[1;37m\n\n");
	else
		printf("\033[1;32mALIVE\033[0;37m\n\n");
	printf(" Live time:      |%zu|\n", philo->live_time);
	printf(" Time to die:    |%zu|\n", philo->time_to_die);
	printf(" Last eating on: |%zu|\n", philo->last_eat);
	philo->time_to_die += philo->last_eat;
	if (philo->live_time < philo->time_to_die)
		for_die = philo->time_to_die - philo->live_time;
	else
		for_die = 0;
	printf(" Will live |%zu| mls more\n", for_die);
	printf(" Philosopher must eat");
	printf(" |%ld| times\n\n", philo->times_to_eat);
	ft_print_forks_stat(philo->l_fork, 1);
	ft_print_forks_stat(philo->r_fork, 1);
	pthread_mutex_unlock(philo->print);
}
