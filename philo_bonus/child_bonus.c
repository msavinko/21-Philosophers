/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:55:04 by marlean           #+#    #+#             */
/*   Updated: 2022/05/19 16:48:52 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(int num)
{
	if (num == 1)
		write(1, "Wrong arguments\n", 16);
	else if (num == 2)
		write(1, "Malloc error\n", 13);
	else if (num == 3)
		write(1, "Child error\n", 23);
	else if (num == 4)
		write(1, "Pthread error\n", 14);
	return (1);
}

void	print_b(t_data *data, char *str)
{
	long long	now;

	sem_wait(data->sem);
	now = my_time() - data->start_time;
	printf("%lld %d %s\n", now, data->ph_index, str);
	sem_post(data->sem);
}

void	*monitor_death(void *data_in)
{
	t_data		*data;
	long long	now;

	data = (t_data *)data_in;
	while (1)
	{
		now = my_time();
		if (now - data->last_eat > data->time_to_die)
		{
			sem_wait(data->sem);
			now = my_time() - data->start_time;
			printf("%lld %d died\n", now, data->ph_index);
			sem_post(data->semdie);
			exit(0);
		}
	}
	return (NULL);
}

int	create_monitor(t_data *data)
{
	data->last_eat = my_time();
	if (pthread_create(&data->pthread_id, NULL, &monitor_death, data) != 0)
		return (ft_error(4));
	if (pthread_detach(data->pthread_id) != 0)
		return (ft_error(4));
	return (0);
}

void	start_action(t_data *data)
{
	while (1)
	{
		sem_wait(data->semfork);
		print_b(data, "has taken a fork");
		sem_wait(data->semfork);
		print_b(data, "has taken a fork");
		print_b(data, "is eating");
		data->last_eat = my_time();
		my_sleep(data->time_to_eat);
		data->i_eat++;
		if (data->i_eat == data->num_of_eat)
			sem_post(data->semeat);
		sem_post(data->semfork);
		sem_post(data->semfork);
		print_b(data, "is sleeping");
		my_sleep(data->time_to_sleep);
		print_b(data, "is thinking");
	}
}
