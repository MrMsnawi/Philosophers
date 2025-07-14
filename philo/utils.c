/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:49:39 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 19:50:55 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	exit_prtcl(t_info *info, int ret)
{
	int	i;

	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->die);
	pthread_mutex_destroy(&info->meal);
	i = -1;
	while (++i < info->n_philos)
		pthread_mutex_destroy(&info->forks[i]);
	safe_free(info);
	return (ret);
}

time_t	get_time(void)
{
	struct timeval	tv;

	if (-1 == gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(t_info *info, int time)
{
	time_t	curr_t;

	pthread_mutex_lock(&info->die);
	if (info->died == 1)
	{
		pthread_mutex_unlock(&info->die);
		return (1);
	}
	pthread_mutex_unlock(&info->die);
	pthread_mutex_lock(&info->print);
	curr_t = get_time();
	pthread_mutex_unlock(&info->print);
	while (get_time() < curr_t + time)
	{
		pthread_mutex_lock(&info->die);
		if (info->died == 1)
		{
			pthread_mutex_unlock(&info->die);
			return (1);
		}
		pthread_mutex_unlock(&info->die);
		usleep(time);
	}
	return (0);
}

int	print_stat(time_t start, t_philo *philo, int id, char *msg)
{
	if (!philo)
		return (1);
	pthread_mutex_lock(&philo->info->print);
	pthread_mutex_lock(&philo->info->die);
	if (philo->info->died == 1)
	{
		pthread_mutex_unlock(&philo->info->die);
		pthread_mutex_unlock(&philo->info->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->die);
	printf("%ld %d %s\n", get_time() - start, id, msg);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}
