#include "philo.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
			c == '\v' || c == '\f' || c == '\r');
}

long	ft_atol(const char *str)
{
	int			sign;
	long int	nb;

	nb = 0;
	sign = 1;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (0 <= (int)*str && (int)*str <= 9)
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (sign * nb);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}