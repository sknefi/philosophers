#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

# define R "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"
# define RES "\033[0m"

/**
 * fork of a philosopher
 * @param id the id of the fork
 * @param mutex the mutex of the fork so no 2 philosophers 
 * use the same fork at the same time
*/
typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

/** 
 * philosopher as a thread with 2 forks 
 * @param id the id of the philosopher
 * @param is_full a flag to check if the philosopher is full 
 * (if the last parameter of input was given)
 * @param meals_eaten the number of meals the philosopher has eaten
 * (to check if he is full)
*/
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

/*
	table contains all the information about the program,
	philos contains all the information about the philosophers,
	forks contains all the information about the forks,
	print_mutex is used to print messages (so no 2 threads write in the same time),
	death_mutex is used to check if a philosopher is dead (death_flag),
	all_philos_full_mutex is used to check if the simulation is over (all_philos_full_flag)
*/
typedef struct s_table
{
	int				death_flag;
	int				no_philosophers;
	int				all_philos_full_flag;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_times_each_philosopher_must_eat;
	t_fork			**forks;
	t_philo			**philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	all_philos_full_mutex;
}	t_table;

// Function declarations
int	init_table(int argc, char **argv, t_table *table);
long	ft_atol(const char *str);
long	get_time(void);
void	print_msg(t_table *table, int philo_id, char *msg);
void	clean_philos(t_table *table);
void	clean_forks(t_table *table);
void	clean_table(t_table *table);
void	*ft_memset(void *b, int c, size_t len);
void	start_dinner(t_table *table);

#endif
