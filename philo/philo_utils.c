#include "philo.h"

void	print_msg(t_table *table, int philo_id, char *msg)
{
	long	timestamp;
	long	current_time;

	pthread_mutex_lock(&table->print_mutex);
	current_time = get_time();
	timestamp = (current_time - table->start_time) / 1000;
	printf("%ld %d %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&table->print_mutex);
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

void	assign_forks(t_table *table)
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

void	put_forks_down(t_philo *philo, int first_fork_id)
{
	if (first_fork_id == philo->left_fork->id)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);	
		pthread_mutex_unlock(&philo->left_fork->mutex);
	}
}