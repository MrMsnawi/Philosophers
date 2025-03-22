/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 06:47:06 by abmasnao          #+#    #+#             */
/*   Updated: 2025/03/22 09:34:37 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		i++;
	i--;
	while (str[++i])
		res = res * 10 + (str[i] - 48);
	return ((int)res);
}

// int	parsing(int ac, char **av, t_info *info)
// {
// 	int		i;
// 	int		j;

// 	if (ac != 5 && ac != 6)
// 		return(p_error(RC"Error: number of arguments!\n"EC));
// 	i = 1;
// 	while (av[i])
// 	{
// 		printf("%d\n", i);
// 		if (ft_strlen(av[i]) == 0)
// 			return (p_error(RC"Empty argument!\n"EC));
// 		j = -1;
// 		while (av[i][++j])
// 		{
// 			if (av[i][j] == ' ' || (av[i][j] >= 9 && av[i][j] <= 13))
// 				return (p_error(RC"Don't use spaces!\n"EC));
// 		}
// 		if (ft_atoi(av[i]) > INT_MAX)
// 			return (1);
// 		i++;
// 	}
// 	// process_data(av, info);
// 	(void)info;
// 	return (0);
// }

/*
	check empty arg
	is didgit
	size limit
	not > INT_MAX
	not negative
	phios <= 200 && > 0
*/

int	is_empty(char *av)
{
	int	i;

	i = 0;
	if (!av[0])
		return (p_error(RC"Error: empty argument!\n"EC));
	while (av[i] && ((av[i] >= 9 && av[i] <= 13) || av[i] == ' '))
		i++;
	if (!av[i])
		return (p_error(RC"Error: empty argument!\n"EC));
	return (0);
}

int	is_valid(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] < '0' || av[i] > '9')
			&& (av[i] < 9 || av[i] > 13) && av[i] != ' ' && av[i] != '+')
			return (p_error(RC"Error: argument not valid!\n"EC));
		i++;
	}
	return (0);
}

time_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	process_data(char **av, t_info *info)
{
	info->start = get_time();
	if (-1 == pthread_mutex_init(&info->print, NULL))
		return (1);
	info->n_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		info->n_meals = ft_atoi(av[5]);
	else
		info->n_meals = -1;
	return (0);
}

int	dinner_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
	{
		if (-1 == pthread_mutex_init(&info->forks[i], NULL))
	}
}

int	parsing(int ac, char **av, t_info *info)
{
	int	i;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		while (av[i])
		{
			if (is_empty(av[i]) || is_valid(av[i]))
				return (1);
			i++;
		}
	}
	else
		return (p_error(RC"Error: number of arguments!\n"EC));
	if (process_data(av, info))
		return (1);
	if (dinner_init(info))
		return (1);
	return (0);
}
