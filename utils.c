/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:45:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/14 16:47:39 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_msleep(t_philo *philo, int ms)
{
	int	target;

	target = ft_gettime() + ms;
	while (target > ft_gettime())
	{
		pthread_mutex_lock(&philo->print->mutex);
		if (philo->print->value)
		{
			pthread_mutex_unlock(&philo->print->mutex);
			pthread_exit(0);
		}
		pthread_mutex_unlock(&philo->print->mutex);
		if (philo->time_of_death < ft_gettime())
		{
			pthread_mutex_lock(&philo->print->mutex);
			printf("%d %d died\n", ft_gettime(), philo->id);
			philo->print->value = 1;
			pthread_mutex_unlock(&philo->print->mutex);
			pthread_exit(0);
		}
	}
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

int	ft_atoi(char *str)
{
	int	result;

	result = 0;
	while (*str)
		result = 10 * result + *str++ - '0';
	return (result);
}
