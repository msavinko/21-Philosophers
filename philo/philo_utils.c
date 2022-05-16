/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:43:36 by marlean           #+#    #+#             */
/*   Updated: 2022/05/16 12:06:26 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	burn_them_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->my_mutex);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
	return (0);
}

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
	if (num == 1)
		write(1, "Wrong input\n", 12);
	else if (num == 2)
		write (1, "Mutex error\n", 12);
	else if (num == 3)
		write (1, "Malloc error\n", 13);
	else if (num == 4)
		write(1, "Pthread error\n", 14);
	else
		write (1, "Error\n", 6);
	return (-1);
}

long long	my_time(void)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time);
}

void	my_sleep(int ms)
{
	long	time;

	time = my_time();
	usleep(ms * 920);
	while (my_time() < time + ms)
		usleep(ms * 2);
}
