#include "../philo.h"
#include "../libft/libft.h"


void    init_info(t_info *info, char **av)
{
    info->nr_philo = ft_atoi(av[1]);
    info->time_die = ft_atoi(av[2]);
    info->time_eat = ft_atoi(av[3]);
    info->time_sleep = ft_atoi(av[4]);
    if (av[5])
        info->nr_must_eat = ft_atoi(av[5]);
    else
        info->nr_must_eat = 0;
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
    t_philo *philo;
	
    if (ac < 5 || ac > 6)
        ft_putstr_fd("Wrong Number of Arguments !\n", 1);
    else
    {    
        if (!check_args(av))
        {
            ft_putstr_fd("Invalid Arguments !\n", 1);
            return (1);
        }
        init_info(&info, av);
        philo = NULL;
        philo = create_philo(&info);
        if (!philo)
        {
            ft_putstr_fd("Error Creating Philosophers !\n", 1);
            return (1);
        }
        if (!create_threads(&info, &philo))
        {
            ft_putstr_fd("Error Creating Philosophers !\n", 1);
            return (1);
        }
        // if (philo)
        // {
        //     while (philo->next)
        //     {
        //         printf("philo id - %d | time_die - %d | must_eat - %d\n", philo->id, philo->time_die, philo->nr_must_eat);
        //         philo = philo->next;
        //     }
        //     printf("philo id - %d | time_die - %d | must_eat - %d\n", philo->id, philo->time_die, philo->nr_must_eat);
        // }
        // printf("nr_philo - %d\n", info.nr_philo);
        // printf("time_die - %d\n", info.time_die);
        // printf("time_eat - %d\n", info.time_eat);
        // printf("time_sleep - %d\n", info.time_sleep);
        // printf("nr_must - %d\n", info.nr_must_eat);
        //ft_putstr_fd("succes!\n", 1);
        
    }
}
