#include "philo.h"

void	clean_table(t_table *table)
{
	sem_close(table->sems->forks);
	sem_close(table->sems->print_sem);
	sem_close(table->sems->death_sem);
	sem_close(table->sems->all_philos_full_sem);
	free(table->sems);
	free(table->philos);
	free(table);
}