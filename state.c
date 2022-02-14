/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:45:02 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/14 16:41:38 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	int	forks;

	forks = 0;
	if (philo->time_of_death != philo->time_to_die)
		ft_printf(philo, "%d %d is thinking\n");
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (!philo->left_fork->value)
		{
			forks++;
			philo->left_fork->value = 1;
			ft_printf(philo, "%d %d has taken a fork\n");
		}
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (!philo->right_fork->value)
		{
			forks++;
			philo->right_fork->value = 1;
			ft_printf(philo, "%d %d has taken a fork\n");
		}
		pthread_mutex_unlock(&philo->right_fork->mutex);
		if (forks == 2)
			return ;
	}
}

void	ft_eat(t_philo *philo)
{
	philo->time_of_death = philo->time_to_die + ft_gettime();
	philo->number_of_times_each_philosopher_must_eat--;
	ft_printf(philo, "%d %d is eating\n");
	ft_msleep(philo, philo->time_to_eat);
	ft_drop(philo->right_fork);
	ft_drop(philo->left_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_printf(philo, "%d %d is sleeping\n");
	ft_msleep(philo, philo->time_to_sleep);
}

void	ft_drop(t_mutex *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->value = 0;
	pthread_mutex_unlock(&fork->mutex);
}
