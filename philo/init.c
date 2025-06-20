#include "philo.h"

static void	init_args(int argc, char **argv, t_table *table)
{
	table->no_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argc == 6)
		table->num_times_each_philosopher_must_eat = ft_atol(argv[5]);
	else
		table->num_times_each_philosopher_must_eat = -1;
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = (t_philo **)malloc(sizeof(t_philo *) * table->no_philosophers);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < table->no_philosophers)
	{
		table->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!table->philos[i])
			return (1);
		ft_memset(table->philos[i], 0, sizeof(t_philo));
		table->philos[i]->id = i + 1;
		i++;
	}
	return (0);
}

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = (t_fork **)malloc(sizeof(t_fork *) * table->no_philosophers);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->no_philosophers)
	{
		table->forks[i] = (t_fork *)malloc(sizeof(t_fork));
		if (!table->forks[i])
			return (1);
		table->forks[i]->id = i + 1;
		if (pthread_mutex_init(&table->forks[i]->mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	init_args(argc, argv, table);
	if (table->no_philosophers == 1)
		return (printf(R "Error: Invalid number of philosophers\n"), NULL);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (NULL);
	if (init_philos(table))
		return (clean_table(table), NULL);
	if (init_forks(table))
		return (clean_table(table), NULL);
	table->start_time = get_time();
	return (table);
}