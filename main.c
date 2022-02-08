/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/08 12:55:30 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	**ft_forkscreate(int number);
t_philo			**ft_philocreate(char *argv[], pthread_mutex_t **forks);
void			*ft_thread(void *arg);

int	main(int argc, char *argv[])
{
	pthread_mutex_t	**forks;
	t_philo			**philo;
	int				i;

	if (argc < 5 || argc > 6)
		return (1);
	forks = ft_forkscreate(ft_atoi(argv[1]));
	philo = ft_philocreate(argv, forks);
	while (1)
	{
		i = 0;
		while (philo[i])
		{
			if (philo[i]->last_meal + philo[i]->time_to_die < ft_gettime())
			{
				printf("%d %d died\n", ft_gettime(), philo[i]->id);
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
		pthread_mutex_lock(philo->left_fork);
		printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
		philo->last_meal = ft_gettime();
		printf("%d %d is eating\n", ft_gettime(), philo->id);
		ft_msleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%d %d is sleeping\n", ft_gettime(), philo->id);
		ft_msleep(philo->time_to_sleep);
		printf("%d %d is thinking\n", ft_gettime(), philo->id);
		ft_msleep(1000);
	}
	return (0);
}

t_philo	**ft_philocreate(char *argv[], pthread_mutex_t **forks)
{
	t_philo		**philo;
	int			number_of_philo;
	int			i;

	number_of_philo = ft_atoi(argv[1]);
	philo = malloc(sizeof(*philo) * (number_of_philo + 1));
	philo[number_of_philo] = 0;
	i = 0;
	while (i < number_of_philo)
	{
		philo[i] = malloc(sizeof(*philo[i]));
		if (i)
			philo[i]->left_fork = forks[i - 1];
		else
			philo[i]->left_fork = forks[number_of_philo - 1];
		philo[i]->right_fork = forks[i];
		philo[i]->id = i + 1;
		philo[i]->time_to_die = ft_atoi(argv[2]);
		philo[i]->time_to_eat = ft_atoi(argv[3]);
		philo[i]->time_to_sleep = ft_atoi(argv[4]);
		philo[i]->last_meal = 0;
		pthread_create(&philo[i]->thread, 0, ft_thread, philo[i]);
		i++;
	}
	return (philo);
}

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
