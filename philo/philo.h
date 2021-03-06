/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:59:56 by marlean           #+#    #+#             */
/*   Updated: 2022/05/16 12:50:04 by marlean          ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;
typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	long long		start_time;
	t_mutex			my_mutex;
	struct s_philo	*philo;
	pthread_t		*id;
	t_mutex			*forks;
	int				death;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	t_mutex			*r_fork;
	t_mutex			*l_fork;
	int				index;
	long long		last_eat;
	int				iam_last;
	int				i_eat;
}	t_philo;

void		ph_print(char *str, t_philo *philo);
int			ft_error(int num);
int			ph_atoi(const char *str);
void		init_each_philo(t_data *data);
int			init_philo(t_data *data, char **argv);
void		take_forks(t_philo *philo);
void		*philo_action(void *philo_in);
int			monitoring(t_data *data);
long long	my_time(void);
void		my_sleep(int time);
int			create_philo(t_data *data);
int			burn_them_all(t_data *data);

#endif
