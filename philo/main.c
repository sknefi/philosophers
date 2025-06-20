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

int main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (printf(R "Error: Invalid number of arguments\n" RES), EXIT_FAILURE);
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	
	clean_table(table);
    return (EXIT_SUCCESS);
}
