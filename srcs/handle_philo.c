#include "../philo.h"
#include "../libft/libft.h"

t_philo	*last_philo(t_philo *philo)
{
	if (!philo)
		return (NULL);
	while (philo->next)
		philo = philo->next;
	return (philo);
}

t_philo *new_philo(t_info *info, int index)
{
    t_philo *tmp_philo;

	tmp_philo = malloc(sizeof(t_philo));
	if (!tmp_philo)
		ft_putstr_fd("Error Creating Philo\n", 1);
	tmp_philo->id = index;
    tmp_philo->time_die = info->time_die;
    tmp_philo->nr_must_eat = info->nr_must_eat;
	tmp_philo->next = NULL;
	return (tmp_philo);
}

t_philo *init_philo(t_info *info)
{
    t_philo *tmp_philo;
    t_philo *first_philo;
    int i;

    i = 1;
    tmp_philo = NULL;
    while (i <= info->nr_philo)
    {
        if (!tmp_philo)
        {
            tmp_philo = new_philo(info, i);
            first_philo = tmp_philo;
        }
        else
        {
            tmp_philo = last_philo(tmp_philo);
            tmp_philo->next = new_philo(info, i);
        }
        i++;
    }
    return (first_philo);
}

t_philo *create_philo(t_info *info)
{
    t_philo *philo;

    if (info->nr_philo == 1)
        printf("ola\n");
    else
    {
        philo = init_philo(info);
    }
    return (philo);
}