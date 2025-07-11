/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:52 by abmasnao          #+#    #+#             */
/*   Updated: 2025/07/11 19:55:17 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

// void	safe_free(void *ptr)
// {
// 	if (ptr)
// 		free(ptr);
// }

// int	exit_prtcl(t_info *info, int ret)
// {
// 	int	i;

// 	pthread_mutex_destroy(&info->print);
// 	pthread_mutex_destroy(&info->die);
// 	i = -1;
// 	while (++i < info->n_philos)
// 		pthread_mutex_destroy(&info->forks[i]);
// 	safe_free(info);
// 	return (ret);
// }

// int	mutex_init(t_info *info)
// {
// 	int	i;
	
// 	if (-1 == pthread_mutex_init(&info->print, NULL)
// 		|| -1 == pthread_mutex_init(&info->print, NULL))
// 		return (1);
// 	i = -1;
// 	while (++i < info->n_philos)
// 	{
// 		info->philos[i].id = i + 1;
// 		info->philos[i].last_meal = 0;
// 		if (-1 == pthread_mutex_init(&info->forks[i], NULL))
// 			return (1);
// 	}
// 	return (0);
// }

// int	data_init(t_info *info, char **args)
// {
// 	if (!info || !args)
// 		return (1);
// 	info->n_philos = (int)ft_atol(args[1]);
// 	if (info->n_philos > 200)
// 		return (error("Number of philosophers greater that 200!"));
// 	info->time_to_die = (int)ft_atol(args[2]);
// 	info->time_to_eat = (int)ft_atol(args[3]);
// 	info->time_to_sleep = (int)ft_atol(args[4]);
// 	info->died = 0;
// 	if (info->time_to_die < 60 || info->time_to_eat < 60 || info->time_to_sleep < 60)
// 		return (error("Minimum of time to die-eat-sleep is 60 ms!"));
// 	if (args[5])
// 		info->n_meals = (int)ft_atol(args[5]);
// 	else
// 		info->n_meals = -1;
// 	return (mutex_init(info));
// }

// time_t	get_time()
// {
// 	struct timeval tv;
	
// 	if (-1 == gettimeofday(&tv, NULL))
// 		return (-1);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// void	ft_usleep(int time)
// {
// 	time_t	curr_t;
	
// 	curr_t = get_time();
// 	while (get_time() < curr_t + time)
// 		usleep(500);
// }

// void	print_stat(time_t start, t_philo *philo, int id, char *msg)
// {
// 	if (!philo)
// 		return ;

// 	// pthread_mutex_lock(&philo->info->print);
// 	printf("%ld %d %s\n", get_time() - start, id, msg);
// 	// pthread_mutex_unlock(&philo->info->print);
// }

// void	*routine(void *arg)
// {
// 	t_philo	*philo;

// 	if (!arg)
// 		return (NULL);
// 	philo = (t_philo *)arg;
// 	if (philo->id % 2)
// 		ft_usleep(philo->info->time_to_eat);
// 	while (true)
// 	{
// 		// if (philo->info->n_philos == 1)
// 		// 	one_philo(philo);
// 		if (philo->info->died == 1)
// 			return (NULL);
// 		if (philo->info->time_to_die < get_time() - philo->last_meal)
// 		{
// 			philo->info->died = 1;
// 			return (NULL);
// 		}
// 		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
// 		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
// 		pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
// 		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
// 		print_stat(philo->info->start, philo, philo->id, "is eating");
// 		pthread_mutex_lock(&philo->info->meal);
// 		philo->last_meal = get_time();
// 		philo->n_meals++;
// 		if (philo->info->n_meals && philo->n_meals == philo->info->n_meals)
// 			return (NULL);
// 		pthread_mutex_unlock(&philo->info->meal);
// 		ft_usleep(philo->info->time_to_eat);
// 		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
// 		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
// 		print_stat(philo->info->start, philo, philo->id, "is sleeping");
// 		ft_usleep(philo->info->time_to_sleep);
// 		print_stat(philo->info->start, philo, philo->id, "is thinking");
// 	}
// 	// while (philo->info->time_to_die >= get_time() - philo->last_meal)
// 	// {
// 	// 	pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
// 	// 	print_stat(philo->info->start, philo, philo->id, "has taken a fork");
// 	// 	pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
// 	// 	print_stat(philo->info->start, philo, philo->id, "has taken a fork");
// 	// 	print_stat(philo->info->start, philo, philo->id, "is eating");
// 	// 	pthread_mutex_lock(&philo->info->meal);
// 	// 	philo->last_meal = get_time();
// 	// 	philo->n_meals++;
// 	// 	if (philo->info->n_meals && philo->n_meals == philo->info->n_meals)
// 	// 		return (NULL);
// 	// 	pthread_mutex_unlock(&philo->info->meal);
// 	// 	ft_usleep(philo->info->time_to_eat);
// 	// 	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
// 	// 	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
// 	// 	print_stat(philo->info->start, philo, philo->id, "is sleeping");
// 	// 	ft_usleep(philo->info->time_to_sleep);
// 	// 	print_stat(philo->info->start, philo, philo->id, "is thinking");
// 	// }
// 	return (NULL);
// }

// int	check_n_meals(t_info *info)
// {
// 	int i;
// 	int	philos;

// 		pthread_mutex_lock(&info->meal);
// 	i = 0;
// 	philos = 0;
// 	while (i < info->n_philos)
// 	{
// 		// int o_meals = info->philos[i].n_meals;
// 		// int p_meals = info->n_meals;
// 		// fprintf(stderr, "%d\n", info->philos[i].n_meals);
// 		if (info->philos[i].n_meals >= info->n_meals)
// 			philos++;
// 		i++;
// 	}
// 		pthread_mutex_unlock(&info->meal);
// 	if (philos == info->n_philos)
// 		return (1);
// 	return (0);
// }

// void	*monitor(void *arg)
// {
// 	int	i;
// 	int	flag;
// 	t_info	*info;

// 	info = (t_info *)arg;
// 	flag = 0;
// 	while (1)
// 	{
// 		// if (info->n_meals && check_n_meals(info))
// 		// 	return (NULL);
// 		// usleep(500);
// 		i = 0;
// 			pthread_mutex_lock(&info->meal);
// 		while (i < info->n_philos)
// 		{
// 			int time_to_die = info->time_to_die;
// 			int last_meal = (get_time() - info->philos[i].last_meal);
// 			if (time_to_die < last_meal)
// 			{
// 				flag = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 			pthread_mutex_unlock(&info->meal);
// 		if (flag == 1)
// 		{
// 			print_stat(info->start, &info->philos[i], info->philos[i].id, "died");
// 			// exit_prtcl(info, 0);
// 			return (NULL);
// 		}
// 		printf("debugging...\n");
// 	}
// 	return (NULL);
// }

// int	create_philos(t_info *info)
// {
// 	int		i;
// 	pthread_t	m_thread;

// 	if (!info)
// 		return (1);
// 	i = -1;
// 	info->start = get_time();
// 	while (++i < info->n_philos)
// 	{
// 		info->philos[i].id = i + 1;
// 		info->philos[i].r_fork = i;
// 		info->philos[i].l_fork = (i + 1) % info->n_philos;
// 		pthread_mutex_lock(&info->meal);
// 		info->philos[i].n_meals = 0;
// 		info->philos[i].last_meal = get_time();
// 		pthread_mutex_unlock(&info->meal);
// 		info->philos[i].info = info;
// 		if (-1 == pthread_create(&info->philos[i].thread, NULL, routine, &info->philos[i]))
// 			return (error("pthread_create failed!"));
// 	}
// 	if (-1 == pthread_create(&m_thread, NULL, monitor, info))
// 		return (error("monitor thread creating failed!"));
// 	if (-1 == pthread_join(m_thread, NULL))
// 		return (error("pthread_join failed!"));
// 	i = -1;
// 	while (++i < info->n_philos)
// 	{
// 		if (-1 == pthread_join(info->philos[i].thread, NULL))
// 			return (error("pthread_join failed!"));
// 	}
// 	return (0);
// }

// int main(int ac, char **av)
// {
// 	t_info	*info;

// 	info = malloc(sizeof(t_info));
// 	if (!info)
// 		return (error("malloc failed!"));
// 	if (ac == 5 || ac == 6)
// 	{
// 		if (parse_data(ac, av))
// 			return (1);
// 		if (data_init(info, av))
// 			return (exit_prtcl(info, 1));
// 		if (create_philos(info))
// 			return (exit_prtcl(info, 1));
// 		// monitor(info);
// 	}
// 	else
// 		return (print_usage(), exit_prtcl(info, 1));
// 	return (exit_prtcl(info, 0));
// }


#include "philo.h"

void	safe_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	exit_prtcl(t_info *info, int ret)
{
	int	i;

	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->die);
	i = -1;
	while (++i < info->n_philos)
		pthread_mutex_destroy(&info->forks[i]);
	safe_free(info);
	return (ret);
}

int	mutex_init(t_info *info)
{
	int	i;
	
	if (-1 == pthread_mutex_init(&info->print, NULL)
		|| -1 == pthread_mutex_init(&info->die, NULL))
		return (1);
	i = -1;
	while (++i < info->n_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].last_meal = 0;
		if (-1 == pthread_mutex_init(&info->forks[i], NULL))
			return (1);
	}
	return (0);
}

int	data_init(t_info *info, char **args)
{
	if (!info || !args)
		return (1);
	info->n_philos = (int)ft_atol(args[1]);
	if (info->n_philos > 200)
		return (error("Number of philosophers greater that 200!"));
	info->time_to_die = (int)ft_atol(args[2]);
	info->time_to_eat = (int)ft_atol(args[3]);
	info->time_to_sleep = (int)ft_atol(args[4]);
	info->died = 0;
	if (info->time_to_die < 60 || info->time_to_eat < 60 || info->time_to_sleep < 60)
		return (error("Minimum of time to die-eat-sleep is 60 ms!"));
	if (args[5])
		info->n_meals = (int)ft_atol(args[5]);
	else
		info->n_meals = -1;
	return (mutex_init(info));
}

time_t	get_time()
{
	struct timeval tv;
	
	if (-1 == gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	time_t	curr_t;

	curr_t = get_time();
	while (get_time() < curr_t + time)
		usleep(500);
}

void	print_stat(time_t start, t_philo *philo, int id, char *msg)
{
	if (!philo)
		return ;

	pthread_mutex_lock(&philo->info->print);
	printf("%ld %d %s\n", get_time() - start, id, msg);
	pthread_mutex_unlock(&philo->info->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int p_meals;
	int	die;
	int n_meals;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->info->meal);
	n_meals = philo->info->n_meals;
	pthread_mutex_unlock(&philo->info->meal);
	if (philo->id % 2)
		ft_usleep(philo->info->time_to_eat);
	while (true)
	{
		// if (philo->info->n_philos == 1)
		// 	one_philo(philo);
		pthread_mutex_lock(&philo->info->die);
		die = philo->info->died;
		pthread_mutex_unlock(&philo->info->die);
		if (die == 1)
			return (NULL);
		if (philo->info->time_to_die < get_time() - philo->last_meal)
		{
			pthread_mutex_lock(&philo->info->die);
			philo->info->died = 1;
			pthread_mutex_unlock(&philo->info->die);
			print_stat(philo->info->start, philo, philo->id, "died");
			return (NULL);
		}
		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
		print_stat(philo->info->start, philo, philo->id, "has taken a fork");
		print_stat(philo->info->start, philo, philo->id, "is eating");
		pthread_mutex_lock(&philo->info->meal);
		philo->last_meal = get_time();
		philo->n_meals++;
		p_meals = philo->n_meals;
		pthread_mutex_unlock(&philo->info->meal);
		ft_usleep(philo->info->time_to_eat);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		print_stat(philo->info->start, philo, philo->id, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		print_stat(philo->info->start, philo, philo->id, "is thinking");
		if (n_meals && p_meals == n_meals)
		{
			fprintf(stderr, "%d\n", p_meals);
			return (NULL);
		}
	}
	return (NULL);
}

int	create_philos(t_info *info)
{
	int		i;

	if (!info)
		return (1);
	i = -1;
	info->start = get_time();
	while (++i < info->n_philos)
	{
		info->philos[i].r_fork = i;
		info->philos[i].l_fork = (i + 1) % info->n_philos;
		pthread_mutex_lock(&info->meal);
		info->philos[i].n_meals = 0;
		info->philos[i].last_meal = get_time();
		pthread_mutex_unlock(&info->meal);
		info->philos[i].info = info;
		if (-1 == pthread_create(&info->philos[i].thread, NULL, routine, &info->philos[i]))
			return (error("pthread_create failed!"));
	}
	i = -1;
	while (++i < info->n_philos)
	{
		if (-1 == pthread_join(info->philos[i].thread, NULL))
			return (error("pthread_join failed!"));
	}
	printf("hokay\n");
	return (0);
}

int main(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (error("malloc failed!"));
	if (ac == 5 || ac == 6)
	{
		if (parse_data(ac, av))
			return (1);
		if (data_init(info, av))
			return (exit_prtcl(info, 1));
		if (create_philos(info))
			return (exit_prtcl(info, 1));
	}
	else
		return (print_usage(), exit_prtcl(info, 1));
	return (exit_prtcl(info, 0));
}
