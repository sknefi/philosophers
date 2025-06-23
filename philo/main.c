#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (printf(ERR_ARG), EXIT_FAILURE);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (EXIT_FAILURE);
	if (init_table(argc, argv, table))
		return (EXIT_FAILURE);
	if (start_dinner(table))
		return (EXIT_FAILURE);
	clean_table(table);
	return (EXIT_SUCCESS);
}
