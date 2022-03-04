/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/04 09:58:48 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	**philos;
	t_mutex	print;
	int		args[6];

	if (argc < 5 || argc > 6)
		return (1);
	args[5] = -1;
	while (argc-- > 1)
	{
		args[argc] = ft_atoi(argv[argc]);
		if (args[argc] == -1)
			return (1);
	}
	print.value = 0;
	pthread_mutex_init(&print.mutex, 0);
	pthread_mutex_lock(&print.mutex);
	philos = ft_philoscreate(args, &print);
	if (!philos)
		return (1);
	pthread_mutex_unlock(&print.mutex);
	if (args[5] != -1)
		ft_monitor(philos, &print);
	while (args[1]--)
		pthread_join(philos[args[1]]->thread, NULL);
	ft_free_philos(philos);
}

int	ft_checkdeath(t_philo *philo)
{
	pthread_mutex_lock(&philo->print->mutex);
	if (philo->print->value)
	{
		pthread_mutex_unlock(&philo->print->mutex);
		return (1);
	}
	if (philo->time_of_death < ft_gettime())
	{
		printf("%d %d died\n", ft_gettime(), philo->id);
		philo->print->value = 1;
		pthread_mutex_unlock(&philo->print->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->print->mutex);
	return (0);
}

int	ft_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->print->mutex);
	if (philo->print->value)
	{
		pthread_mutex_unlock(&philo->print->mutex);
		return (1);
	}
	printf(str, ft_gettime(), philo->id);
	pthread_mutex_unlock(&philo->print->mutex);
	return (0);
}

int	ft_monitor(t_philo **philos, t_mutex *print)
{
	int	meals;
	int	i;

	while (1)
	{
		meals = 0;
		i = 0;
		pthread_mutex_lock(&print->mutex);
		if (print->value)
		{
			pthread_mutex_unlock(&print->mutex);
			return (1);
		}
		while (philos[i])
			meals += philos[i++]->meals_left;
		if (!meals)
		{
			print->value = 1;
			pthread_mutex_unlock(&print->mutex);
			return (1);
		}
		pthread_mutex_unlock(&print->mutex);
		usleep(1000);
	}
}
