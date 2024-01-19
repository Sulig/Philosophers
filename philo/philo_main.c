/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:34:20 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/19 11:38:55 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **args)
{
	t_prog	prog;

	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments!\n", 27);
		return (1);
	}
	if (!ft_check_all(args))
		return (ft_free_prog(&prog, 1));
	if (!ft_init_prog(&prog, args, argc))
		return (ft_free_prog(&prog, 1));
	if (!ft_start_pthreads(&prog))
		return (ft_free_prog(&prog, 1));
	if (!ft_join_pthreads(&prog))
		return (ft_free_prog(&prog, 1));
	return (ft_free_prog(&prog, 0));
}
