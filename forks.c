/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:51:20 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/08 17:08:11 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	**ft_forkscreate(int number)
{
	pthread_mutex_t	**forks;
	int				i;

	forks = malloc(sizeof(*forks) * (number + 1));
	forks[number] = 0;
	i = 0;
	while (i < number)
	{
		forks[i] = malloc(sizeof(*forks[i]));
		pthread_mutex_init(forks[i], 0);
		i++;
	}
	return (forks);
}

void	ft_forks(t_philo **philos, int nb)
{
	pthread_mutex_t	**forks;
	int				i;

	forks = ft_forkscreate(nb);
	i = 0;
	while (philos[i])
	{
		if (i)
			philos[i]->left_fork = forks[i - 1];
		philos[i]->right_fork = forks[i];
	}
	philos[0]->left_fork = forks[i - 1];
}
