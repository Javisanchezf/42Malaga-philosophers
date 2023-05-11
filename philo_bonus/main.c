/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/11 21:34:37 by javiersa         ###   ########.fr       */
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

void	close_and_clean2(t_philos *philo)
{
	int	i;

	i = -1;
	// while (++i < philo->data->n_philos)
	// 	kill(philo[i].pid, SIGKILL);
	sem_unlink("/forks");
	sem_unlink("/talk");
	sem_unlink("/stop");
	sem_close(philo->data->stop_sem);
	sem_close(philo->data->talk);
	sem_close(philo->data->forks);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		sem_unlink("/philo_sem");
		sem_close(philo[i].philo_sem);
	}
}

int	main(int narg, char **argv)
{
	t_data			data;
	t_philos		philo[242];
	int				i;

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
			printf("FAIL"); // hacer cositas
	}
	if (philo->pid > 0)
		check_philos(philo);
	// close_and_clean2(philo);
	return (0);
}
