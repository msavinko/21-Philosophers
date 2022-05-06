/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:29:09 by marlean           #+#    #+#             */
/*   Updated: 2022/05/06 16:03:20 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	burn_them_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&data->print_mutex);
	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		return (ft_error(2));
	pthread_mutex_unlock(&data->eat);
	if (pthread_mutex_destroy(&data->eat) != 0)
		return (ft_error(2));
	while (i < data->num_of_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (ft_error(2));
		i++;
	}
	return (0);
}