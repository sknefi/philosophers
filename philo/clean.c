/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:55 by fkarika           #+#    #+#             */
/*   Updated: 2025/06/27 20:00:56 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_dinner_args(t_dinner_args *dinner_args)
{
	if (!dinner_args)
		return ;
	free(dinner_args);
}

void	free_philos(t_table *table)
{
	int		i;

	if (!table->philos)
		return ;
	i = 0;
	while (i < table->no_philosophers)
	{
		pthread_mutex_destroy(&table->philos[i]->philo_mutex);
		free(table->philos[i]);
		i++;
	}
	free(table->philos);
}

void	free_forks(t_table *table)
{
	int		i;

	if (!table->forks)
		return ;
	i = 0;
	while (i < table->no_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]->mutex);
		free(table->forks[i++]);
	}
	free(table->forks);
}

void	clean_table(t_table *table)
{
	if (!table)
		return ;
	free_philos(table);
	free_forks(table);
	if (table->init_mutexes_success)
	{
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->all_philos_full_mutex);
		pthread_mutex_destroy(&table->death_mutex);
	}
	free(table);
}
