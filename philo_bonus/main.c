/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/21 16:32:26 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_philo	philo;
	sem_t	*forks;
	int		amount;

	sem_unlink("/forks");
	if (argc < 5 || argc > 6)
		return (1);
	amount = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]);
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	philo.meals_left = -1;
	if (argc == 6)
		philo.meals_left = ft_atoi(argv[5]);
	philo.time_of_death = philo.time_to_die;
	forks = sem_open("/forks", O_CREAT, 644, amount);
	philo.forks = forks;
	ft_fork(&philo, amount);
	while (amount--)
		waitpid(0, 0, 0);
	sem_close(forks);
	sem_unlink("/forks");
}

void	ft_philo(t_philo *philo)
{
	while (1)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
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
