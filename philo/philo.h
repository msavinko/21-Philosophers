/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:59:56 by marlean           #+#    #+#             */
/*   Updated: 2022/04/13 17:48:28 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	long long		start_time;
	pthread_mutex_t	print_mutex;
	struct s_philo	*philo;
	pthread_t		*id;
	void			*result;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_mutex_t *forks;
	int				philo_index;
	long long		last_eat;
}	t_philo;

int			ph_atoi(const char *str);
int			ft_error(int num);
int			init_each_philo(t_data *data);
int			init_philo(t_data *data, char **argv);
long long	my_time(void);

int			eat(t_philo *philo);
void		*philo_action(void *data);
void		create_philo(t_data *data);

#endif

//TODO
// correct initialize
// create correct num of philo
// create my usleep
// create my free function