/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:29:59 by sadoming          #+#    #+#             */
/*   Updated: 2023/12/27 13:57:57 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_philo
{
	size_t		num;
	int			eating;
	int			dead;
}				t_philo;

typedef struct	s_program
{
	int			p_dead;
	t_philo		*t_philos;
}				t_program;

#endif
