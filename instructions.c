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
	ft_write(philosopher, ft_timestamp(), "has taken a fork");
	pthread_mutex_lock(philosopher->left_fork);
	ft_write(philosopher, ft_timestamp(), "has taken a fork");
	philosopher->eating = 1;
	ft_write(philosopher, ft_timestamp(), "is eating");
	ft_usleep(philosopher->time_to_eat);
	philosopher->eating = 0;
	philosopher->nb_of_meals += 1;
	philosopher->last_meal = ft_timestamp();
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}

void	fsleep(t_phil *philosopher)
{
	ft_write(philosopher, ft_timestamp(), "is sleeping");
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
		if (self->alive)
			eat(self);
		if (self->alive)
			fsleep(self);
		if (self->alive)
			ft_write(self, ft_timestamp(), "is thinking");
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
		s->has_died = check_all_done(s->table);
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
	pthread_mutex_lock(s->writing);
	stop_threads(s);
	pthread_mutex_unlock(s->writing);
	return (NULL);
}
