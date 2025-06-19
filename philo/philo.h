#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

typedef struct s_table
{
	int				no_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_times_each_philosopher_must_eat;
	t_philo			**philos;
	t_fork			**forks;
}	t_table;


typedef struct s_philo
{
	int				id;
	t_info			*data;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_info
{
	int				is_full;
	long			meals_eaten;
	long			last_meal_time;
}	t_info;

int		init_table(int argc, char **argv, t_table *table);
long	ft_atol(const char *str);

#endif
