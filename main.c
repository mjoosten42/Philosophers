/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/09 12:59:09 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*philos;

	if (argc < 5 || argc > 6)
		return (1);
	philos = ft_philoscreate(argv);
	pthread_exit(EXIT_SUCCESS);
}

void	*ft_philo(void *arg)
{
	while (1)
	{
		ft_think(arg);
		ft_eat(arg);
		ft_sleep(arg);
	}
	return (0);
}
