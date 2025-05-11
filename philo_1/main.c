/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/05/03 18:26:25 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	last_clean(t_philo **philo, t_info **info)
// {
// 	if (*philo)
// 		free(*philo);
// 	if (*info)
// 		free(*info);
// }

int	data_init(t_info *info, char **args)
{
	int	i;

	info->n_philos = (int)ft_atol(args[1]);
	info->time_to_die = (int)ft_atol(args[2]);
	info->time_to_eat = (int)ft_atol(args[3]);
	info->time_to_sleep = (int)ft_atol(args[4]);
	if (args[5])
		info->n_meals = (int)ft_atol(args[5]);
	else
		info->n_meals = -1;
	info->forks = malloc(info->n_philos);
	i = -1;
	while (++i < info->n_philos)
	{
		if (0 != pthread_mutex_init(&info->forks[i], NULL))
		{
			exit_protocol(info);
		}
		
	}
}

int main(int ac, char **av)
{
	t_philo	*philo;
	t_info	*info;

	philo = malloc(sizeof(philo));
	info = maloc(sizeof(info));
	if (!philo || !info)
		return (error("Malloc failed!"));
	if (ac == 5 || ac == 6)
	{
		if (parse_data(ac, av))
			return (1);
		if (data_init(info, av))
			return (1);
		// create_philos();
		// monitor();
	}
	else
		print_usage();
	// last_clean(&philo, &info);
}
