/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:13:26 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/08 22:31:31 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exception(t_philos *philo)
{
	printf_sem("is thinking.", philo);
	while (timer() - philo->data.time_start > philo->data.time_dead)
		usleep(10);
	printf_sem("is dead.", philo);
}

void	*philo_check(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		sem_wait(philo->eat);
		if (timer() - philo->last_meal > philo->data.time_dead)
			sem_post(philo->data.died);
		if (philo->data.ends == 1 && philo->n_eats >= philo->data.n_eats)
			sem_post(philo->eat);
		sem_post(philo->eat);
		usleep(100);
	}
}

void	philo_process(t_philos *philo)
{
	while (1)
	{
		sem_wait(philo->data.forks);
		printf_sem("has taken one fork.", philo);
		sem_wait(philo->data.forks);
		printf_sem("has taken the other fork.", philo);
		printf_sem("is eating.", philo);
		sem_wait(philo->eat);
		philo->last_meal = timer();
		philo->n_eats++;
		sem_post(philo->eat);
		sem_post(philo->data.forks);
		sem_post(philo->data.forks);
		printf_sem("is sleaping.", philo);
		printf_sem("is thinking.", philo);
	}
}

void	philo_born(t_philos *philo, t_data *data, int i)
{
	if (data->n_philos == 1)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			ft_error("Error creating process.", 0);
		else if (philo[i].pid == 0)
			exception(&philo[i]);
		waitpid(philo[i].pid, NULL, 0);
		exit(EXIT_SUCCESS);
	}
	while (++i < data->n_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			ft_error("Error creating process.", 0);
		else if (philo[i].pid == 0)
			philo_process(&philo[i]);
	}
}
