#include "philo.h"

// tv.sec - seconds | tv.usec - microseconds

long long	get_time(long long t0)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec * 0.001)) - t0);
}

int	check_odd(int i)
{
	if (i % 2 == 0)
		return (2);
	else
		return (1);
}

int	check_philo_dead(t_info *info, int i)
{
	if ((get_time(info->start_time) - info->philo[i].last_eat) < info->time_die)
	{
		// printf("now - %lld | last_eat - %lld | time_die - %d | wait ms - %lld\n", get_time(info->start_time), info->philo[i].last_eat, info->time_die, (get_time(info->start_time) - info->philo[i].last_eat));
		return (1);
	}
	else
    {
		// printf("now - %lld | last_eat - %lld | time_die - %d | wait ms - %lld\n", get_time(info->start_time), info->philo[i].last_eat, info->time_die, (get_time(info->start_time) - info->philo[i].last_eat));
        printf("%s%lld ms - Philosopher %d has died\n", RED, get_time(info->start_time), info->philo[i].id);
        exit (1);
    }
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - 48;
		i++;
	}
	return (num *= sign);
}
