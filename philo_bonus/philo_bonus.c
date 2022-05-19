/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:37:24 by marlean           #+#    #+#             */
/*   Updated: 2022/05/19 16:49:21 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*par_check_eat(void *data_in)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_in;
	sem_wait(data->sem);
	while (i < data->num_of_philo)
	{
		sem_post(data->sem);
		sem_wait(data->semeat);
		sem_wait(data->sem);
		i++;
	}
	sem_post(data->semdie);
	return (NULL);
}

int	parent_control(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_eat)
	{
		if (pthread_create(&data->pthread_id, NULL, &par_check_eat, data) != 0)
			return (ft_error(4));
		if (pthread_detach(data->pthread_id) != 0)
			return (ft_error(4));
	}
	sem_wait(data->semdie);
	while (i < data->num_of_philo)
	{
		kill(data->pid_philo[i], SIGKILL);
		i++;
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
		data->ph_index = i + 1;
		data->pid_philo[i] = fork();
		if (data->pid_philo[i] == 0)
		{
			if (create_monitor(data))
				return (1);
			start_action(data);
		}
		else if (data->pid_philo[i] == -1)
		{
			while (--i >= 0)
				kill(data->pid_philo[i], SIGKILL);
			return (1);
		}
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
		return (ft_error(2));
	if (init_data(data, argv))
		return (1);
	if (create_philo(data))
		return (ft_error(3));
	if (parent_control(data))
		return (1);
	return (0);
}
