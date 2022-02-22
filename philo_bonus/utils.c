/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:54:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/22 13:59:36 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_msleep(t_philo *philo, int ms)
{
	int	target;

	target = ft_gettime() + ms;
	while (target > ft_gettime())
	{
		if (philo->time_of_death < ft_gettime())
		{
			printf("%d %d died\n", ft_gettime(), philo->id);
			sem_unlink(FORKS);
			sem_unlink(MEALS);
			kill(0, SIGKILL);
		}
		usleep(1000);
	}
}

int	ft_atoi(char *str)
{
	int		result;

	result = 0;
	while (*str >= '0' && *str <= '9')
		result = 10 * result + *str++ - '0';
	return (result);
}

int	ft_gettime(void)
{
	static t_timeval	start;
	t_timeval			time;

	if (!start.tv_sec)
		gettimeofday(&start, 0);
	gettimeofday(&time, 0);
	return ((time.tv_sec - start.tv_sec) * 1000
		+ (time.tv_usec - start.tv_usec) / 1000);
}
