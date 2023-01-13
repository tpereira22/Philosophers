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
    if (pthread_mutex_init(&info->m_check_eat, NULL))
        return (0);
    if (pthread_mutex_init(&info->m_print_lock, NULL))
        return (0);
    return (1);
}

int lock_left_fork(t_info *info, int i)
{
    if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    if (pthread_mutex_lock(&info->m_fork[info->philo[i].left]) != 0)
         return (0);
    info->forks[info->philo[i].left] = 1;
    usleep(300);
    if (!print_philo(info, i, CYAN, FORK))
        return (0);
    return (1);
}

int lock_right_fork(t_info *info, int i)
{

    if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    if (pthread_mutex_lock(&info->m_fork[info->philo[i].right]) != 0)
        return (0);
    info->forks[info->philo[i].right] = 1;
    usleep(300);
    if (!print_philo(info, i, CYAN, FORK))
        return (0);
    return (1);
}

// void    destroy_mutex(t_info *info)
// {
//     int i;

//     i = 1;
//     while (i < info->nr_philo)
//     {
//         pthread_mutex_destroy(&info->m_fork[i-1]);
//         i++;
//     }
//     pthread_mutex_destroy(&info->m_dead_philo);
//     pthread_mutex_destroy(&info->m_check_eat);
//     pthread_mutex_destroy(&info->m_print_lock);
// }