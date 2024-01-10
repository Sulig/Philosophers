/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:34:20 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/10 14:25:37 by sadoming         ###   ########.fr       */
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

static int	ft_start_pthreads(t_prog *prog)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	prog->time = 0;
	while (i < prog->n_philos)
	{
		philo = &prog->t_philos[i];
		if (pthread_create(&philo->p_live, NULL, &ft_print_action, philo))
			return (ft_write_error(prog, 0));
		else
			printf("\033[1;36mN.%zu Start living\n", philo->num);
		i++;
	}
	if (pthread_create(&prog->pthread, NULL, &ft_loop_time, prog))
		return (ft_write_error(prog, 0));
	return (1);
}

static int	ft_join_pthreads(t_prog *prog)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	printf("\033[0;37mJoining pthreads...\n");
	prog->error = pthread_join(prog->pthread, NULL);
	if (prog->error)
		return (ft_write_error(prog, 1));
	while (i < prog->n_philos)
	{
		philo = &prog->t_philos[i];
		if (pthread_join(philo->p_live, NULL))
			return (ft_write_error(prog, 1));
		else
			printf("\033[1;36mN.%zu Finish\n", philo->num);
		i++;
	}
	return (1);
}

int	main(int argc, char **args)
{
	t_prog	t_prog;

	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments!\n", 27);
		return (1);
	}
	if (!ft_check_all(args))
		return (ft_free_prog(&t_prog));
	if (!ft_init_prog(&t_prog, args, argc))
		return (ft_free_prog(&t_prog));
	if (!ft_start_pthreads(&t_prog))
		return (ft_free_prog(&t_prog));
	if (!ft_join_pthreads(&t_prog))
		return (ft_free_prog(&t_prog));
	return (ft_free_prog(&t_prog));
}
