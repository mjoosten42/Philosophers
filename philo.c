/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:25:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/15 16:17:34 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->print->mutex);
	pthread_mutex_unlock(&philo->print->mutex);
	while (1)
	{
		if (ft_think(philo))
			return (NULL);
		if (ft_eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
	}
}

void	*ft_free_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (philos[i]->right_fork)
			free(philos[i]->right_fork);
		free(philos[i]);
		i++;
	}
	free(philos);
	return (NULL);
}

t_philo	**ft_philoscreate(int *args, t_mutex *print)
{
	t_philo	**philos;
	t_mutex	*fork;
	int		i;

	fork = 0;
	philos = malloc(sizeof(*philos) * (args[1] + 1));
	if (!philos)
		return (NULL);
	philos[args[1]] = 0;
	i = -1;
	while (i++ < args[1] - 1)
	{
		philos[i] = ft_philo_new(args, print);
		if (!philos[i])
			return (ft_free_philos(philos));
		philos[i]->id = i + 1;
		philos[i]->left_fork = fork;
		fork = ft_mutex_new();
		philos[i]->right_fork = fork;
		if (!fork)
			return (ft_free_philos(philos));
		pthread_create(&philos[i]->thread, 0, ft_philo, philos[i]);
	}
	philos[0]->left_fork = fork;
	return (philos);
}

t_philo	*ft_philo_new(int *args, t_mutex *print)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (NULL);
	philo->print = print;
	philo->time_to_die = args[2];
	philo->time_to_eat = args[3];
	philo->time_to_sleep = args[4];
	philo->time_of_death = philo->time_to_die;
	philo->meals_left = args[5];
	return (philo);
}

t_mutex	*ft_mutex_new(void)
{
	t_mutex	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	pthread_mutex_init(&new->mutex, NULL);
	new->value = 0;
	return (new);
}
