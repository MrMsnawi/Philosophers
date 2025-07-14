/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/13 10:51:40 by abmasnao         ###   ########.fr       */
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
	i = -1;
	while (++i < info->n_philos)
		pthread_mutex_destroy(&info->forks[i]);
	safe_free(info);
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
		if (-1 == pthread_mutex_init(&info->forks[i], NULL))
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
	info->died = 0;
	if (info->time_to_die < 60 || info->time_to_eat < 60 || info->time_to_sleep < 60)
		return (error("Minimum of time to die-eat-sleep is 60 ms!"));
	if (args[5])
		info->n_meals = (int)ft_atol(args[5]);
	else
		info->n_meals = -1;
	return (mutex_init(info));
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
	if (!philo)
		return ;

	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d %s\n", get_time() - start, id, msg);
	pthread_mutex_unlock(&philo->info->print);
}

int	one_philo(t_philo *philo)
{	
	if (philo->info->n_philos == 1)
	{
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		ft_usleep(philo->info->time_to_die);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int p_meals;
	int n_meals;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	philo->info->start = get_time();
	pthread_mutex_lock(&philo->info->meal);
	n_meals = philo->info->n_meals;
	pthread_mutex_unlock(&philo->info->meal);
	if (one_philo(philo))
		return (NULL);
	if (philo->id % 2)
		ft_usleep(philo->info->time_to_eat);
	while (philo->info->time_to_die >= (get_time() - philo->last_meal))
	{
		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		print_stat(philo->info->start, philo, philo->id, "is eating");
		pthread_mutex_lock(&philo->info->meal);
		philo->last_meal = get_time();
		philo->n_meals++;
		p_meals = philo->n_meals;
		pthread_mutex_unlock(&philo->info->meal);
		ft_usleep(philo->info->time_to_eat);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		print_stat(philo->info->start, philo, philo->id, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		print_stat(philo->info->start, philo, philo->id, "is thinking");
		if (n_meals && p_meals == n_meals)
			return (NULL);
	}
	return (NULL);
}

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
			l_meal = get_time() - info->philos[i].last_meal;
			pthread_mutex_unlock(&info->meal);
			if (info->time_to_die < l_meal)
			{
				print_stat(info->start, &info->philos[i], info->philos[i].id, "died");
				return (1);
			}
			i++;
		}
	}
	return (0);
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
		pthread_mutex_lock(&info->meal);
		info->philos[i].n_meals = 0;
		info->philos[i].last_meal = get_time();
		pthread_mutex_unlock(&info->meal);
		info->philos[i].info = info;
		if (-1 == pthread_create(&info->philos[i].thread, NULL, routine, &info->philos[i]))
			return (error("pthread_create failed!"));
	}
	if (monitor(info))
		ret = 1;
	if (joining(info))
		return (1);
	return (ret);
}

int main(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (error("malloc failed!"));
	if (ac == 5 || ac == 6)
	{
		if (parse_data(ac, av))
			return (1);
		if (data_init(info, av))
			return (exit_prtcl(info, 1));
		if (create_philos(info))
			return (exit_prtcl(info, 1));
	}
	else
		return (print_usage(), exit_prtcl(info, 1));
	return (exit_prtcl(info, 0));
}
