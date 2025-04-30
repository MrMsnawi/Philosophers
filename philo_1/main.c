/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/04/30 20:01:43 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

void	parse_data(int ac, char **av)
{
	int	i;

	
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		parse_data(ac, av);
		// create_philos();
		// monitor();
	}
	else
		print_usage();
}
