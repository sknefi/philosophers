/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:27 by fkarika           #+#    #+#             */
/*   Updated: 2025/06/27 21:28:44 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_full(t_table *table, t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->philo_mutex);
	if (table->num_times_each_philosopher_must_eat != -1
		&& philo->meals_eaten >= table->num_times_each_philosopher_must_eat)
	{
		philo->is_full = 1;
		res = 1;
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (res);
}

/**
 * @brief Check if all the philosophers are full
 * @param table table of the simulation
 * @return 1 if all the philosophers are full, 0 if at least one is not full
 */
static int	are_all_philos_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		if (!is_philo_full(table, table->philos[i]))
			return (0);
		i++;
	}
	pthread_mutex_lock(&table->all_philos_full_mutex);
	table->all_philos_full_flag = 1;
	pthread_mutex_unlock(&table->all_philos_full_mutex);
	return (1);
}

/**
 * @brief Check if the philo is alive
 * @param table table of the simulation
 * @param philo philo to check
 * @return 1 if the philo is alive, 0 if the philo is dead
 */
static int	is_philo_alive(t_table *table, t_philo *philo)
{
	long	time_since_last_meal;
	long	time_since_start;
	long	meals_eaten;

	pthread_mutex_lock(&philo->philo_mutex);
	meals_eaten = philo->meals_eaten;
	if (meals_eaten == 0)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		time_since_start = get_time() - table->start_time;
		if (time_since_start < table->time_to_die)
			return (1);
	}
	else
	{
		time_since_last_meal = get_time() - philo->last_meal_time;
		pthread_mutex_unlock(&philo->philo_mutex);
		if (time_since_last_meal < table->time_to_die)
			return (1);
	}
	return (0);
}

/**
 * @brief Check if all the philosophers are alive
 * @param table table of the simulation
 * @return 1 if all the philosophers are alive, 0 if at least one is dead
 */
static int	are_all_philos_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->no_philosophers)
	{
		if (!is_philo_alive(table, table->philos[i]))
		{
			pthread_mutex_lock(&table->death_mutex);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->death_mutex);
			print_msg(table, table->philos[i]->id, MSG_DIED);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*watchdog_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (are_all_philos_alive(table) && !are_all_philos_full(table))
		precise_usleep(1000);
	return (NULL);
}
