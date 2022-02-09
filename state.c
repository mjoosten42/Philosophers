/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:45:02 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/09 15:39:58 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	ft_state(philo, thinking);
	printf("%d %d is thinking\n", ft_gettime(), philo->id);
	while (1)
	{
		if ((philo->right_philo->state == thinking
				|| philo->right_philo->state == sleeping)
			&& (philo->left_philo->state == thinking
				|| philo->left_philo->state == sleeping))
		{
			ft_state(philo, hungry);
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
	ft_state(philo, eating);
	philo->time_of_death = philo->time_to_die + ft_gettime();
	printf("%d %d is eating\n", ft_gettime(), philo->id);
	ft_msleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_state(philo, sleeping);
	printf("%d %d is sleeping\n", ft_gettime(), philo->id);
	ft_msleep(philo->time_to_sleep);
}

void	ft_state(t_philo *philo, t_state state)
{
	if (philo->state == died)
		pthread_exit(EXIT_SUCCESS);
	philo->state = state;
}
