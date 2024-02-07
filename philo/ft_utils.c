/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:14:19 by sadoming          #+#    #+#             */
/*   Updated: 2024/02/07 12:04:02 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	cnt;
	char	*dest;

	dest = (char *) s;
	cnt = 0;
	while (cnt < n)
	{
		dest[cnt] = '\0';
		cnt++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*call;

	call = malloc(count * size);
	if (!call)
		return (NULL);
	ft_bzero(call, count * size);
	return (call);
}

size_t	ft_atos(const char *str)
{
	size_t	cnt;
	size_t	find;

	find = '\0';
	cnt = -1;
	while (str[++cnt] < 33)
		if ((str[cnt] < 9 || str[cnt] > 13) && str[cnt] != ' ')
			return ('\0');
	if (str[cnt] == '-' || str[cnt] == '+')
		cnt++;
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		find *= 10;
		find += str[cnt] - '0';
		cnt++;
	}
	return (find);
}

/*
 * 1 Sec = 1000 Milisec
 * 1 Milisec = 1000 Microseg
 * tv_usec is in microseg, so / 1000 is in miliseg
 */
size_t	ft_gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t miliseg)
{
	size_t	start;

	start = ft_gettime();
	while (ft_gettime() - start < miliseg)
		usleep(25);
}
