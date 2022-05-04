/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/05/04 16:43:57 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_odd_forks(t_philo *philo)
{
	t_data			*data;
	int				i;
	long long		now;

	i = 0;
	data = philo->data;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d has taken a left fork\n", now, philo->philo_index );
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d has taken a right fork\n", now, philo->philo_index );
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->print_mutex);
	now = my_time() - data->start_time;
	printf("%lld %d is eating\n", now, philo->philo_index );
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->l_fork);

	// start_eat()
	// if (pthread_mutex_unlock(philo->l_fork) != 0)
	// 	return (ft_error(2));
	// if (pthread_mutex_unlock(philo->r_fork) != 0)
	// 	return (ft_error(2));
	return (0);
}
// int	take_even_forks(t_philo *philo)
// {
// 	t_data			*data;
// 	int				i;
// 	long long		now;
// 	i = 0;
// 	data = philo->data;
// 	if (pthread_mutex_lock(philo->l_fork) != 0)
// 		return (ft_error(2));
// 	if (pthread_mutex_lock(&data->print_mutex) != 0)
// 		return (ft_error(2));
// 	now = my_time() - data->start_time;
// 	if (now < 0)
// 		return (-1);
// 	printf("%lld %d has taken a left fork\n", now, philo->philo_index + 1);
// 	if (pthread_mutex_unlock(&data->print_mutex) != 0)
// 		return (ft_error(2));
// 	if (pthread_mutex_lock(philo->r_fork) != 0)
// 		return (ft_error(2));
// 	if (pthread_mutex_lock(&data->print_mutex) != 0)
// 		return (ft_error(2));
// 	now = my_time() - data->start_time;
// 	if (now < 0)
// 		return (-1);
// 	printf("%lld %d has taken a right fork\n", now, philo->philo_index + 1);
// 	if (pthread_mutex_unlock(&data->print_mutex) != 0)
// 		return (ft_error(2));
// 	if (pthread_mutex_unlock(philo->l_fork) != 0)
// 		return (ft_error(2));
// 	if (pthread_mutex_unlock(philo->r_fork) != 0)
// 		return (ft_error(2));
// 	return (0);
// }
int	take_forks(t_philo *philo)
{
	if (philo->philo_index % 2 != 0)
	{
		//usleep(2500);
		take_odd_forks(philo);
	}
	else
	{
		my_sleep(10);
		take_odd_forks(philo);
	}
	return (0);
}

void	*philo_action(void *philo)
{
	t_philo *tmp_philo;

	tmp_philo = (t_philo *)philo;
	while (1)
	{
		if (take_forks(tmp_philo) != 0)
			return ((void *)-1);
	}
	return ((void *)0);
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&(data->id[i]), NULL, &philo_action, &(data->philo[i])) != 0)
			return (ft_error(2));
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->id[i], &data->result) != 0)
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

	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		ft_error(2);
	free(data);
	return (0);
}
