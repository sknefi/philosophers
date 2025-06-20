#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

# define R "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"
# define RES "\033[0m"

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				is_full;
	long			meals_eaten;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
}	t_philo;

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

// Function declarations
t_table	*init_table(int argc, char **argv);
long	ft_atol(const char *str);
void	clean_philos(t_table *table);
void	clean_forks(t_table *table);
void	clean_table(t_table *table);
void	*ft_memset(void *b, int c, size_t len);

void	print_philos(t_table *table);

#endif
