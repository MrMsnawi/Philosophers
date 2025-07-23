/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:51:50 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/23 21:36:34 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutex_forks(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->n_philos)
	{
		if (-1 == pthread_mutex_init(&info->forks[i], NULL))
		{
			j = i - 1;
			while (j >= 0)
				pthread_mutex_destroy(&info->forks[j--]);
			return (1);
		}
	}
	return (0);
}

static int	mutex_init(t_info *info)
{
	if (-1 == pthread_mutex_init(&info->print, NULL))
		return (1);
	if (-1 == pthread_mutex_init(&info->die, NULL))
	{
		pthread_mutex_destroy(&info->print);
		return (1);
	}
	if (-1 == pthread_mutex_init(&info->meal, NULL))
	{
		pthread_mutex_destroy(&info->print);
		pthread_mutex_destroy(&info->die);
		return (1);
	}
	if (-1 == pthread_mutex_init(&info->time, NULL))
	{
		pthread_mutex_destroy(&info->print);
		pthread_mutex_destroy(&info->die);
		pthread_mutex_destroy(&info->time);
		return (1);
	}
	if (mutex_forks(info))
		return (1);
	return (0);
}

int	data_init(t_info *info, char **args)
{
	if (!info || !args)
		return (1);
	info->n_philos = (int)ft_atol(args[1]);
	if (info->n_philos > 200)
		return (error("Number of philosophers greater that 200!"));
	if (info->n_philos <= 0)
		return (error("Number of philosophers must be greater than 0!"));
	info->time_to_die = (int)ft_atol(args[2]);
	info->time_to_eat = (int)ft_atol(args[3]);
	info->time_to_sleep = (int)ft_atol(args[4]);
	info->died = 0;
	if (info->time_to_die < 60 || info->time_to_eat < 60
		|| info->time_to_sleep < 60)
		return (error("Minimum of time to die-eat-sleep is 60 ms!"));
	if (args[5])
		info->n_meals = (int)ft_atol(args[5]);
	else
		info->n_meals = -1;
	if (info->n_meals == 0)
		return (error("Number of meals must be greater than 0!"));
	return (mutex_init(info));
}
