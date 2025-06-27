#include "philo.h"

static void	*philo_monitor(void *arg)
{
	t_table					*table;
	t_philo					*philo;
	t_philo_monitor_args	*philo_monitor_args;

	philo_monitor_args = (t_philo_monitor_args *)arg;
	table = philo_monitor_args->table;
	philo = philo_monitor_args->philo;
	free(philo_monitor_args);
	while (1)
	{
		if (philo->meals_eaten == 0)
		{
			if ((get_time() - table->start_time) >= table->time_to_die)
				(print_msg(table, philo->id, MSG_DIED), exit(1));
		}
		else
		{
			if (get_time() - philo->last_meal_time >= table->time_to_die)
				(print_msg(table, philo->id, MSG_DIED), exit(1));
		}
		precise_usleep(1000);
	}
	return (NULL);
}

static void	dinner_routine(t_table *table, t_philo *philo)
{
	pthread_t				watchdog_thread;
	t_philo_monitor_args	*philo_monitor_args;

	philo_monitor_args = malloc(sizeof(t_philo_monitor_args));
	if (!philo_monitor_args)
		exit(1);
	philo_monitor_args->table = table;
	philo_monitor_args->philo = philo;
	if (pthread_create(&watchdog_thread, NULL, &philo_monitor,
			philo_monitor_args) != 0)
		exit(1);
	pthread_detach(watchdog_thread);
	while (!is_philo_full(table, philo))
	{
		take_forks(table, philo);
		philo->last_meal_time = get_time();
		print_msg(table, philo->id, MSG_EAT);
		precise_usleep(table->time_to_eat);
		philo->meals_eaten++;
		put_forks_down(table);
		if (is_philo_full(table, philo))
			break ;
		print_msg(table, philo->id, MSG_SLEEP);
		precise_usleep(table->time_to_sleep);
		print_msg(table, philo->id, MSG_THINK);
		think(table);
	}
	exit(0);
}

int	start_dinner(t_table *table)
{
	int		i;
	int		status;

	if (table->no_philosophers == 1)
		return (solo_dinner(table), 0);
	i = 0;
	while (i < table->no_philosophers)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			return (1);
		if (table->philos[i].pid == 0)
			dinner_routine(table, &table->philos[i]);
		i++;
	}
	waitpid(-1, &status, 0);
	kill_all_philo_processes(table);
	return (0);
}
