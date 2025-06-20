#include "philo.h"

void	clean_philos(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->no_philosophers)
		free(table->philos[i++]);
	if (table->philos)
		free(table->philos);
}

void	clean_forks(t_table *table)
{
	int		i;

	if (!table->forks)
		return ;
	i = 0;
	while (i < table->no_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]->mutex);
		free(table->forks[i++]);
	}
	free(table->forks);
}

void	clean_table(t_table *table)
{
	if (!table)
		return ;
	clean_philos(table);
	clean_forks(table);
	free(table);
}