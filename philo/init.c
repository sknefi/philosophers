#include "philo.h"

/**
 * @brief Initialize the arguments of the table from input
 * @param argc number of arguments
 * @param argv arguments
 * @param table table to initialize
 * @return 0 if all params are valid, 1 if there is some negative value
 */
static int	init_args(int argc, char **argv, t_table *table)
{
	table->no_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argc == 6)
	{
		table->num_times_each_philosopher_must_eat = ft_atol(argv[5]);
		if (table->num_times_each_philosopher_must_eat <= 0)
			return (1);
	}
	else
		table->num_times_each_philosopher_must_eat = -1;
	return (table->no_philosophers <= 0
		|| table->time_to_die <= 0
		|| table->time_to_eat <= 0
		|| table->time_to_sleep <= 0);
}

/**
 * @brief Initialize the philosophers of the table
 * @param table table to initialize
 * @return 0 if OK, 1 if malloc/mutex error
 */
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
		table->philos[i]->last_meal_time = get_time();
		if (pthread_mutex_init(&table->philos[i]->philo_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Initialize the forks of the table
 * @param table table to initialize
 * @return 0 if OK, 1 if malloc/mutex error
 */
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

int	init_table(int argc, char **argv, t_table *table)
{
	table->death_flag = 0;
	table->start_time = get_time();
	table->all_philos_full_flag = 0;
	if (init_args(argc, argv, table))
		return (printf(ERR_IN), 1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->all_philos_full_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (1);
	if (init_philos(table))
		return (1);
	if (init_forks(table))
		return (1);
	return (0);
}

t_dinner_args	*init_dinner_args(t_table *table)
{
	int				i;
	t_dinner_args	*dinner_args;

	dinner_args = (t_dinner_args *)malloc(sizeof(t_dinner_args) * table->no_philosophers);
	if (!dinner_args)
		return (NULL);
	i = 0;
	while (i < table->no_philosophers)
	{
		dinner_args[i].table = table;
		dinner_args[i].philo = table->philos[i];
		i++;
	}
	return (dinner_args);
}