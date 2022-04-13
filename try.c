#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#define PHT_SIZE 5

// Объявим структуру «философ», которая будет хранить имя философа 
// и номера вилок, которые он может взять.
typedef struct philosopher_tag {
    const char *name;
    unsigned int left_fork;
    unsigned int right_fork;
} philosopher_t;

// Далее структура «стол», которая состоит их массива вилок. 
// В качестве вилки будет выступать мьютекс. 
// Блокировка мьютекса означает «взять вилку», а разблокировка 
// «положить её обратно».
typedef struct table_tag {
    pthread_mutex_t forks[PHT_SIZE];
} table_t;

// Кроме того, для передачи этих параметров в поток объединим их в структуру
typedef struct philosopher_args_tag {
    philosopher_t *philosopher;
    table_t *table;
} philosopher_args_t;

// Две вспомогательные функции инициализации
void init_philosopher(philosopher_t *philosopher, const char *name, 
		unsigned left_fork, unsigned right_fork) {
    philosopher->name = name;
    philosopher->left_fork = left_fork;
    philosopher->right_fork = right_fork;
}
 
void init_table(table_t *table) {
    size_t i;
    for (i = 0; i < PHT_SIZE; i++) {
        pthread_mutex_init(&table->forks[i], NULL);
    }
}

// И наша основная функция, eat, которая моделирует обед
void* eat(void *args) {
    philosopher_args_t *arg = (philosopher_args_t*) args;
    philosopher_t *philosopher = arg->philosopher;
    table_t *table = arg->table;
 
    printf("%s started dinner\n", philosopher->name);
 
    pthread_mutex_lock(&table->forks[philosopher->left_fork]);
    pthread_mutex_lock(&table->forks[philosopher->right_fork]);
 
    printf("%s is eating\n", philosopher->name);
 
    pthread_mutex_unlock(&table->forks[philosopher->right_fork]);
    pthread_mutex_unlock(&table->forks[philosopher->left_fork]);
 
    printf("%s finished dinner\n", philosopher->name);
	return (0);
}

// Теперь осталось самое малое – инициализировать 5 потоков и запустить их.
int main() {
    pthread_t threads[PHT_SIZE];
 
    philosopher_t philosophers[PHT_SIZE];
    philosopher_args_t arguments[PHT_SIZE];
    table_t table;
 
    size_t i;
 
    init_table(&table);
 
    init_philosopher(&philosophers[0], "Alice", 0, 1);
    init_philosopher(&philosophers[1], "Bob", 1, 2);
    init_philosopher(&philosophers[2], "Clark", 2, 3);
    init_philosopher(&philosophers[3], "Denis", 3, 4);
    init_philosopher(&philosophers[4], "Eugin", 4, 0);
 
    for (i = 0; i < PHT_SIZE; i++) {
        arguments[i].philosopher = &philosophers[i];
        arguments[i].table = &table;
    }
 
    for (i = 0; i < PHT_SIZE; i++) {
        pthread_create(&threads[i], NULL, eat, &arguments[i]);
    }
 
    for (i = 0; i < PHT_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

	int k = 1;
    wait(&k);
	return (0);
}


//gcc try.c && ./a.out