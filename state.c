/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:45:02 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/15 15:41:02 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_think(t_philo *philo)
{
	int	forks;

	forks = 0;
	if (ft_printf(philo, "%d %d is thinking\n"))
		return (1);
	if (philo->time_of_death == philo->time_to_die && philo->id % 2)
		if (ft_msleep(philo, philo->time_to_eat / 2))
			return (1);
	while (1)
	{
		if (ft_checkdeath(philo))
			return (1);
		if (ft_take(philo->left_fork))
			if (++forks && ft_printf(philo, "%d %d has taken a fork\n"))
				return (1);
		if (ft_take(philo->right_fork))
			if (++forks && ft_printf(philo, "%d %d has taken a fork\n"))
				return (1);
		if (forks == 2)
			return (0);
	}
}

int	ft_eat(t_philo *philo)
{
	philo->time_of_death = philo->time_to_die + ft_gettime();
	philo->meals_left--;
	if (ft_printf(philo, "%d %d is eating\n"))
		return (1);
	if (ft_msleep(philo, philo->time_to_eat))
		return (1);
	ft_drop(philo->right_fork);
	ft_drop(philo->left_fork);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_printf(philo, "%d %d is sleeping\n"))
		return (1);
	if (ft_msleep(philo, philo->time_to_sleep))
		return (1);
	return (0);
}

int	ft_take(t_mutex *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (!fork->value)
	{
		fork->value = 1;
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

int	ft_drop(t_mutex *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->value = 0;
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}
