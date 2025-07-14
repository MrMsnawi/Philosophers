/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:07:58 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/14 17:13:02 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_empty(char *str)
{
	int	i;

	if (!str)
		return (error("Somthing went wrong!"));
	if (!str[0])
		return (error("Empty argument!"));
	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (error("Empty argument!"));
}

static int	is_valid(char *str)
{
	int	i;

	if (!str)
		return (error("Somthing went wrong!"));
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+'))
			return (error("Invalid argument!"));
		i++;
	}
	return (0);
}

static int	is_limit(char *str)
{
	long	arg;

	if (!str)
		return (error("Somthing went wrong!"));
	arg = ft_atol(str);
	if (arg > INT_MAX)
		return (error("Argument too big!"));
	return (0);
}

int	parse_data(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (is_empty(av[i]))
			return (1);
		if (is_valid(av[i]))
			return (1);
		if (is_limit(av[i]))
			return (1);
	}
	return (0);
}
