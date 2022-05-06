/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:29:09 by marlean           #+#    #+#             */
/*   Updated: 2022/05/06 13:33:58 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	burn_them_all(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		return (ft_error(2));
	if (pthread_mutex_destroy(&data->eat) != 0)
		return (ft_error(2));
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (ft_error(2));
		i++;
	}
	return (0);
}