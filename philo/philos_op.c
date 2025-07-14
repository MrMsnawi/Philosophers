/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:51:13 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 13:03:55 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	joining(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philos)
	{
		if (-1 == pthread_join(info->philos[i].thread, NULL))
			return (error("pthread_join failed!"));
	}
	return (0);
}

int	creating(t_info *info)
{
	int	i;

	i = 0;
	info->start = get_time();
	while (i < info->n_philos)
	{
		if (-1 == pthread_create(&info->philos[i].thread, NULL, routine, &info->philos[i]))
			return (error("pthread_create failed!"));
		if (-1 == pthread_detach(info->philos[i].thread))
			return (error("pthread_detach failed!"));
		i++;
	}
	return (0);
}

int	create_philos(t_info *info)
{
	int		i;
	int		ret;

	if (!info)
		return (1);
	ret = 0;
	i = -1;
	while (++i < info->n_philos)
	{
		info->philos[i].r_fork = i;
		info->philos[i].l_fork = (i + 1) % info->n_philos;
		info->philos[i].n_meals = 0;
		info->philos[i].last_meal = get_time();
		info->philos[i].info = info;
	}
	if (creating(info))
		return (1);
	if (monitor(info))
		return (1);
	if (joining(info))
		return (1);
	return (ret);
}
