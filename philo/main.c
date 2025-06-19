#include "philo.h"

int main(int argc, char *argv[])
{
	t_table	*table;
	t_philo	*philos;

	if (init_table(argc, argv, &table))
		return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
