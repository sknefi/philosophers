#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

// philo -> philosopher

// colors for the messages
# define R "\033[31m"
# define Y "\033[33m"
# define G "\033[32m"
# define B "\033[34m"
# define O "\033[38;5;208m"
# define RES "\033[0m"

// // messages for the print_msg function
// # define MSG_EAT  "is eating"
// # define MSG_SLEEP "is sleeping"
// # define MSG_THINK "is thinking"
// # define MSG_FORK "has taken a fork"
// # define MSG_DIED "died"

// // error messages
// # define ERR_IN "Error: Invalid input\n"
// # define ERR_ARG "Error: Invalid number of arguments\n"
// # define ERR_GEN "Error: General error (malloc, mutex, etc.)\n"

// /* I love norminette
# define MSG_EAT  G "is eating" RES
# define MSG_SLEEP Y "is sleeping" RES
# define MSG_THINK O "is thinking" RES
# define MSG_FORK B "has taken a fork" RES
# define MSG_DIED R "died" RES
# define ERR_IN R "Error: Invalid input\n" RES
# define ERR_ARG R "Error: Invalid number of arguments\n" RES
# define ERR_GEN R "Error: General error (malloc, mutex, etc.)\n" RES

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"

# define PID_NOT_INIT -2
typedef struct s_philo
{
	int		id;
	int		is_full;
	long	meals_eaten;
	long	last_meal_time;
	pid_t	pid;
}	t_philo;

typedef struct s_sems
{
	sem_t	*forks_sem;
	sem_t	*print_sem;
}	t_sems;

typedef struct s_table
{
	int		no_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_times_each_philosopher_must_eat;

	long	start_time;

	t_sems	*sems;
	t_philo	*philos;
}	t_table;

long	get_time(void);
long	ft_atol(const char *str);
void	precise_usleep(long time_in_micro);
int		ft_strcmp(const char *s1, const char *s2);
int		init_table(int argc, char **argv, t_table *table);
int		start_dinner(t_table *table);
void	clean_table(t_table *table);
void	solo_dinner(t_table *table);
void	take_forks(t_table *table, t_philo *philo);
void	put_forks_down(t_table *table);
void	print_msg(t_table *table, int philo_id, char *msg);
void	watchdog_routine(t_table *table);
int		is_philo_full(t_table *table, t_philo *philo);
void	kill_all_philo_processes(t_table *table);

#endif