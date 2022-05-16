/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:29:36 by marlean           #+#    #+#             */
/*   Updated: 2022/05/16 19:34:14 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	init_data(t_data *data, char **argv)
{
	data->start_time = my_time();
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
	return (0);
}