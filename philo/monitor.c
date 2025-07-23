/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:47:36 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/23 21:47:28 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_n_meals(t_info *info)
{
	int	i;
	int	philos;

	pthread_mutex_lock(&info->meal);
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

int	monitor(t_info *info)
{
	int		i;
	time_t	l_meal;

	while (1)
	{
		if (info->n_meals != -1 && check_n_meals(info) == 1)
			return (1);
		i = -1;
		while (++i < info->n_philos)
		{
			pthread_mutex_lock(&info->meal);
			l_meal = info->philos[i].last_meal;
			pthread_mutex_unlock(&info->meal);
			if (info->time_to_die < (get_time() - l_meal))
			{
				pthread_mutex_lock(&info->die);
				info->died = 1;
				pthread_mutex_unlock(&info->die);
				print_stat(&info->philos[i], "died");
				return (1);
			}
		}
		usleep(500);
	}
	return (0);
}
