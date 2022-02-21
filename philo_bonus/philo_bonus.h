/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:06:55 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/21 16:12:46 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	sem_t		*forks;
	int			id;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_of_death;
	int			meals_left;
}				t_philo;

	//	main.c
void	ft_fork(t_philo *philo, int i);
void	ft_philo(t_philo *philo);

	//	philo.c
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);

	//	utils.c
int		ft_atoi(char *str);
int		ft_gettime(void);
void	ft_msleep(t_philo *philo, int ms);

#endif