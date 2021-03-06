/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:29:36 by marlean           #+#    #+#             */
/*   Updated: 2022/05/20 16:42:37 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	my_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	my_sleep(int ms)
{
	long	time;

	time = my_time();
	usleep(ms * 920);
	while (my_time() < time + ms)
		usleep(ms * 3);
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

void	init_semaphores(t_data *data)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem");
	sem_unlink("/sem_die");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_lasteat");
	data->semfork = sem_open("/sem_fork", O_CREAT, 0777, data->num_of_philo);
	data->sem = sem_open("/sem", O_CREAT, 0777, 1);
	data->semdie = sem_open("/sem_die", O_CREAT, 0777, 0);
	data->semeat = sem_open("/sem_eat", O_CREAT, 0777, 0);
	data->semlasteat = sem_open("/sem_lasteat", O_CREAT, 0777, 1);
}

int	init_data(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
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
	if (data->num_of_philo <= 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (ft_error(1));
	data->pid_philo = malloc(sizeof(int) * data->num_of_philo);
	if (!data->pid_philo)
		return (ft_error(2));
	memset(data->pid_philo, 0, sizeof(int) * data->num_of_philo);
	init_semaphores(data);
	return (0);
}
