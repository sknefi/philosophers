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
# include <sys/wait.h>

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

/**
	contains the information about the philo with
	the pid of the philo process, so I could call SIGKILL on
	philo processes when the simulation is over (somebody died or
	all the philosophers are full)
 */
typedef struct s_philo
{
	int		id;
	int		is_full;
	long	meals_eaten;
	long	last_meal_time;
	pid_t	pid;
}	t_philo;

/**
	sems contains the semaphores for the forks and the print, 
	so I could tell processes (philos) to take or to put down forks
	and print_sem to print messages (only one philosopher can print at a time)
*/
typedef struct s_sems
{
	sem_t	*forks_sem;
	sem_t	*print_sem;
}	t_sems;

/**
	table contains the information about the philo with
	the pid of the philo process, so I could call SIGKILL on
	philo processes when the simulation is over (somebody died or
	all the philosophers are full)
*/
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

/*
	struct to pass to the philo_monitor function, so it could
	access the table and the philo from process
*/
typedef struct s_philo_monitor_args
{
	t_philo	*philo;
	t_table	*table;
}	t_philo_monitor_args;

/**
 * @brief Get time in microseconds
 * @return time in microseconds
 */
long	get_time(void);

/**
 * @brief Precise usleep, so the program sleeps for the exact time 
 * (for better precision)
 * @param time_in_micro time in microseconds
 */
void	precise_usleep(long time_in_micro);

/**
 * @brief Convert a string to a long integer
 * @param str string to convert
 * @return long integer
 */
long	ft_atol(const char *str);

/**
 * @brief Compare two strings
 * @param s1 first string
 * @param s2 second string
 * @return 0 if the strings are equal, s1-s2 if not equal
 */
int		ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Initialize the table with the arguments given in input
 * @param argc number of arguments
 * @param argv arguments
 * @param table table to initialize
 * @return 0 if OK, 1 if malloc error
 */
int		init_table(int argc, char **argv, t_table *table);

/**
 * @brief Frees everything from table + unlinks sems
 * @param table table to clean
 */
void	clean_table(t_table *table);

/**
 * @brief Kill all the philo processes when simulation is over (somebody died
 * or all philos are full)
 * @param table table to kill processes from (all the philo processes)
 */
void	kill_all_philo_processes(t_table *table);

/**
 * @brief Takes 2 forks from the middle of the table
 * @param table table to take forks from
 * @param philo philo to take forks from
 */
void	take_forks(t_table *table, t_philo *philo);

/**
 * @brief Puts down 2 forks from the middle of the table
 * @param table table to put down forks from
 */
void	put_forks_down(t_table *table);

/**
 * @brief Print a message if the simulation is not over
 * if I pass the MSG_DIED message, it will print it even if the simulation
 * is over because of subject requirements 
 * (if philo dies the message must be printed)
 * @param table table of the simulation
 * @param philo_id id of the philo
 * @param msg message to print defined in header file (philo.h)
 */
void	print_msg(t_table *table, int philo_id, char *msg);

/**
 * @brief Think for a short period of time after philos sleep
 * @param table table of the simulation
 */
void	think(t_table *table);

/**
 * @brief Check if the philo is full
 * @param table table of the simulation
 * @param philo philo to check
 */
int		is_philo_full(t_table *table, t_philo *philo);

/**
 * @brief Start the dinner - create processes for each philo
 * and start their routines where every philo has its own thread
 * to monitor if it dies or if it is full => simulation is over
 * (then kill all the processes)
 * @param table table to use
 * @return 0 - success, 1 - malloc failed in init_dinner_args
 */
int		start_dinner(t_table *table);

/**
 * @brief Solo dinner - only one philo, takes one fork and then dies
 */
void	solo_dinner(t_table *table);

/**
 * @brief Watchdog routine process - monitor if the simulation is over
 * (somebody died or all philos are full)
 * @param table table to monitor
 */
void	watchdog_routine(t_table *table);

#endif