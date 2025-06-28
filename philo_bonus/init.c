/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:26 by fkarika           #+#    #+#             */
/*   Updated: 2025/06/27 22:03:35 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (check_for_only_nums(argc, argv))
		return (1);
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

static int	init_sems(t_table *table)
{
	t_sems	*sems;

	sems = (t_sems *)malloc(sizeof(t_sems));
	if (!sems)
		return (1);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sems->forks_sem = sem_open(SEM_FORKS, O_CREAT, 0644,
			table->no_philosophers);
	if (sems->forks_sem == SEM_FAILED)
		return (1);
	sems->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (sems->print_sem == SEM_FAILED)
		return (1);
	table->sems = sems;
	return (0);
}

static int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * table->no_philosophers);
	if (!philos)
		return (1);
	i = 0;
	while (i < table->no_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].is_full = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_time();
		philos[i].pid = -1;
		i++;
	}
	table->philos = philos;
	return (0);
}

int	init_table(int argc, char **argv, t_table *table)
{
	table->start_time = get_time();
	table->philos = NULL;
	table->sems = NULL;
	if (init_args(argc, argv, table))
		return (printf(ERR_IN), 1);
	if (init_philos(table))
		return (1);
	if (init_sems(table))
		return (1);
	return (0);
}
