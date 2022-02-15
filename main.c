/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/15 13:29:56 by mjoosten         ###   ########.fr       */
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
	args[5] = 0;
	while (argc--)
		args[argc] = ft_atoi(argv[argc]);
	print.value = 0;
	pthread_mutex_init(&print.mutex, 0);
	pthread_mutex_lock(&print.mutex);
	philos = ft_philoscreate(args, &print);
	pthread_mutex_unlock(&print.mutex);
	while (args[1]--)
		pthread_join(philos[args[1]]->thread, NULL);
	system("leaks philo");
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->print->mutex);
	pthread_mutex_unlock(&philo->print->mutex);
	while (1)
	{
		if (ft_think(philo))
			return (NULL);
		if (ft_eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
	}
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
	usleep(1000);
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
