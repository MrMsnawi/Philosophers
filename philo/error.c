/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:10:53 by abmasnao          #+#    #+#             */
/*   Updated: 2025/05/02 16:40:47 by abmasnao         ###   ########.fr       */
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

int	error(char *str)
{
	if (!str)
		write(2, "Somthing went error", 20);
	else
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}
