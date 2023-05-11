/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:00:52 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/11 16:23:36 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timer(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long	time;

	time = timer();
	while ((timer() - time) < ms)
		usleep(10);
}

void	printf_sem(char *str, t_philos *philo)
{
	int	time;

	time = timer() - philo->data->time_start;
	sem_wait(philo->data->talk);
	printf("(%d) Philo %d %s\n", time, philo->id, str);
	sem_post(philo->data->talk);
}
