#include "../philo.h"
#include "../libft/libft.h"

void    *routine()
{
    printf("HEEEEY!\n");
    return (NULL);
}

int create_threads(t_info *info, t_philo **philo)
{
    int i;

    i = 1;
    while (i <= info->nr_philo)
    {
        pthread_create(&(*philo)[i-1].philo_thread, NULL, &routine, NULL);
        //printf("i - %d\n", i);
        i++;
    }
    //printf("%d\n", get_time(0));
    i = 1;
    while (i <= info->nr_philo)
    {
        pthread_join((*philo)[i-1].philo_thread, NULL);
        i++;
    }
    return (1);
}