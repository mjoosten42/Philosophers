/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:41:10 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/21 16:23:29 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_think(t_philo *philo)
{
	printf("%d %d is thinking\n", ft_gettime(), philo->id);
	sem_wait(philo->forks);
	printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
	sem_wait(philo->forks);
	printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
}

void	ft_eat(t_philo *philo)
{
	philo->time_of_death = ft_gettime() + philo->time_to_die;
	if (philo->meals_left > 0)
		philo->meals_left--;
	printf("%d %d is eating\n", ft_gettime(), philo->id);
	ft_msleep(philo, philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	ft_sleep(t_philo *philo)
{
	printf("%d %d is sleeping\n", ft_gettime(), philo->id);
	ft_msleep(philo, philo->time_to_sleep);
}
