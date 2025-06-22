#include "philo.h"

static void	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		table->philos[i]->left_fork = table->forks[i];
		table->philos[i]->right_fork = table->forks[(i + 1) % table->no_philosophers];
		i++;
	}
}

static void	is_philo_full(t_table *table, t_philo *philo)
{
	if (table->num_times_each_philosopher_must_eat != -1
		&& philo->meals_eaten >= table->num_times_each_philosopher_must_eat)
	{
		philo->is_full = 1;
	}
}

// take forks and eat

// check if philo died
// implement watchdog - somebody died, all philos are full
static void	take_forks_eat_think_sleep(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_msg(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_msg(table, philo->id, "has taken a fork");
	print_msg(table, philo->id, "is eating");
	philo->last_meal_time = get_time();
	usleep(table->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	is_philo_full(table, philo);
	print_msg(table, philo->id, "is sleeping");
	usleep(table->time_to_sleep); // use precise_usleep()
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