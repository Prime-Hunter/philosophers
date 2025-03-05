/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:22:59 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:23:01 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	launch_threads(t_monitor *monitor)
{
	t_phil	*philosopher;
	int		i;

	i = 0;
	if (pthread_create(&monitor->id, NULL, monitor_routine, monitor) != 0)
		return (ft_interrupt(monitor, "Error\nCouldn't create threads\n"));
	while (i < monitor->nb_philo)
	{
		philosopher = monitor->table[i];
		if (pthread_create(&philosopher->id, NULL, routine, philosopher) != 0)
			return (ft_interrupt(monitor, "Error\nCouldn't create threads\n"));
		i++;
	}
	i = 0;
	if (pthread_join(monitor->id, NULL) != 0)
		return (ft_interrupt(monitor, "Error\nCouldn't join threads\n"));
	while (i < monitor->nb_philo)
	{
		philosopher = monitor->table[i];
		if (pthread_join(philosopher->id, NULL) != 0)
			return (ft_interrupt(monitor, "Error\nCouldn't join threads\n"));
		i++;
	}
	return (1);
}
