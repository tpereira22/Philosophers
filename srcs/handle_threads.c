#include "philo.h"

void    *routine(void *args)
{
    t_info  *info;
    int i;

    info = (t_info *)args;
    i = info->thread_nr;
    if (info->nr_must_eat > 0)
    {
        while ((info->philo[i].eat_counter < info->nr_must_eat) && (info->philo[i].philo_dead == 0))
        {
            routine_exec(info, i);
        }
    }
    else
    {
        while (info->philo[i].philo_dead == 0)
        {
            routine_exec(info, i);
        }
    }
    return (NULL);
}

void    routine_exec(t_info *info, int i)
{
    if (check_philo_dead(info, i))
    {    
        if (!p_eat(info, i))
            printf("Error mutex lock");
    }
    if (check_philo_dead(info, i))
        p_sleep(info, i);
    if (check_philo_dead(info, i))
        p_think(info, i);
}

int create_threads(t_info *info)
{
    int i;

    i = 0;
    info->start_time = get_time(0);
    while ((i + 1) <= info->nr_philo)
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