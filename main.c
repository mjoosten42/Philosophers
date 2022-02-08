/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/08 16:20:42 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			**philos;
	int				time_to_die;
	int				i;

	if (argc < 5 || argc > 6)
		return (1);
	philos = ft_philocreate(argv);
	time_to_die = ft_atoi(argv[2]);
	while (1)
	{
		i = 0;
		while (philos[i])
		{
			if (philos[i]->last_meal + time_to_die < ft_gettime())
			{
				printf("%d %d died\n", ft_gettime(), philos[i]->id);
				exit(EXIT_SUCCESS);
			}
			i++;
		}
	}
	pthread_exit(EXIT_SUCCESS);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (0);
}
