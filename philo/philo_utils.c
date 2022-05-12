/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:43:36 by marlean           #+#    #+#             */
/*   Updated: 2022/05/12 10:46:30 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_print(char *str, t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->data->my_mutex);
	now = my_time() - philo->data->start_time;
	printf("%lld %d %s\n", now, philo->index, str);
	pthread_mutex_unlock(&philo->data->my_mutex);
}

int	ft_error(int num)
{
	//check if mutex needed
	if (num == 1)
		write(1, "Wrong input\n", 12);
	else if (num == 2)
		write (1, "Mutex error\n", 12);
	else if (num == 3)
		write (1, "Malloc error\n", 13);
	else if (num == 4)
		write(1, "Pthread error\n", 14);
	else
		write (1, "Error\n", 6);
	return (-1);
}

long long	my_time(void)
{
	struct timeval	tv;
	long long		current_time;
	//include mutex

	if (gettimeofday(&tv, NULL) != 0)
		return (ft_error(4));
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time);
}

void	my_sleep(int ms)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, 0);
	gettimeofday(&now, 0);
	while (((now.tv_sec - start.tv_sec) * 1000 +
		(now.tv_usec - start.tv_usec) / 1000) < ms)
		{
			usleep(10);
			gettimeofday(&now, 0);
		}
}
