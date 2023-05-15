/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/12 18:25:05 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *s)
{
	int	i;

	i = 0;
	write (2, "❌ \033[31;1m", 12);
	while (s[i])
	{
		write (2, &s[i], sizeof(char));
		i++;
	}
	write (2, "\n\033[0m", 6);
	return (1);
}

void	preclean(void)
{
	sem_unlink("/forks");
	sem_unlink("/talk");
	sem_unlink("/stop");
	sem_unlink("/n_meals");
	sem_unlink("/philo_sem");
}

int	main(int narg, char **argv)
{
	t_data			data;
	t_philos		philo[242];
	int				i;

	preclean();
	if (parse(narg, argv, &data, philo) != 0)
		return (1);
	i = -1;
	data.time_start = timer();
	while (++i < data.n_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo_fork(&philo[i]);
			exit(EXIT_SUCCESS);
		}			
		if (philo[i].pid < 0)
			return (ft_error("Failed to create the processes."));
	}
	if (philo->pid > 0)
		check_philos(philo);
	return (0);
}
