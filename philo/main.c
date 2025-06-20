#include "philo.h"

void print_table(t_table *table)
{
	printf("table->no_philosophers: %d\n", table->no_philosophers);
	printf("table->time_to_die: %ld\n", table->time_to_die);
	printf("table->time_to_eat: %ld\n", table->time_to_eat);
	printf("table->time_to_sleep: %ld\n", table->time_to_sleep);
}

int main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 6 && argc != 7)
		return (printf(R "Error: Invalid number of arguments\n"), EXIT_FAILURE);
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	print_table(table);
	print_philos(table);
	clean_table(table);
    return (EXIT_SUCCESS);
}
