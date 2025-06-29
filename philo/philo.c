/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:40 by fkarika           #+#    #+#             */
/*   Updated: 2025/06/29 11:36:04 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Philo takes 2 forks, one to each hand
 * @return the id of the first fork taken 
 * (so when putting them down he puts the first one down the first picked up)
 */
static int	take_forks(t_table *table, t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&first_fork->mutex);
	print_msg(table, philo->id, MSG_FORK);
	pthread_mutex_lock(&second_fork->mutex);
	print_msg(table, philo->id, MSG_FORK);
	return (first_fork->id);
}

/**
 * @brief Philo takes 2 forks, eats, sleeps, thinks
 * @param table table to use
 * @param philo current philo in iteration
 */
static void	take_forks_eat_think_sleep(t_table *table, t_philo *philo)
{
	int		first_taken_fork_id;

	first_taken_fork_id = take_forks(table, philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	print_msg(table, philo->id, MSG_EAT);
	precise_usleep(table->time_to_eat);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	put_forks_down(philo, first_taken_fork_id);
	if (is_philo_full(table, philo))
		return ;
	print_msg(table, philo->id, MSG_SLEEP);
	precise_usleep(table->time_to_sleep);
	print_msg(table, philo->id, MSG_THINK);
	think(table);
}

/**
 * @brief Check if the simulation is over (somebody died or all philos are full)
 * that means that one of the flags is set to 1
 * @param table table to use
 * @return 1 if the simulation is over, 0 if it should continue
 */
static int	is_simulation_over(t_table *table)
{
	int	death_flag;
	int	all_philos_full_flag;

	pthread_mutex_lock(&table->death_mutex);
	death_flag = table->death_flag;
	pthread_mutex_unlock(&table->death_mutex);
	pthread_mutex_lock(&table->all_philos_full_mutex);
	all_philos_full_flag = table->all_philos_full_flag;
	pthread_mutex_unlock(&table->all_philos_full_mutex);
	return (death_flag || all_philos_full_flag);
}

/**
 * @brief Dinner routine for a philosopher used in thread as a thread function
 * @param arg pointer to the dinner arguments (struct with table and philo)
 * @return NULL, no need of return value
 */
static void	*dinner_routine(void *arg)
{
	t_table			*table;
	t_philo			*philo;
	t_dinner_args	*dinner_args;

	dinner_args = (t_dinner_args *)arg;
	table = dinner_args->table;
	philo = dinner_args->philo;
	if (philo->id % 2 == 0)
		precise_usleep(200);
	while (!is_simulation_over(table) && !is_philo_full(table, philo))
		take_forks_eat_think_sleep(table, philo);
	return (NULL);
}

int	start_dinner(t_table *table)
{
	int				i;
	t_dinner_args	*dinner_args;

	dinner_args = init_dinner_args(table);
	if (!dinner_args)
		return (1);
	assign_forks(table);
	if (table->no_philosophers == 1)
		return (solo_dinner(table), 0);
	pthread_create(&table->watchdog_thread, NULL, &watchdog_routine, table);
	i = 0;
	while (i < table->no_philosophers)
	{
		pthread_create(&table->philos[i]->thread, NULL, &dinner_routine,
			&dinner_args[i]);
		i++;
	}
	i = 0;
	while (i < table->no_philosophers)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(table->watchdog_thread, NULL);
	return (free_dinner_args(dinner_args), 0);
}
