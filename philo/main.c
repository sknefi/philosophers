#include "philo.h"

int	parser(t_table *table)
{
	return (
		table->no_philosophers <= 0
		|| table->time_to_die <= 0
		|| table->time_to_eat <= 0
		|| table->time_to_sleep <= 0
	);
}

int main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (printf(ERR_ARG), EXIT_FAILURE);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (EXIT_FAILURE);
	if (init_table(argc, argv, table))
		return (EXIT_FAILURE);
	if (parser(table))
		return (printf(ERR_IN), EXIT_FAILURE);
	if (start_dinner(table))
		return (EXIT_FAILURE);
	clean_table(table);
    return (EXIT_SUCCESS);
}
