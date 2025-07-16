/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:21 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/16 08:16:25 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo(t_philo *philo)
{
	if (philo->info->n_philos == 1)
	{
		print_stat(philo, "has taken a fork");
		ft_usleep(philo->info, philo->info->time_to_die);
		return (1);
	}
	return (0);
}

static int	end_sim(t_philo *philo)
{
	if (check_die(philo->info))
		return (1);
	if (ft_mutex_lock(philo->info, &philo->info->meal))
		return (1);
	if (philo->info->n_meals && philo->n_meals == philo->info->n_meals)
	{
		pthread_mutex_unlock(&philo->info->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal);
	return (0);
}

static int	eating(t_philo *philo)
{
	if (ft_mutex_lock(philo->info, &philo->info->forks[philo->r_fork]))
		return (1);
	if (print_stat(philo, "has taken a fork"))
		return (pthread_mutex_unlock(&philo->info->forks[philo->r_fork]), 1);
	if (ft_mutex_lock(philo->info, &philo->info->forks[philo->l_fork]))
		return (pthread_mutex_unlock(&philo->info->forks[philo->r_fork]), 1);
	if (print_stat(philo, "has taken a fork"))
		return (pthread_mutex_unlock(&philo->info->forks[philo->l_fork]), \
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]), 1);
	if (print_stat(philo, "is eating"))
		return (pthread_mutex_unlock(&philo->info->forks[philo->l_fork]), \
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]), 1);
	if (ft_mutex_lock(philo->info, &philo->info->meal))
		return (pthread_mutex_unlock(&philo->info->forks[philo->l_fork]), \
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]), 1);
	philo->last_meal = get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->info->meal);
	if (ft_usleep(philo->info, philo->info->time_to_eat))
		return (pthread_mutex_unlock(&philo->info->forks[philo->l_fork]), \
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]), 1);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (philo->info->died == 1)
		return (NULL);
	if (one_philo(philo))
		return (NULL);
	if (philo->id % 2)
		ft_usleep(philo->info, philo->info->time_to_eat);
	while (philo->info->time_to_die >= (get_time() - philo->last_meal))
	{
		if (eating(philo))
			return (NULL);
		if (end_sim(philo))
			return (NULL);
		if (print_stat(philo, "is sleeping"))
			return (NULL);
		if (ft_usleep(philo->info, philo->info->time_to_sleep))
			return (NULL);
		if (print_stat(philo, "is thinking"))
			return (NULL);
	}
	return (NULL);
}
