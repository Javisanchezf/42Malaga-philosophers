/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:13:26 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/04 21:17:13 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exception(t_philos *philo)
{
	if (philo->data->n_philos == 1)
	{
		printf_sem("is thinking.", philo);
		sem_wait(philo->data->stop_sem);
		while (*(philo->data->stop) == 1)
		{
			sem_post(philo->data->stop_sem);
			ft_usleep(1);
			sem_wait(philo->data->stop_sem);
		}
		sem_post(philo->data->stop_sem);
	}
}

void	eat(t_philos *philo)
{
	sem_wait(philo->data->forks);
	printf_sem("has taken one fork.", philo);
	sem_wait(philo->data->forks);
	printf_sem("has taken the other fork.", philo);
	sem_wait(philo->eat_data);
	printf_sem("is eating.", philo);
	philo->last_meal = timer();
	philo->n_meals++;
	sem_post(philo->eat_data);
	ft_usleep(philo->data->time_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*philo_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	exception(philo);
	sem_wait(philo->data->stop_sem);
	while (*(philo->data->stop) == 1)
	{
		sem_post(philo->data->stop_sem);
		eat(philo);
		printf_sem("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep);
		printf_sem("is thinking.", philo);
		sem_wait(philo->data->stop_sem);
	}
	sem_post(philo->data->stop_sem);
	pthread_exit(NULL);
}

void	philo_born(t_philos *philo, t_data *data, unsigned int i)
{
	data->forks = sem_open("forks", O_CREAT, 0644, data->n_philos);
	data->talk = sem_open("talk", O_CREAT, 0644, 1);
	data->stop_sem = sem_open("stop_sem", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->talk == SEM_FAILED || \
	data->stop_sem == SEM_FAILED)
		ft_error("Error creating semaphore.", 2, philo, data->stop);
	while (++i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].n_meals = 0;
		philo[i].last_meal = timer();
		philo[i].data = data;
		philo[i].eat_data = sem_open("eat_data", O_CREAT, 0644, 1);
		if (philo->eat_data == SEM_FAILED)
			ft_error("Error creating semaphore.", 2, philo, data->stop);
	}
	i = -1;
	data->time_start = timer();
	while (++i < data->n_philos)
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
			ft_error("Error creating thread.", 2, philo, data->stop);
}
