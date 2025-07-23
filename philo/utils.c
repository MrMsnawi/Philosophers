/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:49:39 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/23 21:45:42 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_prtcl(t_info *info, int ret)
{
	int	i;

	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->die);
	pthread_mutex_destroy(&info->meal);
	pthread_mutex_destroy(&info->time);
	i = -1;
	while (++i < info->n_philos)
		pthread_mutex_destroy(&info->forks[i]);
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

	if (check_die(info))
		return (1);
	curr_t = get_time();
	while (get_time() < curr_t + time)
	{
		if (check_die(info))
			return (1);
		usleep(time);
	}
	return (0);
}

int	print_stat(t_philo *philo, char *msg)
{
	static int	died;

	pthread_mutex_lock(&philo->info->print);
	if (ft_strcmp(msg, "died") == 0)
	{
		printf("%ld %d %s\n", get_time() - philo->info->start, philo->id, msg);
		died = 1;
	}
	if (died == 0)
		printf("%ld %d %s\n", get_time() - philo->info->start, philo->id, msg);
	pthread_mutex_unlock(&philo->info->print);
	return (0);
}
