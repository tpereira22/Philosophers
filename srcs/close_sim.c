#include "philo.h"

void    close_sim(t_info *info, int i)
{
    int c;

    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_right]);
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_left]);
    pthread_mutex_unlock(&info->m_check_eat);
    c = 0;
    while (c < info->nr_philo)
    {
        pthread_mutex_destroy(&info->m_fork[i]);
        c++;
    }
    pthread_mutex_destroy(&info->m_dead_philo);
    pthread_mutex_destroy(&info->m_check_eat);
    pthread_mutex_destroy(&info->m_print_lock);
    pthread_mutex_destroy(&info->m_print_lock2);
}

int check_eat_all(t_info *info)
{
    int i;
    int c;

    i = 0;
    c = 0;
    pthread_mutex_lock(&info->m_check_eat);
    //printf("th 1\n");
    while (i < info->nr_philo)
    {
        if (info->philo[i].eat_counter >= info->nr_must_eat)
            c++;
        i++;
    }
    if (c == info->nr_philo)
    {
        info->eat_flag = 1;
        return (0);
    }
    pthread_mutex_unlock(&info->m_check_eat);
    return (1);
}