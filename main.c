/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:24:27 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:24:30 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **args)
{
	t_phil		**table;
	t_monitor	*monitor;

	if (!ft_check_args(argc, args))
		return (0);
	monitor = init_monitor(args);
	table = init_table(monitor->nb_philo, args);
	monitor->table = table;
	if (!launch_threads(monitor))
		return (0);
	ft_free(table);
	free(monitor);
	return (1);
}
