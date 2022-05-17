/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:37:24 by marlean           #+#    #+#             */
/*   Updated: 2022/05/17 14:52:03 by marlean          ###   ########.fr       */
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

void	print_b(t_data *data, char *str)
{
	sem_wait("/sem_print");
	data->now = my_time() - data->start_time;
	printf("%lld %d %s\n", data->now, data-> ph_index, str);
	sem_post("/sem_print");
}

void	start_action(t_data *data)
{
	sem_wait("/sem_fork");
	sem_wait("/sem_fork");
	print_b(data, "has taken a fork");
	my_sleep(data->time_to_eat);
	sem_post("/sem_fork");
	sem_post("/sem_fork");




}

int	create_philo(t_data *data)
{
	int	i;

	i = 1;
	data->pid_philo = fork();
	data->ph_index = i;
	while (i < data->num_of_philo && data->pid_philo != 0)
	{
		data->ph_index = i + 1;
		data->pid_philo = fork();
		i++;
	}
	if (data->pid_philo == 0)
	{
		start_action(data);
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