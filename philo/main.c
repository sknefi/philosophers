#include "philo.h"

void print_table(t_table *table)
{
	printf("table->no_philosophers: %d\n", table->no_philosophers);
	printf("table->time_to_die: %ld\n", table->time_to_die);
	printf("table->time_to_eat: %ld\n", table->time_to_eat);
	printf("table->time_to_sleep: %ld\n", table->time_to_sleep);
	printf("table->num_times_each_philosopher_must_eat: %ld\n", table->num_times_each_philosopher_must_eat);
	printf("table->start_time: %ld\n", table->start_time);
}

void	print_philos(t_table *table)
{
	int	i;

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

int main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (printf(R "Error: Invalid number of arguments\n" RES), EXIT_FAILURE);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (printf(R "Error: Failed to allocate memory\n" RES), EXIT_FAILURE);
	if (init_table(argc, argv, table))
		return (EXIT_FAILURE);
	if (start_dinner(table))
		return (EXIT_FAILURE);
	clean_table(table);
    return (EXIT_SUCCESS);
}
