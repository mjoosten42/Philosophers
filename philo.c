/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:25:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/14 16:25:21 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**ft_philoscreate(char *argv[], t_mutex *print)
{
	t_philo	**philos;
	t_mutex	*fork;
	int		number_of_philo;
	int		i;

	fork = 0;
	i = 0;
	number_of_philo = ft_atoi(argv[1]);
	philos = malloc(sizeof(*philos) * number_of_philo);
	while (i < number_of_philo)
	{
		philos[i] = ft_philo_new(argv, print);
		philos[i]->id = i + 1;
		philos[i]->left_fork = fork;
		fork = ft_mutex_new();
		philos[i]->right_fork = fork;
		i++;
	}
	philos[0]->left_fork = fork;
	while (i--)
		pthread_create(&philos[i]->thread, 0, ft_philo, philos[i]);
	return (philos);
}

t_philo	*ft_philo_new(char *argv[], t_mutex *print)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		pthread_exit(0);
	philo->print = print;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philo->number_of_times_each_philosopher_must_eat = 0;
	philo->time_of_death = philo->time_to_die;
	return (philo);
}

t_mutex	*ft_mutex_new(void)
{
	t_mutex	*new;

	new = malloc(sizeof(*new));
	if (!new)
		pthread_exit(0);
	pthread_mutex_init(&new->mutex, 0);
	new->value = 0;
	return (new);
}
