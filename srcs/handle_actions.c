#include "philo.h"

int p_eat(t_info *info, int i)
{
    usleep(500);
    if (info->nr_philo == 1)
    {
        philo_odd(info, i);
        return (1);
    }
    if (check_odd(info->philo[i].id) == 1)
    {
        if (!philo_odd(info, i))
            return (0);
    }
    else
    {
        if (!philo_even(info, i))
            return (0);
    }
    if (info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    if (info->philo[i].fork == 2)
    {   
        printf("%s%lld ms - Philosopher %d is eating\n", GREEN, get_time(info->start_time), info->philo[i].id);
        info->philo[i].last_eat = get_time(info->start_time);
        usleep(info->time_eat * 1000);
        if (info->nr_must_eat > 0)
            info->philo[i].eat_counter++;
        pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_right]);
        pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_left]);
    }
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_right]);
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_left]);
    return (1);
}

void    p_sleep(t_info *info, int i)
{
    if (info->philo[i].fork == 2)
    {
        printf("%s%lld ms - Philosopher %d is sleeping\n", BLUE, get_time(info->start_time), info->philo[i].id);
        usleep(info->time_sleep * 1000);
    }
}

void    p_think(t_info *info, int i)
{
    if (info->philo[i].fork == 2)
        printf("%s%lld ms - Philosopher %d is thinking\n", YELLOW, get_time(info->start_time), info->philo[i].id);
}