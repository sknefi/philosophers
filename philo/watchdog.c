#include "philo.h"

int	are_all_philos_full(t_table *table)
{
	int	i;

	i = 0;	
	while (i < table->no_philosophers)
	{
		if (!table->philos[i]->is_full)
			return (0);
		i++;
	}
	return (1);
}

void	are_philos_alive(t_table *table)
{
	int	i;

	i = 0;
	while
}