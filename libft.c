/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:27:49 by mjoosten          #+#    #+#             */
/*   Updated: 2022/01/25 16:28:33 by mjoosten         ###   ########.fr       */
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
