/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:35:45 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:35:46 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_interrupt(t_monitor *monitor, char *msg)
{
	stop_threads(monitor);
	ft_free(monitor->table);
	printf("%s", msg);
	return (0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_timestamp();
	while ((ft_timestamp() - start) < milliseconds)
		usleep(500);
	return (0);
}
