/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:06:55 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/22 14:34:02 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>	//	sem_*
# include <sys/time.h>	//	gettimeofday
# include <signal.h>	//	kill
# include <unistd.h>	//	fork
						//	usleep
# include <stdio.h>		//	printf
# include <stdlib.h>	//	exit

# define FORKS "/forks"
# define MEALS "/meals"

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int			id;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_of_death;
	int			meals_left;
}				t_philo;

	//	main.c
int		ft_init(t_philo *philo, int argc, char **argv);
void	ft_fork(t_philo *philo, int i);
void	ft_philo(t_philo *philo);
void	ft_monitor(t_philo *philo, sem_t *meals, int amount);

	//	utils.c
void	ft_msleep(t_philo *philo, int ms);
int		ft_atoi(char *str);
int		ft_gettime(void);

#endif