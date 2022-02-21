/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:06:55 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/21 10:10:29 by mjoosten         ###   ########.fr       */
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
	int			meals_left;
}				t_philo;

	//	main.c
int		ft_checkdeath(t_philo *philo);
int		ft_printf(t_philo *philo, char *str);
int		ft_monitor(t_philo **philos, t_mutex *print);

	//	philo.c
void	*ft_philo(void *arg);
void	*ft_free_philos(t_philo **philos);
t_philo	**ft_philoscreate(int *args, t_mutex *print);
t_philo	*ft_philo_new(int *args, t_mutex *print);
t_mutex	*ft_mutex_new(void);

	//	state.c
int		ft_think(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_take(t_mutex *fork);
int		ft_drop(t_mutex *fork);

	//	utils.c
char	*ft_itoa(int nb);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_msleep(t_philo *philo, int ms);
int		ft_gettime(void);

#endif