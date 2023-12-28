/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:34:20 by sadoming          #+#    #+#             */
/*   Updated: 2023/12/28 13:48:26 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **args)
{
	t_program	t_prog;

	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments!\n", 27);
		exit(1);
	}
	if (!ft_check_all(args))
		exit(1);
	ft_init_prog(&t_prog, args, argc);
	if (!t_prog.t_philos)
		exit(1);
	ft_print_stat(&t_prog);
	ft_print_forks_stat(t_prog.t_forks, t_prog.n_philos);
	return (0);
}
