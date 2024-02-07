/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:29:59 by sadoming          #+#    #+#             */
/*   Updated: 2024/02/07 11:58:15 by sadoming         ###   ########.fr       */
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
	pthread_mutex_t	locker;
}					t_fork;

typedef struct s_philo
{
	size_t			num;
	long			times_to_eat;
	size_t			start_time;
	size_t			last_eat;
	size_t			live_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				eating;
	int				status;
	int				lf_grab;
	int				rf_grab;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_t		p_live;
	pthread_mutex_t	*print;
	pthread_mutex_t	m_ltime;
	pthread_mutex_t	m_dtime;
	pthread_mutex_t	m_eating;
	pthread_mutex_t	m_timeat;
	pthread_mutex_t	m_stat;
}				t_philo;

typedef struct s_prog
{
	int				error;
	int				flag;
	size_t			end_eating;
	size_t			dp;
	size_t			n_philos;
	size_t			*values;
	t_fork			*forks;		
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	print;
}				t_prog;

/* UTILS */
size_t	ft_atos(const char *str);
size_t	ft_gettime(void);
void	ft_usleep(size_t miliseg);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* CHECK, INIT & FREE */
int		ft_check_all(char **args);
int		ft_free_prog(t_prog *prog, int error);
int		ft_init_prog(t_prog *t_prog, char **args, int argc);

int		ft_check_eating_times(t_prog *prog);
int		ft_status_philo(t_philo *philo);

/* MUTEX */
int		ft_init_mutex(t_prog *prog);
int		ft_destroy_mutex(t_prog *prog);
void	ft_grab_forks(t_philo *philo);
void	ft_release_forks(t_philo *philo, int print);

/* PTHREADS */
int		ft_start_pthreads(t_prog *prog);
int		ft_join_pthreads(t_prog *prog);
void	*ft_observer(void *arg);
void	*ft_routine(void *arg);

/* PRINT STATUS && DEBUGG */
void	ft_print_action(t_philo *philo, char *action);
void	ft_print_forks_stat(t_fork *forks, size_t len);
void	ft_print_philo_stat(t_philo *philo);

#endif
