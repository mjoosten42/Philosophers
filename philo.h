/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:06:55 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/08 17:08:02 by mjoosten         ###   ########.fr       */
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

typedef enum e_state {thinking, hungry, eating, sleeping}	t_state;

typedef struct s_philo
{
	struct s_philo	*left_philo;
	struct s_philo	*right_philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_state			state;
	int				id;
	int				last_meal;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_philo;

	//	main.c
void			*ft_thread(void *arg);

	//	philo.c
t_philo			**ft_philocreate(char *argv[]);
void			ft_neighbours(t_philo **philos);
void			ft_think(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);

	//	forks.c
pthread_mutex_t	**ft_forkscreate(int number);
void			ft_forks(t_philo **philos, int nb);

	//	utils.c
void			ft_free_array(void **array);
int				ft_atoi(char *str);
int				ft_gettime(void);
int				ft_msleep(int ms);

#endif