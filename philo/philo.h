#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>

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
	print_mutex is used to print messages (so no 2 threads write in 
	the same time),
	death_mutex is used to check if a philosopher is dead (death_flag),
	all_philos_full_mutex is used to check if the simulation is 
	over (all_philos_full_flag),
	watchdog_thread is the thread of the "waiter" that is checking if
	the simulation is over
	(his thread is running in the same time as the philosophers threads)
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

/*
	used only to pass current philo from while loop and
	table to dinner routine as arguments in pthreads
 */
typedef struct s_dinner_args
{
	t_philo	*philo;
	t_table	*table;
}	t_dinner_args;

/**
 * @brief Convert a string to a long integer
 * @param str string to convert
 * @return long integer
 */
long			ft_atol(const char *str);

/**
 * @brief Set memory to a value
 * (I used this function to write 0 to the whole structs - default init)
 * @param b pointer to the memory to set
 * @param c value to set
 * @param len length of the memory to set
 * @return pointer to the memory where the value was set
 */
void			*ft_memset(void *b, int c, size_t len);

/**
 * @brief Get time in microseconds
 * @return time in microseconds
 */
long			get_time(void);

/**
 * @brief Precise usleep, so the program sleeps for the exact time 
 * (for better precision)
 * @param time_in_micro time in microseconds
 */
void			precise_usleep(long time_in_micro);

/**
 * @brief Initialize the table with the arguments given in input
 * @param argc number of arguments
 * @param argv arguments
 * @param table table to initialize
 * @return 0 if OK, 1 if malloc/mutex error
 */
int				init_table(int argc, char **argv, t_table *table);

/**
 * @brief Initialize the dinner arguments
 * for table and current philo in iteration so I can pass 
 * them to the dinner routine
 * @param table table to initialize
 * @return pointer to the dinner arguments
 */
t_dinner_args	*init_dinner_args(t_table *tabled);

/**
 * @brief Start the dinner - assign forks, initialize the 
 * threads and the watchdog threads
 * then start their routines
 * @param table table to use
 * @return 0 - success, 1 - malloc failed in init_dinner_args
 */
int				start_dinner(t_table *table);

/**
 * @brief Print a message if the simulation is not over
 * if I pass the MSG_DIED message, it will print it even if the simulation
 * is over because of subject requirements 
 * (if philo dies the message must be printed)
 * @param table table of the simulation
 * @param philo_id id of the philo
 * @param msg message to print defined in header file (philo.h)
 */
void			print_msg(t_table *table, int philo_id, char *msg);

/**
 * @brief Assign the forks to each philosopher
 * @param table table of the simulation
 */
void			assign_forks(t_table *table);

/**
 * @brief Put the forks down, when philo is done eating
 * @param philo philo to use
 * @param first_fork_id id of the first fork taken
 */
void			put_forks_down(t_philo *philo, int first_fork_id);

/**
 * @brief Print the message for the dinner when there is only one philo
 * @param table table of the simulation
 */
void			solo_dinner(t_table *table);

/**
 * @brief Routine of the watchdog thread, checks if the simulation is over
 * (if all the philosophers are alive and not full, else it will set the
 * either death_flag or all_philos_full_flag to 1)
 * @param arg pointer to the table
 * @return NULL
 */
void			*watchdog_routine(void *arg);

/**
 * @brief Check if the philo is full
 * @param table table of the simulation
 * @param philo philo to check
 * @return 
 * the last parameter of input was not set -> 0
 * the last parameter of input was set and philo is not full -> 0
 * the last parameter of input was set and philo is full -> 1
*/
int				is_philo_full(t_table *table, t_philo *philo);

/**
 * @brief Free the philosophers - destroy the mutexes and free the philosophers
 * @param table table of the simulation
*/
void			free_philos(t_table *table);

/**
 * @brief Free the forks - destroy the mutexes and free the forks
 * @param table table of the simulation
*/
void			free_forks(t_table *table);

/**
 * @brief Clean the table - clean the whole program
 * (philos, forks, mutexes, ...)
 * @param table table of the simulation
*/
void			clean_table(t_table *table);

/**
 * @brief Free the dinner arguments after the simulation is over
 * @param dinner_args pointer to the dinner arguments
*/
void			free_dinner_args(t_dinner_args *dinner_args);

/**
 * @brief Compares if the strings are equal
 * @param s1 string1
 * @param s2 string2
 * @return 0 if yes, 1 if not
 */
int				ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Think for a short period of time after philos sleep
 * @param table table of the simulation
 */
void			think(t_table *table);

#endif
