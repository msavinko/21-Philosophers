/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:21:25 by marlean           #+#    #+#             */
/*   Updated: 2022/05/13 12:49:26 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 != 0)
	{
		if (philo->iam_last == 1 && philo->data->num_of_philo % 2 != 0)
			usleep(700);
		pthread_mutex_lock(philo->l_fork);
		ph_print("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		ph_print("has taken a fork", philo);
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philo->r_fork);
		ph_print("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		ph_print("has taken a fork", philo);
	}
}

void	*philo_action(void *philo_in)
{
	t_philo	*philo;

	philo = (t_philo *)philo_in;
	// pthread_mutex_lock(&philo->data->my_mutex);
	while (1)
	{
		take_forks(philo);
		ph_print("is eating", philo);

		pthread_mutex_lock(&philo->data->my_mutex);
		philo->last_eat = my_time() - philo->data->start_time;
		// printf("philo: %d last time eat: %lld\n", philo->index, philo->last_eat);
		pthread_mutex_unlock(&philo->data->my_mutex);

		my_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);

		pthread_mutex_lock(&philo->data->my_mutex);
		if (philo->data->num_of_eat > philo->i_eat)
			philo->i_eat++;
		pthread_mutex_unlock(&philo->data->my_mutex);

		ph_print("is sleeping", philo);
		my_sleep(philo->data->time_to_sleep);
		ph_print("is thinking", philo);
		// pthread_mutex_lock(&philo->data->my_mutex);
		usleep(10);
	}
	// pthread_mutex_unlock(&philo->data->my_mutex);
	return ((void *)0);
}
