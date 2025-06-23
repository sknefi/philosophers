#include "philo.h"

void	print_msg(t_table *table, int philo_id, char *msg)
{
	int		death_flag;
	long	timestamp;
	long	current_time;

	pthread_mutex_lock(&table->print_mutex);
	pthread_mutex_lock(&table->death_mutex);
	death_flag = table->death_flag;
	pthread_mutex_unlock(&table->death_mutex);
	if (death_flag && strcmp(msg, MSG_DIED) != 0)
	{
		pthread_mutex_unlock(&table->print_mutex);
		return ;
	}
	current_time = get_time();
	timestamp = (current_time - table->start_time) / 1000;
	printf("%ld %d %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}

void	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		table->philos[i]->left_fork = table->forks[i];
		table->philos[i]->right_fork = table->forks[(i + 1)
			% table->no_philosophers];
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

void	solo_dinner(t_table *table)
{
	t_philo	*philo;

	philo = table->philos[0];
	printf("0 %d %s\n", philo->id, MSG_FORK);
	printf("%ld %d %s\n", table->time_to_die / 1000, philo->id, MSG_DIED);
}
