/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:47:36 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 12:51:36 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_meals(t_info *info)
{
	int i;
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
	int		n_meals;
	time_t	l_meal;
    time_t	tt_die;

	pthread_mutex_lock(&info->meal);
	n_meals = info->n_meals;
	pthread_mutex_unlock(&info->meal);
	while (1)
	{
		if (n_meals != -1 && check_n_meals(info) == 1)
			return (1);
		i = 0;
		while (i < info->n_philos)
		{
			pthread_mutex_lock(&info->meal);
			l_meal = info->philos[i].last_meal;
            tt_die = info->time_to_die;
			pthread_mutex_unlock(&info->meal);
			if (tt_die < (get_time() - l_meal))
			{
				pthread_mutex_lock(&info->die);
				info->died = 1;
				pthread_mutex_unlock(&info->die);
				print_stat(info->start, &info->philos[i], info->philos[i].id, "died");
				return (1);
			}
			i++;
		}
		usleep(500);
	}
	return (0);
}
