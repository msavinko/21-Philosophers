/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:58 by marlean           #+#    #+#             */
/*   Updated: 2022/05/11 12:18:29 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_print(char *str, t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->data->my_mutex);
	now = my_time() - philo->data->start_time;
	printf("%lld %d %s\n", now, philo->index, str);
	pthread_mutex_unlock(&philo->data->my_mutex);
}

int	ft_error(int num)
{
	//check if mutex needed
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
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_error(2));
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		data->philo[i].index = i + 1;
		data->philo[i].last_eat = my_time();
		data->philo[i].data = data;
		data->philo[i].iam_last = 0;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].i_eat = 0;
		if (i == 0)
			data->philo[i].r_fork = &data->forks[data->num_of_philo - 1];
		else
			data->philo[i].r_fork = &data->forks[i - 1];
		i++;
	}
	data->philo[i - 1].iam_last = 1;
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
	else
		data->num_of_eat = 0;
	if (data->num_of_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (ft_error(1));
	data->start_time = my_time();
	if (pthread_mutex_init(&data->my_mutex, NULL) != 0)
		return (ft_error(2));
	data->id = malloc(sizeof(pthread_t) * data->num_of_philo);
	data->forks = malloc(sizeof(t_mutex) * data->num_of_philo);
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo || !data->id)
		return (ft_error(3));
	if (init_each_philo(data) != 0)
		return (-1);
	return (0);
}
