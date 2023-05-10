/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:13:26 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/10 14:09:36 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*exception(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->data->n_philos == 1)
	{
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
		while (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			usleep(1);
			pthread_mutex_lock(&philo->data->stop_mutex);
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	pthread_exit(NULL);
}

void	eat(t_philos *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
	}
	pthread_mutex_lock(&philo->mutex_eat);
	printf_mutex("is eating.", philo);
	philo->last_meal = timer();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->mutex_eat);
	ft_usleep(philo->data->time_eat, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(&philo->fork_r);
}

void	*philo_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		eat(philo);
		printf_mutex("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep, philo);
		if (philo->data->time_sleep == 0)
			usleep(1);
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_exit(NULL);
}
