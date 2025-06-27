/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:24 by fkarika           #+#    #+#             */
/*   Updated: 2025/06/27 20:00:25 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_table *table, int philo_id, char *msg)
{
	long	timestamp;

	sem_wait(table->sems->print_sem);
	timestamp = (get_time() - table->start_time) / 1000;
	printf("%ld %d %s\n", timestamp, philo_id, msg);
	if (ft_strcmp(msg, MSG_DIED) != 0)
		sem_post(table->sems->print_sem);
}

void	put_forks_down(t_table *table)
{
	sem_post(table->sems->forks_sem);
	sem_post(table->sems->forks_sem);
}

void	take_forks(t_table *table, t_philo *philo)
{
	sem_wait(table->sems->forks_sem);
	print_msg(table, philo->id, MSG_FORK);
	sem_wait(table->sems->forks_sem);
	print_msg(table, philo->id, MSG_FORK);
}

void	think(t_table *table)
{
	long	thinking_time;

	if (table->time_to_eat < table->time_to_die - table->time_to_sleep)
	{
		thinking_time = (table->time_to_die - table->time_to_eat
				- table->time_to_sleep) / 2;
		if (thinking_time > 30000)
			thinking_time = 30000;
		if (thinking_time > 0)
			precise_usleep(thinking_time);
	}
}

void	solo_dinner(t_table *table)
{
	t_philo	*philo;

	philo = &table->philos[0];
	printf("0 %d %s\n", philo->id, MSG_FORK);
	printf("%ld %d %s\n", table->time_to_die / 1000, philo->id, MSG_DIED);
}
