/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/11 16:55:48 by javiersa         ###   ########.fr       */
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

void	close_and_clean(t_philos *philo)
{
	int	i;

	i = -1;
	// sleep(1);
	// while (++i < philo->data->n_philos)
	// 	kill(philo[i].pid, SIGKILL);
	pthread_join(philo->data->ckeck_thread, NULL);
	while (++i < philo->data->n_philos)
		waitpid(philo[i].pid, NULL, 0);
	sem_unlink("/forks");
	sem_unlink("/talk");
	sem_unlink("/stop");
	sem_close(philo->data->stop_sem);
	sem_close(philo->data->talk);
	sem_close(philo->data->forks);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		sem_unlink("/n_meals");
		sem_unlink("/t_meal");
		sem_close(philo[i].n_meals);
		sem_close(philo[i].t_meal);
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
	if (pthread_create(&data.ckeck_thread, NULL, check_thread, philo))
		return (ft_error("Error creating thread."));
	data.time_start = timer();
	sem_wait(philo->data->stop_sem);
	while(++i < data.n_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo_fork(&philo[i]);
			exit(EXIT_SUCCESS);
		}			
		// if (philo[i].pid < 0)
			//fail
	}
	// printf("%s", (char *)&(HEADER));
	sem_post(philo->data->stop_sem);
	if (philo->pid > 0)
		close_and_clean(philo);
	// i++;
	// close_and_clean(philo);
	return (0);
}
