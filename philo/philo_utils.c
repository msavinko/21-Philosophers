/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:58 by marlean           #+#    #+#             */
/*   Updated: 2022/04/11 20:10:11 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	my_time(void)
{
	struct timeval	tv;
	long long		calc_time;

	gettimeofday(&tv, NULL);
	calc_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (calc_time);
}

void	ft_error(int num)
{
	if (num == 1)
		write(1, "Wrong input\n", 12);
	else if (num == 2)
		write (1, "Mutex error\n", 12);
	else if (num == 3)
		write (1, "Malloc error\n", 13);
	exit(1);
}

int	ph_atoi(const char *str)
{
	int			i;
	long int	res;

	i = 0;
	res = 0;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			ft_error(1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res) > 2147483647)
			ft_error(1);
	}
	if (res == 0)
		ft_error(1);
	return (res);
}

void	init_each_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->philo->forks[i], NULL) != 0)
			ft_error(2);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		data->philo[i].philo_index = i + 1;
		data->philo[i].left_fork = &data->philo->forks[i];
		data->philo[i].right_fork = &data->philo->forks[(i + 1) % data->num_of_philo];
		data->philo[i].last_eat = my_time();
		i++;
	}
}

void	init_philo(t_data *data, char **argv)
{
	data->num_of_philo = ph_atoi(argv[1]);
	data->time_to_die = ph_atoi(argv[2]);
	data->time_to_eat = ph_atoi(argv[3]);
	data->time_to_sleep = ph_atoi(argv[4]);
	if (argv[5])
		data->num_of_eat = ph_atoi(argv[5]);
	data->start_time = my_time();
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	data->id = malloc(sizeof(pthread_t) * data->num_of_philo);
	data->philo->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->philo || !data->id || !data->philo->forks)
		ft_error(3);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		ft_error(2);
	init_each_philo(data);
}