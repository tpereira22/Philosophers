#include "../philo.h"
#include "../libft/libft.h"

void    *routine()
{
    printf("HEEEEY!\n");
    return (NULL);
}

int create_threads(t_info *info, t_philo **philo)
{
    pthread_create(&(*philo)->philo_thread, NULL, &routine, NULL);
    printf("%d\n", get_time(0));
    pthread_join((*philo)->philo_thread, NULL);
    (void)info;
    return (1);
}