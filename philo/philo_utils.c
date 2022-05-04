/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:58 by marlean           #+#    #+#             */
/*   Updated: 2022/05/04 16:19:28 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	my_time(void)
{
	struct timeval	tv;
	long long		calc_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (ft_error(4));
	calc_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (calc_time);
}

int	my_sleep(int time)
{
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	usleep(time * 900);
	while (((now.tv_sec * 1000000 + now.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec)) < time * 1000)
	{
		usleep(100);
		gettimeofday(&now, NULL);
	}
	return (0);
}

int	ft_error(int num)
{
	if (num == 1)
		write(1, "Wrong input\n", 12);
	else if (num == 2)
		write (1, "Mutex error\n", 12);
	else if (num == 3)
		write (1, "Malloc error\n", 13);
	else if (num == 4)
		write (1, "Time error\n", 11);
	return (-1);
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
			return (-1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res) > 2147483647)
			return (-1);
	}
	if (str[i] != '\0' && (!(str[i] >= '0' && str[i] <= '9') || res == 0))
		return (-1);
	return (res);
}

int	init_each_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_error(2));
		data->philo[i].philo_index = i + 1;
		data->philo[i].last_eat = my_time();
		data->philo[i].data = data;
		data->philo[i].last = 0;
		data->philo[i].l_fork = &data->forks[i + 1];
		if (i == 0)
			data->philo[i].r_fork = &data->forks[data->num_of_philo];
		else
			data->philo[i].r_fork = &data->forks[i];
		i++;
	}
	data->philo[i - 1].last = 1;
	return (0);
}

int	init_philo(t_data *data, char **argv)
{
	data->num_of_philo = ph_atoi(argv[1]);
	data->time_to_die = ph_atoi(argv[2]);
	data->time_to_eat = ph_atoi(argv[3]);
	data->time_to_sleep = ph_atoi(argv[4]);
	if (argv[5])
	{
		data->num_of_eat = ph_atoi(argv[5]);
		if (data->num_of_eat <= 0)
			return (ft_error(1));
	}
	if (data->num_of_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (ft_error(1));
	data->start_time = my_time();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ft_error(2));
	data->id = malloc(sizeof(pthread_t) * data->num_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	data->result = NULL;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo || !data->id)
		return (ft_error(3));
	if (init_each_philo(data) != 0)
		return (-1);
	return (0);
}
