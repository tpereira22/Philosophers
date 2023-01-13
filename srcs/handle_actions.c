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
    if (!lock_left_fork(info, i))
        return (0);
    if (!lock_right_fork(info, i))
        return (0);
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
    if (!print_philo(info, i, GREEN, EAT))
        return (0);
    info->philo[i].last_eat = get_time(info->start_time);
    info->philo[i].eat_counter += 1;
    //printf("eat - %d\n", info->philo[i].eat_counter);
    usleep(info->time_eat * 1000);
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
    if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    // pthread_mutex_unlock(&info->m_fork[info->philo[i].right]);
    // pthread_mutex_unlock(&info->m_fork[info->philo[i].left]);
    return (1);
}

int p_sleep(t_info *info, int i)
{

    if (!print_philo(info, i, BLUE, SLEEP))
        return (0);
    usleep(info->time_sleep * 1000);
    return (1);
}

int p_think(t_info *info, int i)
{
    if (!print_philo(info, i, YELLOW, THINK))
        return (0);
    return (1);
}