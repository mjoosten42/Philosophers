/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:45:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/15 16:23:49 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_itoa(int nb)
{
	char	*str;
	int		number;
	int		size;

	number = nb;
	size = 1;
	while (nb / 10 && size++)
		nb /= 10;
	str = malloc(size + 1);
	str[size] = 0;
	while (number)
	{
		str[--size] = '0' + number % 10;
		number /= 10;
	}
	return (str);
}

int	ft_atoi(char *str)
{
	char	*start;
	int		result;

	result = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	while (*str == '0')
		str++;
	start = str;
	while (*str >= '0' && *str <= '9')
		result = 10 * result + *str++ - '0';
	if (ft_strcmp(start, ft_itoa(result)))
		return (-1);
	return (result);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

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
