/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:45:02 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/10 15:47:35 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	printf("%d %d is thinking\n", ft_gettime(), philo->id);
	while (1)
	{
		if (philo->died)
		{
			printf("%d %d died\n", ft_gettime(), philo->id);
			pthread_exit(EXIT_SUCCESS);
		}
		pthread_mutex_lock(&philo->left_fork->mutex);
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (!philo->left_fork->istaken && !philo->right_fork->istaken)
		{
			philo->left_fork->istaken = 1;
			philo->right_fork->istaken = 1;
			printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
			printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
			pthread_mutex_unlock(&philo->left_fork->mutex);
			pthread_mutex_unlock(&philo->right_fork->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
}

void	ft_eat(t_philo *philo)
{
	philo->time_of_death = philo->time_to_die + ft_gettime();
	philo->number_of_times_each_philosopher_must_eat--;
	printf("%d %d is eating\n", ft_gettime(), philo->id);
	ft_msleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->left_fork->istaken = 0;
	philo->right_fork->istaken = 0;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	ft_sleep(t_philo *philo)
{
	printf("%d %d is sleeping\n", ft_gettime(), philo->id);
	ft_msleep(philo->time_to_sleep);
}
