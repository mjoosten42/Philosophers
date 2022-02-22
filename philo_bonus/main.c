/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/22 14:34:11 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	philo;
	sem_t	*forks;
	sem_t	*meals;
	int		amount;

	sem_unlink(FORKS);
	sem_unlink(MEALS);
	amount = ft_init(&philo, argc, argv);
	forks = sem_open(FORKS, O_CREAT, 0700, amount);
	meals = sem_open(MEALS, O_CREAT, 0700, amount);
	ft_fork(&philo, amount);
	if (argc == 6)
		ft_monitor(&philo, meals, amount);
	usleep(UINT32_MAX);
}

int	ft_init(t_philo *philo, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		exit(EXIT_FAILURE);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->meals_left = -1;
	if (argc == 6)
		philo->meals_left = ft_atoi(argv[5]);
	philo->time_of_death = philo->time_to_die;
	return (ft_atoi(argv[1]));
}

void	ft_fork(t_philo *philo, int amount)
{
	int	i;

	i = 0;
	ft_gettime();
	while (i++ < amount)
	{
		if (!fork())
		{
			philo->id = i;
			ft_philo(philo);
		}
	}
}

void	ft_philo(t_philo *philo)
{
	sem_t	*forks;
	sem_t	*meals;

	forks = sem_open(FORKS, 0);
	meals = sem_open(MEALS, 0);
	sem_wait(meals);
	while (1)
	{
		printf("%d %d is thinking\n", ft_gettime(), philo->id);
		sem_wait(forks);
		printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
		sem_wait(forks);
		printf("%d %d has taken a fork\n", ft_gettime(), philo->id);
		philo->time_of_death = ft_gettime() + philo->time_to_die;
		if (philo->meals_left > 0)
			philo->meals_left--;
		if (!philo->meals_left)
			sem_post(meals);
		printf("%d %d is eating\n", ft_gettime(), philo->id);
		ft_msleep(philo, philo->time_to_eat);
		sem_post(forks);
		sem_post(forks);
		printf("%d %d is sleeping\n", ft_gettime(), philo->id);
		ft_msleep(philo, philo->time_to_sleep);
	}
}

void	ft_monitor(t_philo *philo, sem_t *meals, int amount)
{
	usleep(1000 * philo->time_to_eat);
	while (amount--)
		sem_wait(meals);
	sem_unlink(FORKS);
	sem_unlink(MEALS);
	kill(0, SIGKILL);
}
