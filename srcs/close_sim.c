#include "philo.h"

int close_sim(t_info *info, int i)
{
    if (info->philo[i].id <= info->nr_philo)
    {
        //printf("id - %d\n", info->philo[i].id);
        if (info->forks[info->philo[i].right] == 1)
        {
            info->forks[info->philo[i].right] = 0;
            pthread_mutex_unlock(&info->m_fork[info->philo[i].right]);
        }
        if (info->forks[info->philo[i].left] == 1)
        {   
            info->forks[info->philo[i].left] = 0;
            pthread_mutex_unlock(&info->m_fork[info->philo[i].left]);
        }
    }
    return (1);
}

void    free_all(t_info *info)
{
    int i;

    i = 0;
    while (i < info->nr_philo)
    {
        pthread_mutex_destroy(&info->m_fork[i]);
        i++;
    }
    pthread_mutex_destroy(&info->m_check_eat);
    pthread_mutex_destroy(&info->m_dead_philo);
    pthread_mutex_destroy(&info->m_print_lock);
    free(info->m_fork);
    free(info->philo);
    free(info->forks);
}

int check_eat_all(t_info *info)
{
    int i;
    int c;

    i = 0;
    c = 0;
    pthread_mutex_lock(&info->m_check_eat);
    while (i < info->nr_philo)
    {
        if (info->philo[i].eat_counter >= info->nr_must_eat)
            c++;
        i++;
    }
    if (c == info->nr_philo)
    {
        info->eat_flag = 1;
        pthread_mutex_unlock(&info->m_check_eat);
        return (0);
    }
    pthread_mutex_unlock(&info->m_check_eat);
    return (1);
}