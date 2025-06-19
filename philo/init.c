#include "philo.h"

int	init_table(int argc, char **argv, t_table *table)
{
	if (argc != 6 && argc != 7)
		return (1);
	table->no_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_times_each_philosopher_must_eat = ft_atol(argv[5]);
	else
		table->num_times_each_philosopher_must_eat = -1;
	return (0);
}

t_philo	*init_philos(t_table *table)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * table->no_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->no_philosophers)
		philos[i++].id = i;
	return (philos);
}
