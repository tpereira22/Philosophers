#include "philo.h"

int create_threads(t_info *info)
{
    int i;

    i = 0;
    info->start_time = get_time(0);
    while (i <= info->nr_philo)
    {
        info->thread_nr = i;
        info->philo[i].last_eat = get_time(info->start_time);
        if (pthread_create(&info->philo[i].philo_thread, NULL, &routine, (void*)info))
            return (0);
        i++;
        usleep(1000);
    }
    i = 0;
    while (i <= info->nr_philo)
    {
        if (pthread_join(info->philo[i].philo_thread, NULL))
            return (0);
        i++;
    }
    return (1);
}

void    *routine(void *args)
{
    t_info  *info;
    int i;

    info = (t_info *)args;
    if (info->nr_must_eat == 0)
        return (NULL);
    i = info->thread_nr;
    if (info->nr_must_eat > 0)
    {
        while ((info->eat_flag == 0) && (info->dead_flag == 0))
        {
            if (!routine_exec(info, i) || !check_all_philos(info))
                break ;
        }
        close_sim(info, i);
    }
    else
    {
        while (info->dead_flag == 0)
        {  
            if (!routine_exec(info, i) || !check_all_philos(info))
                break ;
        }
        close_sim(info, i);
    }
    return (NULL);
}

int routine_exec(t_info *info, int i)
{
    //printf("id - %d\n", info->philo[i].id);
    // printf("r.fork - %d | l.fork - %d\n", info->philo[i].right, info->philo[i].left);
    if (info->philo[i].id == info->nr_philo + 1)
    {
        if (info->dead_flag != 0 || !check_all_philos(info))
            return (0);
        return (1);
    }
    if (info->eat_flag != 0 || info->dead_flag != 0 || (!p_eat(info, i)))
        return (0);
    if (info->nr_philo == 1)
        usleep(info->time_die * 1000);
    if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    p_sleep(info, i);
    if (info->eat_flag != 0 || info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    p_think(info, i);
    info->philo[i].fork = 0;
    return (1);
}