#include "philo.h"

// return the id of a first fork so when putting them down i put the first one down first
static int	take_forks(t_table *table, t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&first_fork->mutex);
	print_msg(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&second_fork->mutex);
	print_msg(table, philo->id, "has taken a fork");
	return (first_fork->id);
}

// check if philo died
// implement watchdog - somebody died, all philos are full
static void	take_forks_eat_think_sleep(t_table *table, t_philo *philo)
{
	int	first_taken_fork_id;

	first_taken_fork_id = take_forks(table, philo);
	print_msg(table, philo->id, "is eating");
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_time();
	precise_usleep(table->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	put_forks_down(philo, first_taken_fork_id);
	is_philo_full(table, philo); // maybe if he is full i need to end here
	print_msg(table, philo->id, "is sleeping");
	precise_usleep(table->time_to_sleep); // use precise_usleep()
	print_msg(table, philo->id, "is thinking");
}

static void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	// For now, let's just print the philosopher ID to test
	printf("Philosopher %d is starting dinner\n", philo->id);
	// while 1
		// if death_flag or all_philos_full_flag (from watchdog)
		// take_forks_eat_think_sleep()
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	assign_forks(table);
	i = 0;
	// create pthread watchdog
	while (i < table->no_philosophers)
	{
		pthread_create(&table->philos[i]->thread_id, NULL, &dinner_routine, table->philos[i]);
		i++;
	}
	i = 0;
	while (i < table->no_philosophers)
	{
		pthread_join(table->philos[i]->thread_id, NULL);
		i++;
	}
}