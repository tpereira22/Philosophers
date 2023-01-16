/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:57:13 by timartin          #+#    #+#             */
/*   Updated: 2023/01/16 18:15:44 by timartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_p_data	*data(void)
{
	static t_p_data	data;

	return (&data);
}

void	p_error(t_info *info, char *msg)
{
	if (data()->forks)
		free(data()->forks);
	if (info->philo)
		free(info->philo);
	printf("%s\n", msg);
	exit(1);
}

void	check_args(char **av)
{
	int	i;
	int	j;

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
	t_info	info;

	if (ac < 5 || ac > 6)
		printf("Error! Wrong Number of Arguments !\n");
	else
	{
		check_args(av);
		init_data(&info, av);
		start_threads(&info);
		free_and_destroy(&info);
	}
}
