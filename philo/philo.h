/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:48:07 by marlean           #+#    #+#             */
/*   Updated: 2022/04/11 20:11:54 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h> //library for gettimeofday

//typedef pthread_mutex_t t_mutex;
typedef struct s_data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat;
	long long	start_time;
	pthread_mutex_t print_mutex;
	struct s_philo	*philo;
	pthread_t	*id;

}	t_data;

typedef struct s_philo
{
	int philo_index;
	pthread_mutex_t *forks;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	long long	last_eat;
}	t_philo;


//philo struct index_philo, left ford, right fork, сколько поели, последнее время приема пищи


int			ph_atoi(const char *str);
void		ft_error(int num);
void		init_each_philo(t_data *data);
void		init_philo(t_data *data, char **argv);
long long	my_time(void);

void		*philo_action(void *data);
void		create_philo(t_data *data);


#endif

//void *memset (void *destination, int c, size_t n);
//memset fill first n byte in dest wiht "int c"

//gettimeofday cat get the time and timezone.

//pthread_create -- создает поток
//pthread_join -- ожидает завершения потока
//pthread_detach -- отсоединить поток и вернуть ресурсы главному потоку
//если поток был отсоединен, то его уже нельзя джоинить и наоборот
//нельзя дважды вызывать детач от одного и того же потока.

//pthread_mutex_init -- инициализация мьютекса
//pthread_mutex_lock -- заблокировать мьютекс
//pthread_mutex_unlock -- разблокировать мьютекс
//pthread_mutex_destroy -- 
