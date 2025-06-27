#include "philo.h"

/**
 * @brief Check if the philo is alive
 * @param table table of the simulation
 * @param philo philo to check
 * @return 1 if the philo is alive, 0 if the philo is dead
 */
static int	is_philo_alive(t_table *table, t_philo *philo)
{
	int		res;
	long	time_since_last_meal;
	long	time_since_start;

	res = 0;
	if (philo->meals_eaten == 0)
	{
		time_since_start = get_time() - table->start_time;
		if (time_since_start < table->time_to_die)
			res = 1;
	}
	else
	{
		time_since_last_meal = get_time() - philo->last_meal_time;
		if (time_since_last_meal < table->time_to_die)
			res = 1;
	}
	return (res);
}

/**
 * @brief Check if all the philosophers are full
 * @param table table of the simulation
 * @return 1 if all the philosophers are full, 0 if at least one is not full
 */
static int	are_all_philos_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		if (!is_philo_full(table, &table->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_philo_full(t_table *table, t_philo *philo)
{
	if (table->num_times_each_philosopher_must_eat != -1
		&& philo->meals_eaten >= table->num_times_each_philosopher_must_eat)
	{
		philo->is_full = 1;
		return (1);
	}
	return (0);
}

void	kill_all_philo_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		if (table->philos[i].pid > 0)
			kill(table->philos[i].pid, SIGKILL);
		i++;
	}
}

void	watchdog_routine(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->no_philosophers)
		{
			if (!is_philo_alive(table, &table->philos[i]))
			{
				print_msg(table, table->philos[i].id, MSG_DIED);
				kill_all_philo_processes(table);
				exit(1);
			}
			i++;
		}
		if (are_all_philos_full(table))
		{
			kill_all_philo_processes(table);
			exit(0);
		}
		precise_usleep(10);
	}
}
