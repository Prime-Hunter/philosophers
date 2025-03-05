/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:26:49 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:26:51 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_phil
{
	int						alive;
	int						index;
	int						eating;
	int						nb_of_meals;
	int						max_meals;
	int						done;
	size_t					last_meal;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					time_to_die;
	pthread_t				id;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
}				t_phil;

typedef struct s_monitor
{
	int			start;
	int			nb_philo;
	int			has_died;
	t_phil		**table;
	pthread_t	id;
}				t_monitor;

int					ft_check_args(int argc, char **args);
int					ft_atoi(const char *nptr);
int					check_all_done(t_phil **table);
int					ft_usleep(size_t milliseconds);
int					launch_threads(t_monitor *monitor);
int					ft_interrupt(t_monitor *monitor, char *msg);
void				stop_threads(t_monitor *monitor);
void				ft_free(t_phil **table);
void				eat(t_phil *philosopher);
void				fsleep(t_phil *philosopher);
void				*routine(void *n);
void				*monitor_routine(void *n);
size_t				ft_timestamp(void);
t_phil				**init_table(int number, char **args);
t_monitor			*init_monitor(char **args);

#endif
