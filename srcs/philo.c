#include "philo.h"

t_p_data    *data(void)
{
    static t_p_data data;
    
    return (&data);
}

void    p_error(t_info *info, char *msg)
{
    if (data()->forks)
        free(data()->forks);
    if (info->philo)
        free(info->philo);
    printf("%s\n", msg);
    exit(1);
}

void    check_args(char **av)
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
            {
                printf("Error! Invalid Arguments !\n");
                exit(1);
            }
            j++;
        }
        i++;
    }
}

int	main(int ac, char **av)
{
    t_info  info;
    //int i;

    if (ac < 5 || ac > 6)
        printf("Error! Wrong Number of Arguments !\n");
    else
    {    
        check_args(av);
        init_data(&info, av);
        start_threads(&info);
        // if (info.philo)
        // {
        //     i = 1;
        //     while (i <= data()->nr_philo)
        //     {
        //         printf("right - %d | left - %d\n", info.philo[i-1].right, info.philo[i-1].left);
        //         //printf("philo id - %d | time_die - %d | must_eat - %d\n", philo[i-1].id, philo[i-1].time_die, philo[i-1].nr_must_eat);
        //         i++;
        //     }
        // }
    }
}
