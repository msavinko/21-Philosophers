#include "philosophers.h"

void	*my_thread_func(void *data)
{
	printf("thread1 wiht num: %d\n", (int)data);
	return ((void *)528);
}

void	go_to_threads(t_philo *philo)
{
	pthread_t id;
	void *returned;

	printf("\nphilo %d\n", philo->num_philo);
	pthread_create(&id, 0, my_thread_func, (void *)11);
	
	pthread_join(id, &returned);
	// OR 
	pthread_detach(id);
	
	printf("\n\n thread id %d and returned %d\n\n", 
	(int)id, (int)returned);
	// sleep(1);
}

void	init_philo(t_philo *philo, char** argv)
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
	//	printf("quantity of eat: %d\n", philo->quant_eat);
	}
	else 
		philo->quant_eat = -1;
	
	// printf("num of philo: %d\n", philo->num_philo);
	// printf("time to die: %d\n", philo->die_time);
	// printf("time to eat: %d\n", philo->eat_time);
	// printf("time to sleep: %d\n", philo->sleep_time);
	// printf("forks: %d\n", philo->num_forks);
}

int	main(int argc, char **argv)
{
	t_philo philo;
//	struct timeval current_time;
	if (argc != 5 && argc != 6)
		return (0);
	init_philo(&philo, argv);
	if (philo.num_philo <= 0 || philo.die_time <= 0 ||
		philo.eat_time <= 0 || philo.sleep_time <= 0)
		printf("ERROR ");
	
	// gettimeofday(&current_time, NULL);
	// printf("seconds : %ld\nmicro seconds : %d",
    // current_time.tv_sec, current_time.tv_usec);

	go_to_threads(&philo);

	return (0);
}

//program must not have data races.
