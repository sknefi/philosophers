#include "philo.h"

int main(int argc, char *argv[])
{
	t_table	*table;

	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);

	clean_table(table);
    return (EXIT_SUCCESS);
}
