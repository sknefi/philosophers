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

static t_sems	*init_sems(t_table *table)
{
	t_sems	*sems;

	sems = (t_sems *)malloc(sizeof(t_sems));
	if (!sems)
		return (NULL);
	sems->forks = sem_open(SEM_FORKS, O_CREAT, 0644, table->no_philosophers);
	sems->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	sems->death_sem = sem_open(SEM_DEATH, O_CREAT, 0644, 1);
	sems->all_philos_full_sem = sem_open(SEM_ALL_PHILOS_FULL, O_CREAT, 0644, 1);
	if (sems->forks == SEM_FAILED || sems->print_sem == SEM_FAILED
		|| sems->death_sem == SEM_FAILED
		|| sems->all_philos_full_sem == SEM_FAILED)
	{
		free(sems);
		return (NULL);
	}
	return (sems);
}

int	init_table(int argc, char **argv, t_table *table)
{
	table->death_flag = 0;
	table->start_time = get_time();
	table->all_philos_full_flag = 0;
	if (init_args(argc, argv, table))
		return (printf(ERR_IN), 1);

	if (init_philos(table))
		return (1);
	if (init_forks(table))
		return (1);
	return (0);
}
