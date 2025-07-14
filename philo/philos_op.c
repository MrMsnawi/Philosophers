/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:51:13 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 19:45:49 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*return_null(t_routine_vars *r_vars)
{
	if (r_vars)
	{
		free(r_vars);
		r_vars = NULL;
	}
	return (NULL);
}

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
		if (-1 == pthread_create(&info->philos[i].thread, \
		NULL, routine, &info->philos[i]))
			return (error("pthread_create failed!"));
		i++;
	}
	return (0);
}

int	create_philos(t_info *info)
{
	int			i;
	int			ret;

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
	{
		ret = 1;
	}
	if (joining(info))
		return (1);
	return (ret);
}

int	ft_mutex_lock(t_info *info, pthread_mutex_t *mutex)
{
	if (!info || !mutex)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&info->die) != 0)
	{
		perror("ft_mutex_lock failed");
		return (EXIT_FAILURE);
	}
	if (info->died == 1)
	{
		pthread_mutex_unlock(&info->die);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(&info->die) != 0)
	{
		perror("pthread_mutex_unlock failed");
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_lock(mutex) != 0)
	{
		perror("ft_mutex_lock failed");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
