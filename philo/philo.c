/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/04/11 18:42:59 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	my_time(void)
{
	struct timeval	tv;
	long long		calc_time;

	gettimeofday(&tv, NULL);
	calc_time = tv.tv_sec*1000LL + tv.tv_usec/1000; // calculate milliseconds
   // printf("timestamp milliseconds: %lld\n", calc_time);
	return (calc_time);
}

void	*philo_action(void *data)
{
	t_data *tmp;
	tmp = (t_data *)data;

	if (pthread_mutex_lock(&tmp->print_mutex) != 0)
		ft_error(2);

		
		printf("philo in my created thread: %d\n", tmp->num_of_philo);
		
	if (pthread_mutex_unlock(&tmp->print_mutex) != 0)
		ft_error(2);

	

	return (0);
}


void	init_philo(t_data *data, char** argv)
{

	data->num_of_philo = ph_atoi(argv[1]);
	data->time_to_die = ph_atoi(argv[2]);
	data->time_to_eat = ph_atoi(argv[3]);
	data->time_to_sleep = ph_atoi(argv[4]);
	if (argv[5])
		data->num_of_eat = ph_atoi(argv[5]);
	data->start_time = my_time();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		ft_error(2);
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		ft_error(3);
	data->philo->id = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!data->philo->id)
		ft_error(3);
	
}


void	create_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
	if (pthread_create(&data->philo->id, 0, philo_action, data) != 0)
		ft_error(2);
	if (pthread_join(data->philo->id, NULL) != 0)
		ft_error(2);
	i++;
	}
}

int	main(int argc, char **argv)
{
	t_data *data;


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
