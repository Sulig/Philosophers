/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:34:20 by sadoming          #+#    #+#             */
/*   Updated: 2023/12/27 13:58:00 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_all(char **args)
{
	
}

int	main(int argc, char **args)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments!\n", 27);
		exit(1);
	}
	printf("\033[1;32mOK\n %s", args[2]);
	return (0);
}
