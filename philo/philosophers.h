#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> //library for gettimeofday

//typedef pthread_mutex_t t_mutex;

typedef struct s_philo
{
	int	num_philo;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	quant_eat;
	int	num_forks;
	pthread_mutex_t *p_mutex;
	pthread_mutex_t *left_mutex;
	pthread_mutex_t *right_mutex;
	struct timeval last_eat;
	int	*num;

}				t_philo;



int	ph_atoi(const char *str);
void	init_philo(t_philo *philo, char** argv);



#endif

//void *memset (void *destination, int c, size_t n);
//memset fill first n byte in dest wiht "int c"

//gettimeofday cat get the time and timezone.

//pthread_create -- создает поток
//pthread_join -- ожидает завершения потока
//pthread_detach -- отсоединить поток и вернуть ресурсы главному потоку
//если поток был отсоединен, то его уже нельзя джоинить и наоборот
//нельзя дважды вызывать детач от одного и того же потока.

// STOP VIDEO ON 1.24


//pthread_mutex_init -- инициализация мьютекса
//pthread_mutex_lock -- заблокировать мьютекс
//pthread_mutex_unlock -- разблокировать мьютекс
//pthread_mutex_destroy -- 
