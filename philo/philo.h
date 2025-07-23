/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:10:25 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/23 21:44:45 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

// ********************** structs **********************************

typedef struct s_info	t_info;

typedef struct s_philo
{
	int			id;
	int			r_fork;
	int			l_fork;
	int			n_meals;
	time_t		last_meal;
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
	int				died;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	die;
	pthread_mutex_t	time;
	time_t			start;
}				t_info;

// ************************* colors ************************************

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

// ************************* parser ************************************

int		parse_data(int ac, char **av);

// ************************* inits *************************************

int		data_init(t_info *info, char **args);

// ************************* utils *************************************

int		exit_prtcl(t_info *info, int ret);
time_t	get_time(void);
int		ft_usleep(t_info *info, int time);
int		print_stat(t_philo *philo, char *msg);

// ************************* philos_op  ********************************

int		joining(t_info *info);
int		creating(t_info *info);
int		create_philos(t_info *info);
int		ft_mutex_lock(t_info *info, pthread_mutex_t *mutex);
int		check_die(t_info *info);

// ************************* error *************************************

void	print_usage(void);
int		error(char *str);

// *************************** strings *********************************

long	ft_atol(char *str);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);

// ************************** philosophers *****************************

void	*routine(void *arg);

// ************************** monitor **********************************

int		monitor(t_info *info);

// *********************************************************************

#endif