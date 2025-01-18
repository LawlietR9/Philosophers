#include "../inc/philosophers.h"

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (1);
        s1++;
        s2++;
    }
    if (*s1 != *s2)
        return (1);
    return (0);
}

int ft_atoi(char *str)
{
	int				sign;
	unsigned long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if (result > LONG_MAX / 10)
			return ((-1 - sign) / 2);
		result = result * 10 + *str - '0';
		if (sign == 1 && result >= (unsigned long)LONG_MAX)
			return (-1);
		if (sign == -1 && result >= (unsigned long)LONG_MAX + 1)
			return (0);
		str++;
	}
	return (sign * result);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_error("gettimeofday() error\n", NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t ms)
{
	size_t	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}

int print_message(t_philo *philo, char *message)
{
    if (is_dead(philo) && ft_strcmp(message, "died"))
        return (1);
    pthread_mutex_lock(&philo->data->write);
    printf("%llu %d %s\n", get_time() - philo->data->time_start, philo->id, message);
    pthread_mutex_unlock(&philo->data->write);
    return (0);
}
