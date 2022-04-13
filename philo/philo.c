/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/04/13 17:49:12 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	eat(t_philo *philo)
{
	t_data			*data;
	int				i;
	long long		now;
	i = 0;
	data = philo->data;
	if (pthread_mutex_lock(&data->print_mutex) != 0)
		ft_error(2);
	now = my_time() - data->start_time;
	if (now < 0)
		return (now);
	printf("%lld %d has taken a fork\n", now, philo->philo_index);
	if (pthread_mutex_unlock(&data->print_mutex) != 0)
		ft_error(2);
	return (0);
}

void	*philo_action(void *philo)
{
	t_philo *tmp_philo;

	tmp_philo = (t_philo *)philo;
	if (eat(tmp_philo) != 0)
		return ((void *)-1);


	return ((void *)0);
}

void	create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&(data->id[i]), NULL, &philo_action, &(data->philo[i])) != 0)
			ft_error(2);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->id[i], &data->result) != 0)
			ft_error(2);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		ft_error(1);
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(3);
	if (init_philo(data, argv) != 0)
		return (-1);
	
	create_philo(data);


	// if (pthread_mutex_destroy(&data->print_mutex) != 0)
	// 	ft_error(2);
	//free(data);
	return (0);
}
