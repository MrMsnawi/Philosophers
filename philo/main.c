/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/24 17:53:56 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac == 5 || ac == 6)
	{
		if (parse_data(ac, av))
			return (1);
		if (data_init(&info, av))
			return (1);
		if (create_philos(&info))
			return (exit_prtcl(&info, 1));
	}
	else
		return (print_usage());
	return (exit_prtcl(&info, 0));
}
