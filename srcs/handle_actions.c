#include "philo.h"

int p_eat(t_info *info, int i)
{
    // printf("id - %d\n", info->philo[i].id);
    // printf("i - %d\n", i);
    if (info->nr_philo == 1)
    {
        philo_odd(info, i);
        return (1);
    }
    //printf("id - %d\n", info->philo[i].id);
    if (!lock_left_fork(info, i))
        return (0);
    pthread_mutex_lock(&info->m_print_lock);
    if (!lock_right_fork(info, i))
        return (0);
    pthread_mutex_unlock(&info->m_print_lock);
    // if (check_odd(info->philo[i].id) == 1)
    // {
    //     if (!philo_odd(info, i))
    //         return (0);
    // }
    // else
    // {
    //     if (!philo_even(info, i))
    //         return (0);
    // }
    if (info->philo[i].fork == 2)
    {
        // pthread_mutex_lock(&info->m_dead_philo);
        // pthread_mutex_unlock(&info->m_dead_philo);
        if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
            return (0);
        printf("%s%lld ms - Philosopher %d is eating\n", GREEN, get_time(info->start_time), info->philo[i].id);
        info->philo[i].last_eat = get_time(info->start_time);
        info->philo[i].eat_counter += 1;
        //printf("eat_counter - %d\n", info->philo[i].eat_counter);
        usleep(info->time_eat * 1000);
        //printf("eat-counter - %d\n", info->philo[i].eat_counter);
        pthread_mutex_unlock(&info->m_fork[info->philo[i].right]);
        pthread_mutex_unlock(&info->m_fork[info->philo[i].left]);
        if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
            return (0);
    }
    // pthread_mutex_unlock(&info->m_fork[info->philo[i].right]);
    // pthread_mutex_unlock(&info->m_fork[info->philo[i].left]);
    return (1);
}

int p_sleep(t_info *info, int i)
{
    if (info->philo[i].fork == 2)
    {
        // pthread_mutex_lock(&info->m_check_eat);
        // pthread_mutex_unlock(&info->m_check_eat);
        // pthread_mutex_lock(&info->m_dead_philo);
        // pthread_mutex_unlock(&info->m_dead_philo);
        // if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        //     return (0);
        printf("%s%lld ms - Philosopher %d is sleeping\n", BLUE, get_time(info->start_time), info->philo[i].id);
        usleep(info->time_sleep * 1000);
    }
    return (1);
}

int p_think(t_info *info, int i)
{
    if (info->philo[i].fork == 2)
    {
        // pthread_mutex_lock(&info->m_check_eat);
        // pthread_mutex_unlock(&info->m_check_eat);
        // pthread_mutex_lock(&info->m_dead_philo);
        // pthread_mutex_unlock(&info->m_dead_philo);
        // if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        //     return (0);
        printf("%s%lld ms - Philosopher %d is thinking\n", YELLOW, get_time(info->start_time), info->philo[i].id);
    }
    return (1);
}