/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:00:46 by fkarika           #+#    #+#             */
/*   Updated: 2025/06/27 20:00:47 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (printf(ERR_ARG), EXIT_FAILURE);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (EXIT_FAILURE);
	if (init_table(argc, argv, table))
		return (clean_table(table), EXIT_FAILURE);
	if (start_dinner(table))
		return (clean_table(table), EXIT_FAILURE);
	clean_table(table);
	return (EXIT_SUCCESS);
}
