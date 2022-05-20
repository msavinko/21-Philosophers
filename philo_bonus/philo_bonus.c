/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:37:24 by marlean           #+#    #+#             */
/*   Updated: 2022/05/20 12:53:44 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*par_check_eat(void *data_in)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_in;
	sem_wait(data->sem);
	while (i < data->num_of_philo)
	{
		sem_post(data->sem);
		sem_wait(data->semeat);
		sem_wait(data->sem);
		i++;
	}
	sem_post(data->semdie);
	return (NULL);
}

void	finish_sem(t_data *data)
{
	sem_post(data->semeat);
	sem_close(data->semeat);
	sem_close(data->semfork);
	sem_post(data->sem);
	sem_close(data->sem);
	sem_close(data->semdie);
	sem_unlink("/sem_fork");
	sem_unlink("/sem");
	sem_unlink("/sem_die");
	sem_unlink("/sem_eat");
	if (data->pid_philo)
		free(data->pid_philo);
	if (data)
		free(data);
}

int	parent_control(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_eat)
	{
		if (pthread_create(&data->pthread_id, NULL, &par_check_eat, data) != 0)
			return (ft_error(4));
		if (pthread_detach(data->pthread_id) != 0)
			return (ft_error(4));
	}
	sem_wait(data->semdie);
	while (i < data->num_of_philo)
	{
		kill(data->pid_philo[i], SIGKILL);
		i++;
	}
	return (0);
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = my_time();
	while (i < data->num_of_philo)
	{
		data->ph_index = i + 1;
		data->pid_philo[i] = fork();
		if (data->pid_philo[i] == 0)
			start_action(data);
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
		return (ft_error(2));
	if (init_data(data, argv))
		return (1);
	if (create_philo(data))
		return (ft_error(3));
	if (parent_control(data))
		return (1);
	finish_sem(data);
	return (0);
}
