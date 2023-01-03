#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define CYAN "\033[96m"

typedef struct s_philo
{
    pthread_t   	philo_thread;
    int 			id;
    int 			eat_counter;
    int 			time_die;
    int             fork_right;
    int             fork_left;
    int             philo_dead;
}	t_philo;

typedef struct s_info
{
    int 			nr_philo;
    int 			time_die;
    int 			time_eat;
    int 			time_sleep;
    int 			nr_must_eat;
    int             thread_nr;
    pthread_mutex_t *m_fork;
    t_philo         *philo;
}   t_info;

// philo.c
int	check_args(char **av);
void    init_info(t_info *info, char **av);

//philo_utils.c
int	ft_atoi(const char *str);
long long   get_time(void);

// handle_philo.c
t_info *create_philo(t_info *args);
int init_philo(t_info *info, int i, int j);

// handle_threads.c
int	create_threads(t_info *info);
void    *routine(void *info);
void    routine_exec(t_info *info, int i);

//handle_actions.c
int p_eat(t_info *info, int i);
void    p_sleep(t_info *info, int i);
void    p_think(t_info *info, int i);

//handle_mutex.c
int create_mutex(t_info *info);

#endif