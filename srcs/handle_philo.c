#include "philo.h"

int init_philo(t_info *info, int i, int j)
{
    info->philo[i].id = j;
    info->philo[i].time_die = info->time_die;
    info->philo[i].eat_counter = 0;
    info->philo[i].philo_dead = 0;
    info->philo[i].fork_left = i;
    if (j == info->nr_philo)
        j = 0;
    info->philo[i].fork_right = j;
    return (1);
}

t_info *create_philo(t_info *info)
{
    int i;
    int j;

    info->philo = malloc(sizeof(t_philo) * (info->nr_philo));
    if (info->philo == NULL)
        return (NULL);
    i = 0;
    j = 1;
    while (j <= info->nr_philo)
    {
        if (!init_philo(info, i, j))
            return (NULL);
        i++;
        j++;
    }
    if (!create_mutex(info))
    {
        printf("mutex error\n");
        return (NULL);
    }
    return (info);
}