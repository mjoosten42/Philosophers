/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:05:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/01/25 16:29:56 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread(void *arg);
int		ft_gettime(void);

int	main(int argc, char *argv[])
{
	pthread_t		**threads;
	int				philo;
	int				i;

	if (argc < 2)
		return (1);
	philo = ft_atoi(argv[1]);
	threads = malloc(sizeof(*threads) * (philo + 1));
	threads[philo] = 0;
	i = 0;
	while (i < philo)
	{
		threads[i] = malloc(sizeof(pthread_t));
		pthread_create(threads[i], 0, ft_thread, 0);
		i++;
	}
	ft_free_array((void **)threads);
	pthread_exit(0);
}

void	*ft_thread(void *arg)
{
	(void)arg;
	printf("%d Thread\n", ft_gettime());
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
