/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/05/11 12:29:04 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	my_time(void)
{
	struct timeval	tv;
	long long		current_time;
	//include mutex

	if (gettimeofday(&tv, NULL) != 0)
		return (ft_error(4));
	current_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (current_time);
}

int	my_sleep(int time)
{
	struct timeval	now;
	struct timeval	start;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	usleep(time * 900);
	while (((now.tv_sec * 1000000 + now.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec)) < time * 1000)
	{
		usleep(110);
		gettimeofday(&now, NULL);
	}
	return (0);
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&(data->id[i]), NULL,
				&philo_action, &(data->philo[i])) != 0)
			return (ft_error(2));
		if (pthread_detach(data->id[i]) != 0)
			return (ft_error(2));
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
	if (death_monitoring(data) == 0)
	{
		if (burn_them_all(data) != 0)
			return (1);
	}

	//monitoring death

	free(data);
	return (0);
}
