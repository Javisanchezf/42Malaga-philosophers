/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:13:26 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/04 14:33:55 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exception(t_philos *philo)
{
	if (philo->data->n_philos == 1)
	{
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
		while (*(philo->data->stop) == 1)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			ft_usleep(1);
			pthread_mutex_lock(&philo->data->stop_mutex);
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
}

void	eat(t_philos *philo)
{
	sem_wait(philo->data->forks);
	printf_mutex("has taken one fork.", philo);
	sem_wait(philo->data->forks);
	printf_mutex("has taken the other fork.", philo);
	pthread_mutex_lock(&philo->mutex_eat);
	printf_mutex("is eating.", philo);
	philo->last_meal = timer();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->mutex_eat);
	ft_usleep(philo->data->time_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*philo_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	exception(philo);
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (*(philo->data->stop) == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		eat(philo);
		printf_mutex("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep);
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_exit(NULL);
}

void	philo_born(t_philos *philo, t_data *data, unsigned int i)
{
	data->forks = sem_open("forks", O_CREAT, 0644, data->n_philos);
	if (data->forks == SEM_FAILED)
		ft_error("Error creating semaphore.", 2, philo, data->stop);
	while (++i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].n_meals = 0;
		philo[i].last_meal = timer();
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].mutex_eat, NULL))
			ft_error("Error creating mutex.", 2, philo, data->stop);
	}
	if (pthread_mutex_init(&philo->data->talk, NULL))
		ft_error("Error creating mutex.", 2, philo, data->stop);
	if (pthread_mutex_init(&philo->data->stop_mutex, NULL))
		ft_error("Error creating mutex.", 2, philo, data->stop);
	i = -1;
	data->time_start = timer();
	while (++i < data->n_philos)
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
			ft_error("Error creating mutex.", 2, philo, data->stop);
}
