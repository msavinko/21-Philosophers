/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:37:24 by marlean           #+#    #+#             */
/*   Updated: 2022/05/17 20:12:54 by marlean          ###   ########.fr       */
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
	sem_wait(data->semprint);
	data->now = my_time() - data->start_time;
	printf("%lld %d %s\n", data->now, data-> ph_index, str);
	sem_post(data->semprint);
}

void	count_eat(t_data *data)
{
	data->i_eat++;
	if (data->i_eat == data->num_of_eat)
		sem_post(data->semeat);
}

void	start_action(t_data *data)
{
	if (data->ph_index % 2 == 0)
		usleep(500);
	while (1)
	{	sem_wait(data->semfork);
		print_b(data, "has taken a fork");
		sem_wait(data->semfork);
		print_b(data, "has taken a fork");
		print_b(data, "is eating");
		my_sleep(data->time_to_eat);
		if (data->num_of_eat)
			count_eat(data);
		sem_post(data->semfork);
		sem_post(data->semfork);
		print_b(data, "is sleeping");
		my_sleep(data->time_to_sleep);
		print_b(data, "is thinking");

	}

}

void	monitoring(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		sem_wait(data->semeat);
		
		// kill(data->pid_philo[i], SIGKILL);
		// sem_wait(data->semdie);
		i++;
	}
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	// data->pid_philo[0] = fork();
	// data->ph_index = i;
	// printf("ONE %d index and PID: %d\n", data->ph_index, data->pid_philo[0]);

	while (i < data->num_of_philo) // && data->pid_philo[i] != 0)
	{
		data->ph_index = i + 1;
		data->pid_philo[i] = fork();
		if (data->pid_philo[i] != 0)
		{
			printf("PARENT %d index and PID: %d\n", data->ph_index, data->pid_philo[i]);
			
		}
		else
		{
			printf("CHILD %d index and PID: %d\n", data->ph_index, data->pid_philo[i]);

		}
		i++;
	}

		// printf("FINAL %d index and PID: %d\n", data->ph_index, data->pid_philo);

		// if (data->pid_philo == 0)
		// {

		// 	start_action(data);
		// }
		// else
		// {

		// 	monitoring(data);
		// }
		// i++;
	
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