#include "../philo.h"
#include "../libft/libft.h"

void    init_philo(t_info *info, t_philo **philo, int i, int j)
{
    (*philo)[i].id = j;
    (*philo)[i].time_die = info->time_die;
    (*philo)[i].nr_must_eat = info->nr_must_eat;
    (*philo)[i].fork = malloc(sizeof(t_fork));
    (*philo)[i].fork->right = i;
    if (j == info->nr_philo)
        j = 0;
    (*philo)[i].fork->left = j;
}

t_philo *create_philo(t_info *info, t_philo **philo)
{
    int i;
    int j;

    *philo = malloc(sizeof(t_philo) * (info->nr_philo));
    if (*philo == NULL)
        return (NULL);
    i = 0;
    j = 1;
    while (j <= info->nr_philo)
    {
        init_philo(info, philo, i, j);
        i++;
        j++;
    }
    return (*philo);
}

t_philo *check_philo(t_info *info)
{
    t_philo *philo;

    if (info->nr_philo == 1)
        printf("ola\n");
    else
    {
        create_philo(info, &philo);
    }
    return (philo);
}