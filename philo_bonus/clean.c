#include "philo.h"

static void	clean_sems(t_table *table)
{
	if (table->sems)
	{
		if (table->sems->forks_sem)
		{
			sem_close(table->sems->forks_sem);
			sem_unlink(SEM_FORKS);
		}
		if (table->sems->print_sem)
		{
			sem_close(table->sems->print_sem);
			sem_unlink(SEM_PRINT);
		}
	}
}

void	clean_table(t_table *table)
{
	clean_sems(table);
	free(table->sems);
	free(table->philos);
	free(table);
}
