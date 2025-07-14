/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 13:40:58 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_info *info)
{
	int	i;
	
	if (-1 == pthread_mutex_init(&info->print, NULL)
		|| -1 == pthread_mutex_init(&info->die, NULL)
		|| -1 == pthread_mutex_init(&info->meal, NULL))
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
	int		p_meals;
	int		n_meals;
	time_t	tt_die;
	time_t	last_meal;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->info->meal);
	n_meals = philo->info->n_meals;
	last_meal = philo->last_meal;
	tt_die = philo->info->time_to_die;
	pthread_mutex_unlock(&philo->info->meal);
	if (one_philo(philo))
		return (NULL);
	if (philo->id % 2)
		ft_usleep(philo->info->time_to_eat);
	while (tt_die >= (get_time() - last_meal))
	{
		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		print_stat(philo->info->start, philo, philo->id, "is eating");
		pthread_mutex_lock(&philo->info->meal);
		philo->last_meal = get_time();
		last_meal = philo->last_meal;
		philo->n_meals++;
		p_meals = philo->n_meals;
		pthread_mutex_unlock(&philo->info->meal);
		ft_usleep(philo->info->time_to_eat);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		print_stat(philo->info->start, philo, philo->id, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		print_stat(philo->info->start, philo, philo->id, "is thinking");
		pthread_mutex_lock(&philo->info->meal);
		if (philo->info->died == 1)
		{
			pthread_mutex_unlock(&philo->info->meal);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->meal);
		pthread_mutex_lock(&philo->info->meal);
		if (n_meals && p_meals == n_meals)
		{
			pthread_mutex_unlock(&philo->info->meal);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->meal);
	}
	return (NULL);
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
