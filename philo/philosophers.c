/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:21 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 19:01:03 by abmasnao         ###   ########.fr       */
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

static int	routine_init(t_philo *philo, t_routine_vars **r_vars)
{
	if (!philo)
		return (1);
	*r_vars = malloc(sizeof(t_routine_vars));
	if (!*r_vars)
	{
		error("malloc failed");
		return (1);
	}
	if (ft_mutex_lock(philo->info, &philo->info->meal))
	{
		free(*r_vars);
		*r_vars = NULL;
		return (1);
	}
	(*r_vars)->n_meals = philo->info->n_meals;
	(*r_vars)->last_meal = philo->last_meal;
	(*r_vars)->tt_die = philo->info->time_to_die;
	pthread_mutex_unlock(&philo->info->meal);
	return (0);
}

static int	end_sim(t_philo *philo, t_routine_vars *r_vars)
{
	if (philo->info->died == 1)
	{
		pthread_mutex_unlock(&philo->info->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal);
	if (ft_mutex_lock(philo->info, &philo->info->meal))
		return (1);
	if (r_vars->n_meals && r_vars->p_meals == r_vars->n_meals)
	{
		pthread_mutex_unlock(&philo->info->meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal);
	return (0);
}

static int	eating(t_philo *philo, t_routine_vars *r_vars)
{
	if (ft_mutex_lock(philo->info, &philo->info->forks[philo->r_fork]))
		return (1);
	if (print_stat(philo->info->start, philo, philo->id, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		return (1);
	}
	if (ft_mutex_lock(philo->info, &philo->info->forks[philo->l_fork]))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		return (1);
	}
	if (print_stat(philo->info->start, philo, philo->id, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		return (1);
	}
	if (print_stat(philo->info->start, philo, philo->id, "is eating"))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		return (1);
	}
	if (ft_mutex_lock(philo->info, &philo->info->meal))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		return (1);
	}
	philo->last_meal = get_time();
	r_vars->last_meal = philo->last_meal;
	philo->n_meals++;
	r_vars->p_meals = philo->n_meals;
	pthread_mutex_unlock(&philo->info->meal);
	if (ft_usleep(philo->info, philo->info->time_to_eat))
	{
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_routine_vars	*r_vars;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (philo->info->died == 1)
		return (NULL);
	if (routine_init(philo, &r_vars))
		return (NULL);
	if (one_philo(philo))
		return (return_null(r_vars));
	if (philo->id % 2)
	{
		if (ft_usleep(philo->info, philo->info->time_to_eat))
			return (return_null(r_vars));
	}
	while (r_vars->tt_die >= (get_time() - r_vars->last_meal))
	{
		if (eating(philo, r_vars))
			return (return_null(r_vars));
		if (print_stat(philo->info->start, philo, philo->id, "is sleeping"))
			return (return_null(r_vars));
		if (ft_usleep(philo->info, philo->info->time_to_sleep))
			return (return_null(r_vars));
		if (print_stat(philo->info->start, philo, philo->id, "is thinking"))
			return (return_null(r_vars));
		if (ft_mutex_lock(philo->info, &philo->info->meal))
			return (return_null(r_vars));
		if (end_sim(philo, r_vars))
			return (return_null(r_vars));
	}
	return (return_null(r_vars));
}
