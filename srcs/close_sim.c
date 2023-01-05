#include "philo.h"

void    close_sim(t_info *info, int i)
{
    int c;

    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_right]);
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_left]);
    c = 0;
    while (c < info->nr_philo)
    {
        pthread_mutex_destroy(&info->m_fork[i]);
        c++;
    }
}