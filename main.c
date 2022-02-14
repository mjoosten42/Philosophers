/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/14 16:33:59 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	**philos;
	t_mutex	print;

	if (argc < 5 || argc > 6)
		return (1);
	print.value = 0;
	pthread_mutex_init(&print.mutex, 0);
	pthread_mutex_lock(&print.mutex);
	philos = ft_philoscreate(argv, &print);
	pthread_mutex_unlock(&print.mutex);
	pthread_exit(EXIT_SUCCESS);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->print->mutex);
	pthread_mutex_unlock(&philo->print->mutex);
	ft_printf(philo, "%d %d is thinking\n");
	if (!(philo->id % 2))
		ft_msleep(philo, philo->time_to_eat);
	while (1)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (arg);
}

void	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->print->mutex);
	if (philo->print->value)
	{
		pthread_mutex_unlock(&philo->print->mutex);
		pthread_exit(0);
	}
	printf(str, ft_gettime(), philo->id);
	pthread_mutex_unlock(&philo->print->mutex);
}
