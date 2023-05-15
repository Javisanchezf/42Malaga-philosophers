/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:00:52 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/12 18:00:50 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timer(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

void	ft_usleep(int ms, t_philos *philo)
{
	int	time;

	time = timer();
	pthread_mutex_lock(&philo->data->stop_mutex);
	while ((timer() - time < ms) && philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		usleep(10);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

void	printf_mutex(char *str, t_philos *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->talk);
	time = timer() - philo->data->time_start;
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
		printf("(%d) Philo %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->talk);
}
