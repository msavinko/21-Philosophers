/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/04/11 12:48:25 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*philo_action(void *data)
{
	t_data *philo;
	philo = (t_data *)data;
	if (pthread_mutex_lock(philo->l_mutex) != 0)
		ft_error(2);

		printf("philo in my created thread: %d\n", philo->num_philo);
		
	if (pthread_mutex_unlock(philo->l_mutex) != 0)
		ft_error(2);
	return (0);
}

void	init_philo(t_data *philo, char** argv)
{
	philo->num_philo = ph_atoi(argv[1]);
	philo->time_to_die = ph_atoi(argv[2]);
	philo->time_to_eat = ph_atoi(argv[3]);
	philo->time_to_sleep = ph_atoi(argv[4]);
	if (argv[5])
		philo->quant_eat = ph_atoi(argv[5]);
	if (philo->num_philo % 2 == 0)
		philo->num_forks = philo->num_philo;
	else
		philo->num_forks = philo->num_philo - 1;
	philo->l_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->l_mutex)
		ft_error(3);
	if (pthread_mutex_init(philo->l_mutex, NULL) != 0)
		ft_error(2);
}

int	main(int argc, char **argv)
{
	t_data *philo;
	if (argc != 5 && argc != 6)
		ft_error(1);
	philo = malloc(sizeof(t_data));
	if (!philo)
		ft_error(3);
	init_philo(philo, argv);
	if (pthread_create(&philo->id, 0, philo_action, philo) != 0)
		ft_error(2);
	// if (pthread_detach(philo->id) != 0)
	// 	ft_error(2);
	if (pthread_join(philo->id, NULL) != 0)
		ft_error(2);
	if (pthread_mutex_destroy(philo->l_mutex) != 0)
		ft_error(2);
	// gettimeofday(&current_time, NULL);
	// printf("seconds : %ld\nmicro seconds : %d", current_time.tv_sec, current_time.tv_usec);
	free(philo);

	return (0);
}

//book 30.2.1 (627-686), 652 API
//stolyarov 7chapter (245-312)