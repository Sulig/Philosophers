/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:29:59 by sadoming          #+#    #+#             */
/*   Updated: 2023/12/29 19:47:46 by sadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				grabed;
	size_t			num;
	pthread_mutex_t	*loker;
}					t_fork;

typedef struct s_philo
{
	size_t		num;
	long		times_to_eat;
	size_t		cron;
	size_t		cron_to_die;
	void		*prog_time;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_think;
	char		*action;
	int			eating;
	int			dead;
	int			g_forks;
	t_fork		l_fork;
	t_fork		r_fork;
	pthread_t	p_live;
}				t_philo;

typedef struct s_prog
{
	int			p_dead;
	int			error;
	int			finish;
	size_t		n_philos;
	t_philo		*t_philos;
	t_fork		*t_forks;
	long long	prog_time;
	pthread_t	time;
}				t_prog;

/* UTILS */
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
size_t	ft_atos(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* CHECK, INIT & FREE */
int		ft_check_all(char **args);
int		ft_free_prog(t_prog *prog);
int		ft_init_prog(t_prog *t_prog, char **args, int argc);

/* PRINT STATUS |DEBUGG| */
void	*ft_print_action(void *philo);
void	ft_print_forks_stat(t_fork *forks, size_t len);
void	ft_print_philo_stat(t_philo *philo);
void	ft_print_stat(t_prog *t_prog);

#endif
