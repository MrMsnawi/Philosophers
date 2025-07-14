/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:21 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 17:26:23 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo(t_philo *philo)
{
	if (philo->info->n_philos == 1)
	{
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		ft_usleep(philo->info, philo->info->time_to_die);
		return (1);
	}
	return (0);
}

static void	routine_init(t_philo *philo, t_routine_vars **r_vars)
{
	if (!philo)
		return ;
	*r_vars = malloc(sizeof(t_routine_vars));
	if (!*r_vars)
	{
		error("malloc failed");
		return ;
	}
	ft_mutex_lock(philo->info, &philo->info->meal);
	(*r_vars)->n_meals = philo->info->n_meals;
	(*r_vars)->last_meal = philo->last_meal;
	(*r_vars)->tt_die = philo->info->time_to_die;
	pthread_mutex_unlock(&philo->info->meal);
}

static int	end_sim(t_philo *philo, t_routine_vars *r_vars)
{
	if (philo->info->died == 1)
	{
		pthread_mutex_unlock(&philo->info->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal);
	ft_mutex_lock(philo->info, &philo->info->meal);
	if (r_vars->n_meals && r_vars->p_meals == r_vars->n_meals)
	{
		pthread_mutex_unlock(&philo->info->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal);
	return (0);
}

static void	eating(t_philo *philo, t_routine_vars *r_vars)
{
	ft_mutex_lock(philo->info, &philo->info->forks[philo->r_fork]);
	print_stat(philo->info->start, philo, philo->id, "has taken a fork");
	ft_mutex_lock(philo->info, &philo->info->forks[philo->l_fork]);
	print_stat(philo->info->start, philo, philo->id, "has taken a fork");
	print_stat(philo->info->start, philo, philo->id, "is eating");
	ft_mutex_lock(philo->info, &philo->info->meal);
	philo->last_meal = get_time();
	r_vars->last_meal = philo->last_meal;
	philo->n_meals++;
	r_vars->p_meals = philo->n_meals;
	pthread_mutex_unlock(&philo->info->meal);
	ft_usleep(philo->info, philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_routine_vars	*r_vars;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	routine_init(philo, &r_vars);
	if (one_philo(philo))
		return (return_null(r_vars));
	if (philo->id % 2)
		ft_usleep(philo->info, philo->info->time_to_eat);
	while (r_vars->tt_die >= (get_time() - r_vars->last_meal))
	{
		eating(philo, r_vars);
		print_stat(philo->info->start, philo, philo->id, "is sleeping");
		ft_usleep(philo->info, philo->info->time_to_sleep);
		print_stat(philo->info->start, philo, philo->id, "is thinking");
		ft_mutex_lock(philo->info, &philo->info->meal);
		if (end_sim(philo, r_vars))
			return (return_null(r_vars));
	}
	return (return_null(r_vars));
}
