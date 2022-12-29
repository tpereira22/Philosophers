#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_info
{
    int 			nr_philo;
    int 			time_die;
    int 			time_eat;
    int 			time_sleep;
    int 			nr_must_eat;
}   t_info;

typedef struct s_philo
{
    pthread_t   	philo_thread;
    int 			id;
    int 			nr_must_eat;
    int 			time_die;
	struct s_philo	*next;
}	t_philo;

// philo.c
int	check_args(char **av);
void    init_info(t_info *info, char **av);

// handle_philo.c
t_philo	*create_philo(t_info *info);
t_philo *init_philo(t_info *info);
t_philo *new_philo(t_info *info, int index);
t_philo	*last_philo(t_philo *philo);

// handle_threads.c
int	create_threads(t_info *info, t_philo **philo);

#endif