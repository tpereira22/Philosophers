#include "philo.h"

int p_eat(t_info *info, int i)
{
    if (check_odd(info->philo[i].id) == 1)
        lock_right_fork(info, i);
    else
        lock_left_fork(info, i);
    if (check_odd(info->philo[i].id) == 2)
        lock_right_fork(info, i);
    else
        lock_left_fork(info, i);
    if (check_philo_dead(info, i))
    {
        printf("%s%lld ms - Philosopher %d is eating\n", GREEN, get_time(info->start_time), info->philo[i].id);
        usleep(info->time_eat * 1000);
        info->philo[i].last_eat = get_time(info->start_time);
        if (info->nr_must_eat > 0)
            info->philo[i].eat_counter++;
    }
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_right]);
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_left]);
    return (1);
}

void    p_sleep(t_info *info, int i)
{
    printf("%s%lld ms - Philosopher %d is sleeping\n", BLUE, get_time(info->start_time), info->philo[i].id);
    usleep(info->time_sleep * 1000);
}

void    p_think(t_info *info, int i)
{
    printf("%s%lld ms - Philosopher %d is thinking\n", YELLOW, get_time(info->start_time), info->philo[i].id);
}