/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:35:26 by marlean           #+#    #+#             */
/*   Updated: 2022/05/17 19:08:11 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	long long	start_time;
	long long	now;
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_eat;
	sem_t		*semfork;
	sem_t		*semprint;
	sem_t		*semeat;
	sem_t		*semdie;
	int			*pid_philo;
	int			ph_index;
	int			i_eat;
}	t_data;

long long	my_time(void);
void		my_sleep(int ms);
int			ph_atoi(const char *str);
void		init_semaphores(t_data *data);
int			init_data(t_data *data, char **argv);

int		ft_error(int num);
void	print_b(t_data *data, char *str);
void	start_action(t_data *data);
void	monitoring(t_data *data);
int		create_philo(t_data *data);



#endif

// waitpid Функция waitpid приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс, указанный в параметре pid, не завершит выполнение, или пока не появится сигнал, который либо завершает текущий процесс либо требует вызвать функцию-обработчик
// sem_open, sem_close,
// sem_post, sem_wait, sem_unlink

// API LINUX semaphores 969-973-982
// ipcs to check opened semaphores
// S_IRWXU  00700 user (file owner) has read, write and execute permission
// kwarpath proverka