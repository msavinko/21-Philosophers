/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:21:25 by marlean           #+#    #+#             */
/*   Updated: 2022/05/05 17:12:52 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_right_fork(t_philo *philo)
{
	t_data			*data;
	int				i;
	long long		now;

	i = 0;
	data = philo->data;
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d has taken a right fork\n", now, philo->index);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d has taken a left fork\n", now, philo->index);
	pthread_mutex_unlock(&data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	t_data		*data;
	long long	now;

	data = philo->data;
	if (philo->iam_last == 1 && data->num_of_philo % 2)
	{
		printf("RIGHT FIRST\n");
		take_right_fork(philo);
	}	
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d has taken a left fork\n", now, philo->index);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d has taken a right fork\n", now, philo->index);
	pthread_mutex_unlock(&data->print_mutex);
}

void	start_forks(t_philo *philo)
{
	if (philo->index % 2)
		usleep(500);
	take_forks(philo);
}

void	ph_eating(t_philo *philo)
{
	t_data		*data;
	long long	now;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d is eating\n", now, philo->index);
	my_sleep(data->time_to_eat);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ph_sleeping(t_philo *philo)
{
	t_data		*data;
	long long	now;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d is sleeping\n", now, philo->index);
	my_sleep(data->time_to_sleep);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_action(void *philo_in)
{
	t_philo	*philo;

	philo = (t_philo *)philo_in;
	while (1)
	{
		start_forks(philo);
		ph_eating(philo);
		ph_sleeping(philo);
		usleep(500);
	}
	return ((void *)0);
}
