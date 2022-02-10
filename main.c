/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/10 14:16:37 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			**philos;

	if (argc < 5 || argc > 6)
		return (1);
	philos = ft_philoscreate(argv);
	ft_death(philos);
}

void	*ft_philo(void *arg)
{
	while (1)
	{
		ft_think(arg);
		ft_eat(arg);
		ft_sleep(arg);
	}
	return (arg);
}

void	ft_death(t_philo **philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (philos[i])
		{
			if (philos[i]->time_of_death < ft_gettime())
			{
				while (*philos)
					(*philos++)->died = 1;
				pthread_exit(EXIT_SUCCESS);
			}
			i++;
		}
	}
}
