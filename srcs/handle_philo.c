#include "philo.h"

int philo_even(t_info *info, int i)
{
    if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    if (!lock_left_fork(info, i))
        return (0);
    if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    if (!lock_right_fork(info, i))
        return (0);
    return (1);
}

int philo_odd(t_info *info, int i)
{
    if (info->nr_philo == 1)
    {
        if (info->dead_flag != 0 || !check_philo_dead(info, i))
            return (0);
        if (!lock_left_fork(info, i))
            return (0);
        pthread_mutex_unlock(&info->m_fork[info->philo[i].left]);
        return (0);
    }
    else
    {
        if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
            return (0);
        if (!lock_right_fork(info, i))
            return (0);
        if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
            return (0);
        if (!lock_left_fork(info, i))
            return (0);
        return (1);
    }
}
int init_philo(t_info *info, int i, int j)
{
    info->philo[i].id = j;
    info->philo[i].time_die = info->time_die;
    info->philo[i].eat_counter = 0;
    info->philo[i].last_eat = 0;
    info->philo[i].philo_dead = 0;
    if (i != info->nr_philo)
    info->philo[i].left = i;
    if (j == info->nr_philo)
        j = 0;
    info->philo[i].right = j;
    return (1);
}

t_info *create_philo(t_info *info)
{
    int i;
    int j;

    info->philo = malloc(sizeof(t_philo) * (info->nr_philo + 1));
    if (info->philo == NULL)
        return (NULL);
    i = 0;
    j = 1;
    while (i <= info->nr_philo)
    {
        if (!init_philo(info, i, j))
            return (NULL);
        i++;
        j++;
    }
    if (!create_mutex(info))
    {
        printf("mutex error\n");
        return (NULL);
    }
    return (info);
}