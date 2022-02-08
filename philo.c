/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:25:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/08 17:07:35 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**ft_philocreate(char *argv[])
{
	t_philo	**philos;
	int		number_of_philo;
	int		time_to_eat;
	int		time_to_sleep;
	int		i;

	number_of_philo = ft_atoi(argv[1]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	philos = malloc(sizeof(*philos) * (number_of_philo + 1));
	philos[number_of_philo] = 0;
	i = 0;
	while (i < number_of_philo)
	{
		philos[i] = malloc(sizeof(*philos[i]));
		philos[i]->id = i + 1;
		philos[i]->time_to_eat = time_to_eat;
		philos[i]->time_to_sleep = time_to_sleep;
		philos[i]->last_meal = 0;
		pthread_create(&philos[i]->thread, 0, ft_thread, philos[i]);
		i++;
	}
	ft_neighbours(philos);
	ft_forks(philos, number_of_philo);
	return (philos);
}

void	ft_neighbours(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (i)
			philos[i]->left_philo = philos[i - 1];
		if (philos[i + 1])
			philos[i]->right_philo = philos[i + 1];
		i++;
	}
	philos[0]->left_philo = philos[i - 1];
	philos[i - 1]->right_philo = philos[0];
}

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
