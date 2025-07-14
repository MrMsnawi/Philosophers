/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:49:39 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 13:39:55 by abmasnao         ###   ########.fr       */
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

time_t	get_time()
{
	struct timeval tv;
	
	if (-1 == gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	time_t	curr_t;

	curr_t = get_time();
	while (get_time() < curr_t + time)
		usleep(time);
}

void	print_stat(time_t start, t_philo *philo, int id, char *msg)
{
    int died;

	if (!philo)
		return ;
    pthread_mutex_lock(&philo->info->die);
    died = philo->info->died;
    pthread_mutex_unlock(&philo->info->die);
	if (ft_strcmp(msg, "died") != 0 && died == 1)
        return ;
	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d %s\n", get_time() - start, id, msg);
	pthread_mutex_unlock(&philo->info->print);
}
