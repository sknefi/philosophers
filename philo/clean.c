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

	i = 0;
	while (i < table->no_philosophers)
		free(table->forks[i++]);
	if (table->forks)
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