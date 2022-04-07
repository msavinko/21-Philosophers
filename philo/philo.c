/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:47 by marlean           #+#    #+#             */
/*   Updated: 2022/04/07 16:57:42 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*my_thread_func(void *data)
{
	t_data *philo;
	philo = (t_data *)data;
	if (pthread_mutex_lock(philo->l_mutex) != 0)
		return (0);

		printf("philo in my created thread: %d\n", philo->num_philo);
	if (pthread_mutex_unlock(philo->l_mutex) != 0)
		return (0);
	return (0);
}

void	init_philo(t_data *philo, char** argv)
{
	philo->l_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->l_mutex)
		return ;
	if (pthread_mutex_init(philo->l_mutex, NULL) != 0)
		return ;
	philo->num_philo = ph_atoi(argv[1]);
	if (philo->num_philo % 2 == 0)
		philo->num_forks = philo->num_philo;
	else
		philo->num_forks = philo->num_philo - 1;
	philo->die_time = ph_atoi(argv[2]);
	philo->eat_time = ph_atoi(argv[3]);
	philo->sleep_time = ph_atoi(argv[4]);
	if (argv[5])
		philo->quant_eat = ph_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_data *philo;
	philo = malloc(sizeof(t_data));
	if (!philo)
		return (0);
	if (argc != 5 && argc != 6)
		return (0);
	init_philo(philo, argv);

	// if (philo.num_philo <= 0 || philo.die_time <= 0 ||
	// 	philo.eat_time <= 0 || philo.sleep_time <= 0)
	// 	write(1, "ERROR", 5);
	if (pthread_create(&philo->id, 0, my_thread_func, philo) != 0)
		return (0);
	if (pthread_detach(philo->id) != 0)
		return (0);
	// if (pthread_mutex_destroy(philo->l_mutex) != 0)
	// 	return (0);
	free(philo->l_mutex);
	free(philo);
	return (0);
}

//book 30.2.1