#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int primes[10] = {2,3,5,7,11,13,17,19,23,29};
pthread_mutex_t mutex;

void* routine(void *arg)
{
	int index = *(int *) arg;

	printf("prime: %d\n", primes[index]);
//	free(arg);
	arg = arg + 2;
	return (arg);
}

int main(void)
{
	pthread_t th[10];
	int i;
//	int *res;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 10; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, (void *)&routine, a))
			return (1);
		//printf("started: %d\n", i);
	}
	for (i = 0; i < 10; i++)
	{
		int *r;
		if (pthread_join(th[i], (void **)&r))
			return (1);
	//	printf("finished and res: %d \n", *r);
		//free(res);
	}
	pthread_mutex_destroy(&mutex);

	return (0);
}