/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:06:55 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/14 16:34:10 by mjoosten         ###   ########.fr       */
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

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				value;
}					t_mutex;

typedef struct s_philo
{
	pthread_t	thread;
	t_mutex		*print;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	int			id;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_of_death;
	int			number_of_times_each_philosopher_must_eat;
}				t_philo;

	//	main.c
void			*ft_philo(void *arg);
void			ft_printf(t_philo *philo, char *str);
void			ft_death(t_philo *philo);

	//	philo.c
t_philo			**ft_philoscreate(char *argv[], t_mutex *print);
t_philo			*ft_philo_new(char *argv[], t_mutex *print);
t_mutex			*ft_mutex_new(void);
void			ft_drop(t_mutex *fork);

	//	state.c
void			ft_think(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);

	//	utils.c
void			ft_msleep(t_philo *philo, int ms);
int				ft_gettime(void);
int				ft_atoi(char *str);

#endif