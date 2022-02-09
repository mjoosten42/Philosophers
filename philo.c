/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:25:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/09 12:58:44 by mjoosten         ###   ########.fr       */
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
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->last_meal = 0;
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

void	ft_printphilo(t_philo *philo)
{
	int	id;

	id = philo->id;
	do
	{
		printf("---Philo[%d]---\n", philo->id);
	printf("Philo: %p\n", philo);
	printf("Right Philo: %p\n", philo->right_philo);
	printf("Left Philo: %p\n", philo->left_philo);
	printf("Right Fork: %p\n", philo->right_fork);
	printf("Left Fork: %p\n", philo->left_fork);
	philo = philo->right_philo;
}
	while (id != philo->id);
}
