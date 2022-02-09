/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:45:02 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/09 12:40:15 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	philo->state = thinking;
	printf("%d %d is thinking\n", ft_gettime(), philo->id);
	while (1)
	{
		if ((philo->right_philo->state == thinking
				|| philo->right_philo->state == sleeping)
			&& (philo->left_philo->state == thinking
				|| philo->left_philo->state == sleeping))
		{
			philo->state = hungry;
			printf("%d %d is hungry\n", ft_gettime(), philo->id);
			pthread_mutex_lock(philo->left_fork);
			printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
			pthread_mutex_lock(philo->right_fork);
			printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
			return ;
		}
	}
}

void	ft_eat(t_philo *philo)
{
	philo->state = eating;
	philo->last_meal = ft_gettime();
	printf("%d %d is eating\n", ft_gettime(), philo->id);
	ft_msleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	philo->state = sleeping;
	printf("%d %d is sleeping\n", ft_gettime(), philo->id);
	ft_msleep(philo->time_to_sleep);
}
