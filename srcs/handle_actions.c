#include "philo.h"

int p_eat(t_info *info, int i)
{
    if (pthread_mutex_lock(&info->m_fork[info->philo[i].fork_right]) != 0)
        return (0);
    printf("%sPhilosopher %d has taken the right fork\n", CYAN, info->philo[i].id);
    if (pthread_mutex_lock(&info->m_fork[info->philo[i].fork_left]) != 0)
        return (0);
    printf("%sPhilosopher %d has taken the left fork\n", CYAN, info->philo[i].id);
    printf("%sPhilosopher %d is eating\n", GREEN, info->philo[i].id);
    usleep(info->time_eat * 1000);
    if (info->nr_must_eat > 0)
        info->philo[i].eat_counter++;
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_right]);
    pthread_mutex_unlock(&info->m_fork[info->philo[i].fork_left]);
    return (1);
}

void    p_sleep(t_info *info, int i)
{
    printf("%sPhilosopher %d is sleeping\n", BLUE, info->philo[i].id);
    usleep(info->time_sleep * 1000);
}

void    p_think(t_info *info, int i)
{
    printf("%sPhilosopher %d is thinking\n", YELLOW, info->philo[i].id);
}