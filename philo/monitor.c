/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:47:36 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 21:18:24 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_n_meals(t_info *info)
{
	int	i;
	int	philos;

	ft_mutex_lock(info, &info->meal);
	i = 0;
	philos = 0;
	while (i < info->n_philos)
	{
		if (info->philos[i].n_meals >= info->n_meals)
			philos++;
		i++;
	}
	pthread_mutex_unlock(&info->meal);
	if (philos == info->n_philos)
		return (1);
	return (0);
}

static void	died_f(t_info *info)
{
	pthread_mutex_lock(&info->die);
	info->died = 1;
	pthread_mutex_unlock(&info->die);
}

int	monitor(t_info *info)
{
	int		i;
	time_t	l_meal;

	while (1)
	{
		if (info->n_meals != -1 && check_n_meals(info) == 1)
			return (1);
		(1) && (i = -1, usleep(500));
		while (++i < info->n_philos)
		{
			pthread_mutex_lock(&info->meal);
			l_meal = info->philos[i].last_meal;
			pthread_mutex_unlock(&info->meal);
			if (info->time_to_die < (get_time() - l_meal))
			{
				died_f(info);
				pthread_mutex_lock(&info->print);
				printf("%ld %d died\n", get_time() - info->start, \
				info->philos[i].id);
				pthread_mutex_unlock(&info->print);
				return (1);
			}
		}
	}
	return (0);
}
