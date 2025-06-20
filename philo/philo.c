#include "philo.h"

int	assign_forks(t_table *table)
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

void	print_philos(t_table *table)
{
	int	i;

	assign_forks(table);
	i = 0;
	while (i < table->no_philosophers)
	{
		printf("==============\n");
		printf("id: %d\n", table->philos[i]->id);
		printf("left_fork: %d\n", table->philos[i]->left_fork->id);
		printf("right_fork: %d\n", table->philos[i]->right_fork->id);
		printf("is_full: %d\n", table->philos[i]->is_full);
		printf("meals_eaten: %ld\n", table->philos[i]->meals_eaten);
		printf("last_meal_time: %ld\n", table->philos[i]->last_meal_time);
		i++;
	}
}
