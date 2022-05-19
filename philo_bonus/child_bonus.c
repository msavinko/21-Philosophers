/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:55:04 by marlean           #+#    #+#             */
/*   Updated: 2022/05/19 10:26:55 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	count_eat(t_data *data)
// {
// 	data->i_eat++;
// 	if (data->i_eat == data->num_of_eat)
// 		//sem_post(data->semeat);
// }

void	*monitor_death(void *data_in)
{
	t_data		*data;
	int			i;
	long long	time_diff;

	data = (t_data *)data_in;
	i = 0;
	while (1)
	{
		sem_wait(data->semlasteat);
		data->now = my_time() - data->start_time;
		time_diff = data->now - data->last_eat;
		// printf("now: %lld and diff: %lld > %d\n", data->now, time_diff, data->time_to_die);
		if (time_diff > data->time_to_die)
		{
			print_b(data, "died");
			sem_post(data->semdie);
		}
		sem_post(data->semlasteat);
	}
}

int	create_monitor(t_data *data)
{
	if (pthread_create(&data->pthread_id, NULL, &monitor_death, data) != 0)
		return (ft_error(4));
	if (pthread_detach(data->pthread_id) != 0)
		return (ft_error(4));
	return (0);
}

void	start_action(t_data *data)
{
	if (data->ph_index % 2 == 0)
		usleep(500);
	while (1)
	{
		sem_wait(data->semfork);
		print_b(data, "has taken a fork");
		sem_wait(data->semfork);
		print_b(data, "has taken a fork");
		print_b(data, "is eating");
		
		sem_wait(data->semlasteat);
		data->last_eat = my_time() - data->start_time;
		printf("last eat: %lld\n", data->last_eat);
		sem_post(data->semlasteat);
		my_sleep(data->time_to_eat);
		
		// if (data->num_of_eat)
		// 	count_eat(data);
		sem_post(data->semfork);
		sem_post(data->semfork);
		print_b(data, "is sleeping");
		my_sleep(data->time_to_sleep);
		print_b(data, "is thinking");
	}
}
