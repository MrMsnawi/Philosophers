/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/05/01 21:39:16 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(void)
{
	printf(RED"bad arguments:\n"RESET);
	printf(YELLOW"usage: <number_of_philosophers>" 
		" <time_to_die>"
		" <time_to_eat>"
		" <time_to_sleep>"
		" [number_of_times_each_philosopher_must_eat]\n"RESET);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	if (!str)
		return (0);
	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return ((int)(res * sign));
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

int	error(char *str)
{
	if (!str)
		return ;
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

int	is_empty(char *str)
{
	int	i;

	if (!str)
		return (error("Somthing went wrong!"));
	if (!str[0])
		return (error("Empty argument!"));
	while (str[i])
	{
		if ()
	}
}

int	parse_data(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (is_empty(av[i]) || is_valid(av[i]))
			return (1);
	}
}

void	last_clean(t_philo **philo, t_info **info)
{
	if (*philo)
		free(*philo);
	if (*info)
		free(*info);
}

int main(int ac, char **av)
{
	t_philo	*philo;
	t_info	*info;

	if (ac == 5 || ac == 6)
	{
		if (parse_data(ac, av))
			return (1);
		// create_philos();
		// monitor();
	}
	else
		print_usage();
	last_clean(&philo, &info);
}
