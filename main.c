/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/09 17:08:20 by mjoosten         ###   ########.fr       */
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
	return (arg);
}

	//	To remove
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
