#include "philo.h"

static int	assign_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		table->philos[i]->left_fork = table->forks[i];
		table->philos[i]->right_fork = table->forks[(i + 1) % table->no_philosophers];
		i++;
	}
	return (0);
}

void	start_dinner(t_table *table)
{
	assign_forks(table);

}