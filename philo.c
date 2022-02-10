/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:25:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/10 14:16:33 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**ft_philoscreate(char *argv[])
{
	t_philo	**philos;
	t_fork	*fork;
	int		number_of_philo;
	int		i;

	fork = 0;
	i = 0;
	number_of_philo = ft_atoi(argv[1]);
	philos = malloc(sizeof(*philos) * (number_of_philo + 1));
	while (i < number_of_philo)
	{
		philos[i] = ft_philo_new(argv);
		philos[i]->id = i + 1;
		philos[i]->right_fork = fork;
		fork = ft_fork_new();
		philos[i]->left_fork = fork;
		i++;
	}
	philos[0]->right_fork = fork;
	return (philos);
}

t_philo	*ft_philo_new(char *argv[])
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	philo->died = 0;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philo->number_of_times_each_philosopher_must_eat = 0;
	philo->time_of_death = philo->time_to_die;
	pthread_create(&philo->thread, 0, ft_philo, philo);
	return (philo);
}

t_fork	*ft_fork_new(void)
{
	t_fork	*new;

	new = malloc(sizeof(*new));
	pthread_mutex_init(&new->mutex, 0);
	new->istaken = 0;
	return (new);
}
