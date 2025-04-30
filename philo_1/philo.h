/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:10:25 by abmasnao          #+#    #+#             */
/*   Updated: 2025/04/30 20:15:09 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// *************************** colors ******************************
# define RED "\033[31m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

typedef struct s_philo
{
	int	n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals;
	t_info *info;
}				t_philo;

typedef struct s_info
{
	//...
	
}				t_info;

#endif