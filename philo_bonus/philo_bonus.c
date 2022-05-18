/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:37:24 by marlean           #+#    #+#             */
/*   Updated: 2022/05/18 16:36:10 by marlean          ###   ########.fr       */
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
	sem_wait(data->semprint);
	data->now = my_time() - data->start_time;
	printf("%lld %d %s\n", data->now, data->ph_index, str);
	sem_post(data->semprint);
}

void	parent_control(t_data *data) //only parent process goes here
{
	if (data->num_of_eat)
	{
		//count and check eating
	}
	else
	{
		int	i;

		i = 0;
		sem_wait(data->semdie);
		while (i < data->num_of_philo)
		{
			kill(data->pid_philo[i], SIGKILL);
			i++;
		}
	}
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->pid_philo[0] = 1;
	while (i < data->num_of_philo && data->pid_philo[i - 1] != 0)
	{
		data->pid_philo[i] = fork();
		data->ph_index = i + 1;
		if (data->pid_philo[i] == 0) // child process
		{
			if (create_monitor(data))
				return (1);
			start_action(data);
		}
		else if (data->pid_philo[i] == -1)
		{
			while (--i >- 0)
				kill(data->pid_philo[i], SIGKILL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(2));
	if (init_data(data, argv))
		return(1);
	if (create_philo(data))
		return (ft_error(3));
	parent_control(data);
	return (0);
}