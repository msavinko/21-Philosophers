/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:37:24 by marlean           #+#    #+#             */
/*   Updated: 2022/05/17 14:19:43 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(int num)
{
	if (num == 1)
		write(1, "Wrong arguments\n", 16);
	else if (num == 2)
		write(1, "Malloc error\n", 13);
	return (1);
}

int	create_philo(t_data *data)
{
	int	i;

	i = 1;
	data->pid_philo = fork();

	while (i < data->num_of_philo && data->pid_philo != 0)
	{
		data->pid_philo = fork();
		i++;
	}
	if (data->pid_philo == 0)
	{
		printf("i'm a child process %d \n", data->pid_philo);
		start_eating(data);
	}
	else
	{
		printf("i'm a parent %d \n", data->pid_philo);

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
	init_data(data, argv);
	create_philo(data);

	return (0);
}