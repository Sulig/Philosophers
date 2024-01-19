/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadoming <sadoming@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:29:59 by sadoming          #+#    #+#             */
/*   Updated: 2024/01/19 14:13:55 by sadoming         ###   ########.fr       */
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
	size_t			time_to_think;
	char			*action;
	int				eating;
	int				dead;
	int				lf_grab;
	int				rf_grab;
	int				lf_num;
	int				rf_num;
	t_fork			*forks;
	pthread_t		p_live;
	pthread_mutex_t	*print;
}				t_philo;

typedef struct s_prog
{
	int				error;
	int				dead_flg;
	int				end_flag;
	size_t			end_eating;
	size_t			n_philos;
	size_t			*values;
	t_fork			*forks;		
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	print;
}				t_prog;

/* UTILS */
int		ft_atoi(const char *str);
size_t	ft_atos(const char *str);
size_t	ft_gettime(void);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* CHECK, INIT & FREE */
int		ft_check_all(char **args);
int		ft_free_prog(t_prog *prog, int error);
int		ft_init_prog(t_prog *t_prog, char **args, int argc);
int		ft_check_eating_times(t_prog *prog);
int		ft_kill_philo(t_philo *philo);

/* PTHREADS */
int		ft_init_mutex(t_prog *prog);
int		ft_destroy_mutex(t_prog *prog);
int		ft_start_pthreads(t_prog *prog);
int		ft_join_pthreads(t_prog *prog);
void	ft_release_forks(t_philo *philo, int print);
void	*ft_observer(void *arg);
void	*ft_routine(void *arg);

/* PRINT STATUS && DEBUGG */
void	ft_print_action(t_philo *philo);
void	ft_print_forks_stat(t_fork *forks, size_t len);
void	ft_print_philo_stat(t_philo *philo);
void	ft_print_stat(t_prog *t_prog);

#endif
