#include "philo.h"

void	*my_thread_func(void *data)
{
	t_data *philo = data;
	pthread_mutex_t l_mutex;
	philo->left_mutex = &l_mutex;
	int n = *(philo->num);
	pthread_mutex_lock(philo->left_mutex);
	n++;
	pthread_mutex_unlock(philo->left_mutex);

	printf("this is here: %d", *(philo->num));
	*(philo->num) = n;
//	printf("thread1 wiht num: %d\n", (int)data);
	return (0);
}

void	go_to_threads(t_data *philo)
{
	void *returned;
	int	tmp = 0;
	pthread_t id;
	pthread_mutex_t my_mutex;
	philo->p_mutex = &my_mutex;
	*(philo->num) = tmp;
	
	pthread_mutex_init(philo->p_mutex, 0);
	printf("\nphilo %d\n", philo->num_philo);
	pthread_create(&id, 0, my_thread_func, &philo);

	pthread_mutex_lock(philo->p_mutex);

	while (tmp < 10)
		{//usleep(1);
			printf("tmp: %d\n", tmp);
			// pthread_mutex_unlock(philo->p_mutex);
			// pthread_mutex_lock(philo->p_mutex);
		}
	pthread_mutex_unlock(philo->p_mutex);

	pthread_join(id, &returned);
	// OR 
	//pthread_detach(id);
	
	// printf("\n\n thread id %d and returned %d\n\n", 
	// (int)id, (int)returned);
	// sleep(1);
}

void	init_philo(t_data *philo, char** argv)
{
	philo->num_philo = ph_atoi(argv[1]);
	if (philo->num_philo % 2 == 0)
		philo->num_forks = philo->num_philo;
	else
		philo->num_forks = philo->num_philo - 1;
	philo->die_time = ph_atoi(argv[2]);
	philo->eat_time = ph_atoi(argv[3]);
	philo->sleep_time = ph_atoi(argv[4]);
	if (argv[5])
	{
		philo->quant_eat = ph_atoi(argv[5]);
	}
	else 
		philo->quant_eat = -1;
}

int	main(int argc, char **argv)
{
	t_data philo;
//	struct timeval current_time;
	if (argc != 5 && argc != 6)
		return (0);
	init_philo(&philo, argv);
	if (philo.num_philo <= 0 || philo.die_time <= 0 ||
		philo.eat_time <= 0 || philo.sleep_time <= 0)
		write(1, "ERROR", 5);
	
	// gettimeofday(&current_time, NULL);
	// printf("seconds : %ld\nmicro seconds : %d",
    // current_time.tv_sec, current_time.tv_usec);

	go_to_threads(&philo);

	return (0);
}
