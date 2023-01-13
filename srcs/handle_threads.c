#include "philo.h"

int create_threads(t_info *info)
{
    int i;

    if (pthread_mutex_init(&info->m_dead_philo, NULL))
        return (0);
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
    return (1);
}

int print_philo(t_info *info, int i, char *color, char *status)
{
	if (info->eat_flag != 0 || info->dead_flag != 0)
		return (0);
	pthread_mutex_lock(&info->m_dead_philo);
	if (info->eat_flag != 0 || info->dead_flag != 0)
	{
        printf("%s%lld ms - Philosopher %d has died\n", RED, get_time(info->start_time), info->philo[i].id);
		pthread_mutex_unlock(&info->m_dead_philo);
		return (0);
	}
	else
		printf("%s%lld ms - Philosopher %d is %s\n", color, get_time(info->start_time), info->philo[i].id, status);
	pthread_mutex_unlock(&info->m_dead_philo);
	return(1);
}