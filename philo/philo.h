/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:59:56 by marlean           #+#    #+#             */
/*   Updated: 2022/05/06 11:19:30 by marlean          ###   ########.fr       */
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
	t_mutex			print_mutex;
	struct s_philo	*philo;
	pthread_t		*id;
	void			*result;
	t_mutex			*forks;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	t_mutex			*r_fork;
	t_mutex			*l_fork;
	int				index;
	long long		last_eat;
	int				iam_last;
}	t_philo;

void		ph_print(char *str, t_philo *philo);
int			ft_error(int num);
int			ph_atoi(const char *str);
int			init_each_philo(t_data *data);
int			init_philo(t_data *data, char **argv);


void		take_forks(t_philo *philo);
void		*philo_action(void *philo_in);
int			death_monitoring(t_data *data);

long long	my_time(void);
int			my_sleep(int time);
int			create_philo(t_data *data);

#endif

//TODO

// eat
// create my free function
// check death

//usleep 100000 = my_sleep 100
//15.06



//!!!!!!!!!!!!!!!!!
//time mutex??
//die mutex
