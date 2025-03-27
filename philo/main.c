/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:30:31 by abmasnao          #+#    #+#             */
/*   Updated: 2025/03/23 14:29:33 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(500);
}

void	print(char *txt, time_t time, int id)
{
	if (!txt)
		return ;
	printf("%ld %d %s", get_time() - time, id, txt);
}

void	*routine(void *philo)
{
	t_philo *pilo;

	pilo = (t_philo *)philo;
	pilo->info->start = get_time();
	// if (pilo->id % 2)
	// 	ft_usleep(pilo->info->time_to_die);
	while (get_time() < pilo->last_meal + pilo->info->time_to_die)
	{
		pthread_mutex_lock(&pilo->info->forks[pilo->r_fork]);
		print("has taken a fork\n", pilo->info->start, pilo->id);
		pthread_mutex_lock(&pilo->info->forks[pilo->l_fork]);
		print("has taken a fork\n", pilo->info->start, pilo->id);
		print("is eating\n", pilo->info->start, pilo->id);
		ft_usleep(pilo->info->time_to_eat);
		pthread_mutex_lock(&pilo->info->meal);
		pilo->last_meal = get_time();
		pilo->n_meals++;
		pthread_mutex_unlock(&pilo->info->meal);
		pthread_mutex_unlock(&pilo->info->forks[pilo->r_fork]);
		pthread_mutex_unlock(&pilo->info->forks[pilo->l_fork]);
		print("is sleeping\n", pilo->info->start, pilo->id);
		ft_usleep(pilo->info->time_to_sleep);
		print("is thinking\n", pilo->info->start, pilo->id);
	}
	return (NULL);
}

void	create_philos(t_info *info)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (1)
	{
		while (i < info->n_philos)
		{
			philo = &info->philos[i];
			philo->id = i + 1;
			philo->r_fork = i;
			philo->l_fork = (i + 1) % info->n_philos;
			pthread_mutex_lock(&info->meal);
			philo->n_meals = 0;
			philo->last_meal = get_time();
			pthread_mutex_unlock(&info->meal);
			philo->info = info;
			if (-1 == pthread_create(&philo->thread, NULL, routine, philo))
				p_error("Failed to create a philo!\n");
			if (-1 == pthread_detach(philo->thread))
				p_error("Failed to detach a philo!\n");
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (p_error("Malloc failed!\n"));
	if (parsing(ac, av))
		return (1);
	if (process_data(av, info))
		return (1);
	if (mutex_init(info))
		return (1);
	create_philos(info);
	pthread_mutex_lock(&info->meal);
}
