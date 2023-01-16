#include "philo.h"

void    *routine(void *args)
{
    t_philo  *philo;

    philo = (t_philo *)args;
    if (philo->id % 2 == 0)
        usleep(15000);
    while (check_all(philo))
    {
        if (philo->id == data()->nr_philo + 1)
        {
            //printf("id - %d\n", philo->id);
            check_all(philo);
        }
        else
        {
            if (data()->nr_philo == 1)
                philo_one(philo);
            else
            {
                if (check_all(philo))
                    eat(philo);
                if (check_all(philo))
                    zzz_sleep(philo);
                if (check_all(philo))
                    printf("%s%lld ms -> Philosopher %d %s\n", YELLOW, get_time(data()->start_time), philo->id, THINK);
            }
        }
    }
    return (NULL);
}

void    start_threads(t_info *info)
{
    int i;

    if (data()->nr_must_eat == 0)
        exit(0);
    data()->start_time = get_time(0);
    i = -1;
    while (++i <= data()->nr_philo)
    {
        info->philo[i].last_eat = data()->start_time;
        if (pthread_create(&info->philo[i].philo_thread, NULL, &routine, &info->philo[i]))
            p_error(info, "Philo thread fail\n");
        //usleep(1000);
    }
    i = -1;
    while (++i <= data()->nr_philo)
        pthread_join(info->philo[i].philo_thread, NULL);
    
}

void    philo_one(t_philo *philo)
{
    printf("%s%lld ms -> Philosopher %d %s\n", CYAN, get_time(data()->start_time), philo->id, FORK);
    usleep(data()->time_die * 1000);
    printf("%s%lld ms -> Philosopher %d %s\n", RED, get_time(data()->start_time), philo->id, DEAD);
    pthread_mutex_lock(&data()->m_dead_philo);
    data()->dead_flag = 1;
    pthread_mutex_unlock(&data()->m_dead_philo);
}