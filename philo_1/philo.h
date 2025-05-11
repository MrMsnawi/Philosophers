/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:10:25 by abmasnao          #+#    #+#             */
/*   Updated: 2025/05/11 13:22:16 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>

// ********************** structs **********************************

typedef struct s_info t_info;

typedef struct s_philo
{
	int			id;
	int			r_fork;
	int			l_fork;
	int			n_meals;
	int			last_meal;
	pthread_t	thread;
	t_info		*info;
}				t_philo;

typedef struct s_info
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
	// pthread_mutex_t	meal;
}				t_info;

// ************************* colors ******************************

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

// ************************* strings *******************************

long	ft_atol(char *str);
int		ft_strlen(char *str);

// ************************* parser **********************************

int	parse_data(int ac, char **av);

// ************************* error *********************************

void	print_usage(void);
int		error(char *str);

#endif