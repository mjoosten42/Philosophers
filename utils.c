/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:45:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/15 13:29:33 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_msleep(t_philo *philo, int ms)
{
	int	target;

	target = ft_gettime() + ms;
	while (target > ft_gettime())
		if (ft_checkdeath(philo))
			return (1);
	return (0);
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
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		result = 10 * result + *str++ - '0';
	return (result);
}
