#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

void	print_msg(t_table *table, int philo_id, char *msg)
{
	long	timestamp;
	long	current_time;

	pthread_mutex_lock(&table->print_mutex);
	current_time = get_time();
	timestamp = (current_time - table->start_time) / 1000;
	printf("%ld %d %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}