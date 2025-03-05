/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:33:10 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:33:11 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_phil **table)
{
	int	i;

	i = 0;
	while (table[i] != NULL)
	{
		pthread_mutex_destroy(table[i]->right_fork);
		free(table[i]->right_fork);
		free(table[i]);
		i++;
	}
	free(table);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		result *= 10;
		result += (*nptr - '0');
		nptr++;
	}
	return ((int) result * sign);
}

size_t	ft_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	stop_threads(t_monitor *monitor)
{
	int		i;
	t_phil	**table;

	i = 0;
	table = monitor->table;
	while (i < monitor->nb_philo)
	{
		if (table[i] != NULL)
			table[i]->alive = 0;
		i++;
	}
}

int	check_all_done(t_phil **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		if (table[i]->done == 0)
			return (0);
		i++;
	}
	return (1);
}
