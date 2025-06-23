#include "philo.h"

/**
 * the last parameter of input was not set -> 0
 * the last parameter of input was set and philo is not full -> 0
 * the last parameter of input was set and philo is full -> 1
*/
int	is_philo_full(t_table *table, t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->philo_mutex);
	if (table->num_times_each_philosopher_must_eat != -1
		&& philo->meals_eaten >= table->num_times_each_philosopher_must_eat)
	{
		philo->is_full = 1;
		res = 1;
	}
	pthread_mutex_unlock(&philo->philo_mutex);	
	return (res);
}

static int	are_all_philos_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		if (!is_philo_full(table, table->philos[i]))
			return (0);
		i++;
	}
	pthread_mutex_lock(&table->all_philos_full_mutex);
	table->all_philos_full_flag = 1; 
	pthread_mutex_unlock(&table->all_philos_full_mutex);
	return (1);
}

static int	is_philo_alive(t_table *table, t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->philo_mutex);
	if ((get_time() - philo->last_meal_time) < table->time_to_die)
		res = 1;
	pthread_mutex_unlock(&philo->philo_mutex);	
	return (res);	
}

static int	are_all_philos_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		if (!is_philo_alive(table, table->philos[i]))
		{
			pthread_mutex_lock(&table->death_mutex);
			table->death_flag = 1; 
			pthread_mutex_unlock(&table->death_mutex);
			print_msg(table, table->philos[i]->id, MSG_DIED);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*watchdog_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (are_all_philos_alive(table) && !are_all_philos_full(table))
		precise_usleep(100);
	return (NULL);
}