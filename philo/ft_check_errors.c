/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:49:13 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/19 17:25:15 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isacceptable(const char *str)
{
	int	parsed;

	parsed = ft_atos(str);
	if (parsed <= 0)
		return (0);
	else
		return (1);
}

int	ft_check_all(char **args)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
		{
			write(2, "Non digit character detected!\n", 30);
			return (0);
		}
		if (!ft_isacceptable(args[i]))
		{
			write(2, "Value can't be less than 1\n", 27);
			return (0);
		}
		i++;
	}
	return (1);
}
