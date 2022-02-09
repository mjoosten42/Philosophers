/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:25:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/09 15:07:50 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_philoscreate(char *argv[])
{
	pthread_mutex_t	*fork;
	t_philo			*first;
	t_philo			*new;
	t_philo			*prev;
	int				i;

	prev = 0;
	fork = 0;
	i = ft_atoi(argv[1]);
	while (i)
	{
		new = ft_philo_new(argv);
		if (!prev)
			first = new;
		new->id = i;
		new->right_philo = prev;
		new->left_philo = 0;
		if (prev)
			prev->left_philo = new;
		new->right_fork = fork;
		fork = ft_forknew();
		new->left_fork = fork;
		prev = new;
		i--;
	}
	first->right_philo = new;
	new->left_philo = first;
	first->right_fork = fork;
	return (new);
}

t_philo	*ft_philo_new(char *argv[])
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
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

pthread_mutex_t	*ft_forknew(void)
{
	pthread_mutex_t	*new;

	new = malloc(sizeof(*new));
	pthread_mutex_init(new, 0);
	return (new);
}
