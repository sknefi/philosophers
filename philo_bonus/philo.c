#include "philo.h"

static void	dinner_routine(t_table *table, t_philo *philo)
{
	while (!is_philo_full(table, philo))
	{
		take_forks(table, philo);
		philo->last_meal_time = get_time();
		print_msg(table, philo->id, MSG_EAT);
		precise_usleep(table->time_to_eat);
		philo->meals_eaten++;
		put_forks_down(table);
		
		if (is_philo_full(table, philo))
			break;
			
		print_msg(table, philo->id, MSG_SLEEP);
		precise_usleep(table->time_to_sleep);
		print_msg(table, philo->id, MSG_THINK);
		if (table->no_philosophers % 2 == 0)
		{
			if (table->time_to_die > (table->time_to_eat + table->time_to_sleep))
			{
				precise_usleep((table->time_to_die - table->time_to_eat 
					- table->time_to_sleep) / 2);
			}
		}
	}
	exit(0);
}

int	start_dinner(t_table *table)
{
	int		i;
	int		status;
	pid_t	watchdog_pid;

	if (table->no_philosophers == 1)
	{
		solo_dinner(table);
		return (0);
	}
	
	// Start watchdog process
	watchdog_pid = fork();
	if (watchdog_pid == -1)
		return (1);
	if (watchdog_pid == 0)
		watchdog_routine(table);
	
	// Start philosopher processes
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
	
	// Wait for any process to finish (either philosopher or watchdog)
	waitpid(-1, &status, 0);
	
	// Kill all remaining processes
	kill_all_philo_processes(table);
	kill(watchdog_pid, SIGKILL);
	
	// Wait for all child processes to avoid zombies
	while (waitpid(-1, &status, WNOHANG) > 0)
		;
	
	return (0);
}
