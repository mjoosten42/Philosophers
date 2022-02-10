/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:06:55 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/10 15:46:32 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval	t_timeval;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				istaken;
}					t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	int			id;
	int			died;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_of_death;
	int			number_of_times_each_philosopher_must_eat;
}				t_philo;

	//	main.c
void			*ft_philo(void *arg);
void			ft_death(t_philo **philos);

	//	philo.c
t_philo			**ft_philoscreate(char *argv[]);
t_philo			*ft_philo_new(char *argv[]);
t_fork			*ft_fork_new(void);

	//	state.c
void			ft_think(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);

	//	utils.c
void			ft_free_array(void **array);
int				ft_atoi(char *str);
int				ft_gettime(void);
void			ft_msleep(int ms);

#endif