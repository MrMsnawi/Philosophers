/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:57:43 by abmasnao          #+#    #+#             */
/*   Updated: 2025/03/21 18:13:38 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define RC "\033[31m"
# define EC "\033[0m"

typedef struct s_philo
{
	int				id;
	time_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int				n_meals;
	int				n_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start;
	t_philo			philos[INT_MAX];
	pthread_mutex_t	forks[INT_MAX];
	pthread_mutex_t	print;
	// pthread_mutex_t	meal;
}				t_info;

int		p_error(char *msg);
int		parsing(int ac, char **av, t_info *info);
size_t	ft_strlen(char *str);

#endif