#include "philo.h"


void    init_info(t_info *info, char **av)
{
    info->nr_philo = ft_atoi(av[1]);
    info->time_die = ft_atoi(av[2]);
    info->time_eat = ft_atoi(av[3]);
    info->time_sleep = ft_atoi(av[4]);
    info->dead_flag = 0;
    info->eat_flag = 0;
    info->start_time = 0;
    info->thread_nr = 0;
    if (av[5])
        info->nr_must_eat = ft_atoi(av[5]);
    else
        info->nr_must_eat = -1;
}

int check_args(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] == 32)
                j++;
            if ((av[i][j] < 48 || av[i][j] > 57) && av[i][j] != '\0')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int	main(int ac, char **av)
{
    t_info  info;
    //int i;

    if (ac < 5 || ac > 6)
        printf("Error! Wrong Number of Arguments !\n");
    else
    {    
        if (!check_args(av))
        {
            printf("Error! Invalid Arguments !\n");
            return (1);
        }
        init_info(&info, av);
        create_philo(&info);
        if (!info.philo)
        {
            printf("Error Creating Philosophers !\n");
            return (1);
        }
        if (!create_threads(&info))
        {
            printf("Error Creating Threads !\n");
            return (1);
        }
        //destroy_mutex(&info);
        free_all(&info);
        // if (info.philo)
        // {
        //     i = 1;
        //     while (i <= info.nr_philo)
        //     {
        //         printf("right - %d | left - %d\n", info.philo[i-1].right, info.philo[i-1].left);
        //         //printf("philo id - %d | time_die - %d | must_eat - %d\n", philo[i-1].id, philo[i-1].time_die, philo[i-1].nr_must_eat);
        //         i++;
        //     }
        // }
        // printf("nr_philo - %d\n", info.nr_philo);
        // printf("time_die - %d\n", info.time_die);
        // printf("time_eat - %d\n", info.time_eat);
        // printf("time_sleep - %d\n", info.time_sleep);
        // printf("nr_must - %d\n", info.nr_must_eat);
        //ft_putstr_fd("succes!\n", 1);
        
    }
}
