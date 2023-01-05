#include "philo.h"

void    *routine(void *args)
{
    t_info  *info;
    int i;

    info = (t_info *)args;
    i = info->thread_nr;
    if (info->nr_must_eat > 0)
    {
        while (check_eat_all(info) && (info->dead_flag == 0))
        {
            if (i == info->nr_philo)
            {
                if (!check_all_philos(info))
                    break ;
            }
            else
            {
                if (!routine_exec(info, i))
                    break ;
            }
        }
        close_sim(info, i);
    }
    else
    {
        while (info->dead_flag == 0)
        {
            if (i == info->nr_philo)
            {
                if (!check_all_philos(info))
                    break ;
            }
            else
            {
                if (!routine_exec(info, i))
                    break ;
            }
        }
        close_sim(info, i);
    }
    return (NULL);
}

int routine_exec(t_info *info, int i)
{
    if (info->dead_flag != 0 || (!p_eat(info, i)))
        return (0);
    if (info->nr_philo == 1)
        usleep(info->time_die * 1000);
    if (info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    p_sleep(info, i);
    if (info->dead_flag != 0 || !check_all_philos(info))
        return (0);
    p_think(info, i);
    info->philo[i].fork = 0;
    return (1);
}

int create_threads(t_info *info)
{
    int i;

    i = 0;
    info->start_time = get_time(0);
    while (i <= info->nr_philo)
    {
        info->thread_nr = i;
        info->philo[i].last_eat = get_time(info->start_time);
        pthread_create(&info->philo[i].philo_thread, NULL, &routine, (void*)info);
        //printf("i - %d\n", i);
        usleep(1000);
        i++;
    }
    i = 0;
    while ((i + 1) <= info->nr_philo)
    {
        pthread_join(info->philo[i].philo_thread, NULL);
        i++;
    }
    return (1);
}