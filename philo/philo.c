/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/05/12 15:35:39 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_data *data)
{
	int	i;
	int	tmp_eat;

	tmp_eat = 0;
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->my_mutex);
		if (data->philo[i].i_eat >= data->num_of_eat )
			tmp_eat++;
		pthread_mutex_unlock(&data->my_mutex);
		i++;

	}
	if (tmp_eat == data->num_of_philo)
	{
		pthread_mutex_lock(&data->my_mutex);
		data->death = 1;
		//data->check = 1;
		printf("\nFINISH\n");
		// burn_them_all(data);
		return (1);
	}
	return (0);
}

int	check_death(t_data *data, int i)
{
	long long	time_diff;
	long long	now;
	
	pthread_mutex_lock(&data->my_mutex);
	now = my_time() - data->start_time;
	time_diff = now - data->philo[i].last_eat;
	//printf("%lld %d %s\n", now, philo->index, str);
	
	// printf("philo %d time diff %lld now and time to die %d\n", data->philo[i].index, time_diff, data->time_to_die);
	pthread_mutex_unlock(&data->my_mutex);
	if (time_diff >= data->time_to_die)
	{
		pthread_mutex_lock(&data->my_mutex);
		ph_print("died", &data->philo[i]);
		printf("DEAD\n");
		data->death = 1;
		// pthread_mutex_unlock(&data->my_mutex);

		return (1);
	}
	return (0);
}

int	monitoring(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < data->num_of_philo)
		{
			if (check_death(data, i) == 1)
				break ;
			if (data->num_of_eat)
			{
				if (check_eat(data) == 1)
					break ;
			}
			i++;
		}
		i = 0;
		usleep(10);
	}
	return (0);
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = my_time();
	while (i < data->num_of_philo)
	{
		if (pthread_create(&(data->id[i]), NULL,
				&philo_action, &(data->philo[i])) != 0)
			return (ft_error(4));
		if (pthread_detach(data->id[i]) != 0)
			return (ft_error(4));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(3));
	if (init_philo(data, argv) != 0)
		return (1);
	if (create_philo(data) != 0)
		return (1);
	if (monitoring(data) != 0)
		return (1);
	burn_them_all(data);
	return (0);
}

