/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:12:37 by lde-guil          #+#    #+#             */
/*   Updated: 2025/03/04 11:12:40 by lde-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_num(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char **args)
{
	int	i;

	i = 1;
	if (!is_num(args))
	{
		return (0);
	}
	if (argc != 5 && argc != 6)
		return (0);
	if (ft_atoi(args[1]) == 1)
	{
		ft_usleep(ft_atoi(args[2]));
		printf("%ld 1 died\n", ft_timestamp());
		return (0);
	}
	while (args[i] != NULL)
	{
		if (ft_atoi(args[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
