/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:21:25 by marlean           #+#    #+#             */
/*   Updated: 2022/05/11 12:55:02 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0) 
		usleep(500);
	if (philo->iam_last == 1 && philo->data->num_of_philo % 2)
	{
		pthread_mutex_lock(philo->r_fork);
		ph_print("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		ph_print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ph_print("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		ph_print("has taken a fork", philo);
	}
}

void	*philo_action(void *philo_in)
{
	t_philo	*philo;

	philo = (t_philo *)philo_in;

	while (1)
	{
		take_forks(philo);
		//include death_monitoring
		ph_print("is eating", philo);
		pthread_mutex_lock(&philo->data->my_mutex);
		philo->last_eat = my_time() - philo->data->start_time;
		pthread_mutex_unlock(&philo->data->my_mutex);
		my_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);

		pthread_mutex_lock(&philo->data->my_mutex);
		if (philo->data->num_of_eat)
			philo->i_eat++;
		pthread_mutex_unlock(&philo->data->my_mutex);

		ph_print("is sleeping", philo);
		my_sleep(philo->data->time_to_sleep);
		ph_print("is thinking", philo);
		usleep(500);
	}

	return ((void *)0);
}

int	death_monitoring(t_data *data)
{
	int	i;
	int	tmp_eat;
	
	tmp_eat = 0;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_mutex_lock(&data->my_mutex);
			if (data->philo[i].i_eat == data->num_of_eat )
				tmp_eat++;
			//printf("\n!!!!eat %d and num %d!!!!\n\n", tmp_eat, i);
			pthread_mutex_unlock(&data->my_mutex);
			usleep(500);
			i++;
		}
		if (tmp_eat == data->num_of_eat)
		{
			printf("\nFINISH\n");
			return (0);
		}
	}
	return (0);
}
