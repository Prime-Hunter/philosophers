/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:16:58 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:17:00 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_monitor	*init_monitor(char **args)
{
	t_monitor	*res;

	res = malloc(sizeof(t_monitor));
	res->nb_philo = ft_atoi(args[1]);
	res->has_died = 0;
	res->start = 0;
	res->writing = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(res->writing, NULL);
	return (res);
}

static t_phil	*init_philo(int i, int etime, int stime, int dtime)
{
	t_phil	*philosopher;

	philosopher = malloc(sizeof(t_phil));
	philosopher->alive = 1;
	philosopher->index = i + 1;
	philosopher->time_to_die = dtime;
	philosopher->time_to_eat = etime;
	philosopher->time_to_sleep = stime;
	philosopher->nb_of_meals = 0;
	philosopher->eating = 0;
	philosopher->last_meal = ft_timestamp();
	philosopher->done = 0;
	philosopher->right_fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philosopher->right_fork, NULL);
	return (philosopher);
}

t_phil	**init_table(t_monitor *m, char **ar)
{
	t_phil	**table;
	t_phil	*phil;
	int		i;

	i = 0;
	table = (t_phil **) malloc(sizeof(t_phil) * m->nb_philo);
	while (i <m->nb_philo)
	{
		phil = init_philo(i, ft_atoi(ar[3]), ft_atoi(ar[4]), ft_atoi(ar[2]));
		if (i > 0)
		{
			table[i - 1]->left_fork = phil->right_fork;
			if (i + 1 == m->nb_philo)
				phil->left_fork = table[0]->right_fork;
		}
		if (ar[5])
			phil->max_meals = ft_atoi(ar[5]);
		phil->writing = m->writing;
		table[i] = phil;
		i++;
	}
	table[i] = NULL;
	return (table);
}
