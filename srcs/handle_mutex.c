#include "philo.h"

int create_mutex(t_info *info)
{
    int i;

    info->m_fork = malloc(sizeof(pthread_mutex_t) * info->nr_philo);
    i = 1;
    while (i <= info->nr_philo)
    {
        if (pthread_mutex_init(&info->m_fork[i-1], NULL))
            return (0);
        i++;
    }
    return (1);
}

int lock_right_fork(t_info *info, int i)
{
    if (info->dead_flag != 0 || !check_philo_dead(info, i))
        return (0);
    pthread_mutex_lock(&info->m_fork[info->philo[i].fork_right]);
    if (info->dead_flag != 0 || !check_philo_dead(info, i))
        return (0);
    printf("%s%lld ms - Philosopher %d has taken the right fork\n", CYAN, get_time(info->start_time), info->philo[i].id);
    return (1);
}

int lock_left_fork(t_info *info, int i)
{
    if (info->dead_flag != 0 || !check_philo_dead(info, i))
        return (0);
    pthread_mutex_lock(&info->m_fork[info->philo[i].fork_left]);
    if (info->dead_flag != 0 || !check_philo_dead(info, i))
        return (0);
    printf("%s%lld ms - Philosopher %d has taken the left fork\n", CYAN, get_time(info->start_time), info->philo[i].id);
    return (1);
}