/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/05/11 21:25:26 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

int	exit_prtcl(t_info *info, int ret)
{
	int	i;

	pthread_mutex_destroy(&info->print);
	i = -1;
	while (++i < info->n_philos)
		pthread_mutex_destroy(&info->forks[i]);
	safe_free(info);
	// safe_free(philo);
	return (ret);
}

int	mutex_init(t_info *info)
{
	int	i;
	
	if (-1 == pthread_mutex_init(&info->print, NULL))
		return (1);
	i = -1;
	while (++i < info->n_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].last_meal = 0;
		if (0 != pthread_mutex_init(&info->forks[i], NULL))
			return (1);
	}
	return (0);
}

int	data_init(t_info *info, char **args)
{
	if (!info || !args)
		return (1);
	info->n_philos = (int)ft_atol(args[1]);
	if (info->n_philos > 200)
		return (error("Number of philosophers greater that 200!"));
	info->time_to_die = (int)ft_atol(args[2]);
	info->time_to_eat = (int)ft_atol(args[3]);
	info->time_to_sleep = (int)ft_atol(args[4]);
	if (info->time_to_die < 60 || info->time_to_eat < 60 || info->time_to_sleep < 60)
		return (error("Minimum of time to die-eat-sleep is 60 ms!"));
	if (args[5])
		info->n_meals = (int)ft_atol(args[5]);
	else
		info->n_meals = -1;
	return (mutex_init(info));
}

int	get_time()
{
	struct timeval tv;
	
	if (-1 == gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000);
}

/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

void	print_stat(t_philo *philo, int id, char *msg)
{
	if (!philo)
		return ;

	pthread_mutex_lock(&philo->info->print);
	printf("%d %d %s\n", get_time(), id, msg);
	pthread_mutex_unlock(&philo->info->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	printf("%d\n", get_time() - philo->last_meal);
	printf("%d\n\n", philo->info->time_to_die);
	while (philo->info->time_to_die >= (get_time() - philo->last_meal))
	{
		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
		print_stat(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
		print_stat(philo, philo->id, "has taken a fork");
		print_stat(philo, philo->id, "is eating");
		usleep(50000);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	}
	return (NULL);
}

int	create_philos(t_info *info)
{
	int		i;
	t_philo	*philo;

	if (!info)
		return (1);
	i = -1;
	while (++i < info->n_philos)
	{
		philo = &info->philos[i];
		philo->id = i + 1;
		philo->r_fork = i;
		philo->l_fork = (i + 1) % info->n_philos;
		pthread_mutex_lock(&info->meal);
		philo->n_meals = 0;
		philo->last_meal = get_time();
		pthread_mutex_unlock(&info->meal);
		if (-1 == pthread_create(&philo->thread, NULL, routine, philo))
			return (error("pthread_create failed!"));
		if (-1 == pthread_detach(philo->thread))
			return (error("pthread_detach failed!"));
	}
	return (0);
}

int main(int ac, char **av)
{
	// t_philo	*philo;
	t_info	*info;

	// philo = malloc(sizeof(philo));
	info = malloc(sizeof(t_info));
	if (!info)
		return (error("Malloc failed!"));
	if (ac == 5 || ac == 6)
	{
		if (parse_data(ac, av))
			return (1);
		if (data_init(info, av))
			return (exit_prtcl(info, 1));
		if (create_philos(info))
			return (exit_prtcl(info, 1));
		// monitor();
		while (1)
		{
			
		}
	}
	else
		return (print_usage(), exit_prtcl(info, 1));
	return (exit_prtcl(info, 0));
}
