/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/04/11 20:14:24 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_action(void *data)
{
	t_data	*tmp;
	int		i;

	i = 0;
	tmp = (t_data *)data;
	if (pthread_mutex_lock(&tmp->print_mutex) != 0)
		ft_error(2);
	printf("%lld %d has taken a fork\n", my_time() - tmp->start_time, tmp->philo->philo_index);
	if (pthread_mutex_unlock(&tmp->print_mutex) != 0)
		ft_error(2);
	return (0);
}

void	create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&(data->id[i]), NULL, &philo_action, data) != 0)
			ft_error(2);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->id[i], NULL) != 0)
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
	init_philo(data, argv);
	create_philo(data);
	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		ft_error(2);
	free(data);
	return (0);
}
