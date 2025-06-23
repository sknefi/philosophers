#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
#include <string.h>

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
 * @param philo_mutex I have to lock the philo with this mutex, because
 * not just philo is accessing data but also watchdog
*/
typedef struct s_philo
{
	int				id;
	int				is_full;
	long			meals_eaten;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
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
	pthread_t		watchdog_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	all_philos_full_mutex;
}	t_table;

// used only to pass current philo from while loop and table to dinner routine as arguments in pthreads
typedef struct s_dinner_args
{
	t_philo	*philo;
	t_table	*table;
}	t_dinner_args;


// Function declarations
int		init_table(int argc, char **argv, t_table *table);
long	ft_atol(const char *str);
long	get_time(void);
void	print_msg(t_table *table, int philo_id, char *msg);
void	free_philos(t_table *table);
void	free_forks(t_table *table);
void	clean_table(t_table *table);
void	*ft_memset(void *b, int c, size_t len);
int		start_dinner(t_table *table);
void	precise_usleep(long time_in_micro);

void	assign_forks(t_table *table);
int		is_philo_full(t_table *table, t_philo *philo);
void	*watchdog_routine(void *arg);
t_dinner_args	*init_dinner_args(t_table *tabled);
void	free_dinner_args(t_dinner_args *dinner_args);
void	put_forks_down(t_philo *philo, int first_fork_id);
void	*watchdog_routine(void *arg);
#endif
