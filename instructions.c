/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:20:58 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:21:01 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork);
	printf("%ld %i has taken a fork\n", ft_timestamp(), philosopher->index);
	pthread_mutex_lock(philosopher->left_fork);
	printf("%ld %i has taken a fork\n", ft_timestamp(), philosopher->index);
	philosopher->eating = 1;
	printf("%ld %i is eating\n", ft_timestamp(), philosopher->index);
	ft_usleep(philosopher->time_to_eat);
	philosopher->eating = 0;
	philosopher->nb_of_meals += 1;
	philosopher->last_meal = ft_timestamp();
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}

void	fsleep(t_phil *philosopher)
{
	printf("%ld %i is sleeping\n", ft_timestamp(), philosopher->index);
	ft_usleep(philosopher->time_to_sleep);
}

void	*routine(void *n)
{
	t_phil	*self;

	self = n;
	if (self->index % 2 == 0)
		usleep(100);
	while (self->alive)
	{
		eat(self);
		fsleep(self);
		printf("%ld %i is thinking\n", ft_timestamp(), self->index);
		if (self->max_meals && self->nb_of_meals >= self->max_meals)
			break ;
	}
	self->done = 1;
	return (NULL);
}

void	*monitor_routine(void *n)
{
	t_monitor	*s;
	int			i;

	s = n;
	while (!(s->has_died))
	{
		i = 0;
		if (check_all_done(s->table))
			s->has_died = 1;
		while (i < s->nb_philo)
		{
			if (s->table[i]->time_to_die + s->table[i]->last_meal
				< ft_timestamp()
				&& !s->table[i]->eating && !s->table[i]->done)
			{
				printf("%ld %i died\n", ft_timestamp(), s->table[i]->index);
				s->has_died = 1;
				break ;
			}
			i++;
		}
	}
	stop_threads(s);
	return (NULL);
}
