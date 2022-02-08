/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:45:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/08 16:41:20 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_array(void **array)
{
	void	**start;

	if (!array)
		return ;
	start = array;
	while (*array)
		free(*array++);
	free(start);
}

int	ft_atoi(char *str)
{
	int	result;

	result = 0;
	while (*str)
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

int	ft_msleep(int ms)
{
	return (usleep(1000 * ms));
}
