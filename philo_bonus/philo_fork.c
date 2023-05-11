/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:13:26 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/11 16:22:19 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philos *philo, long start)
{
	long	eat_time;
	long	i;

	sem_wait(philo->data->forks);
	printf_sem("has taken the forks and is eating.", philo);
	sem_post(philo->n_meals);
	eat_time = timer();
	i = -1;
	while (++i < (eat_time - start - philo->last_meal))
		sem_post(philo->t_meal);
	philo->last_meal = eat_time;
	ft_usleep(philo->data->time_eat);
	sem_post(philo->data->forks);
}

void	philo_fork(t_philos *philo)
{
	while (1)
	{
		eat(philo, philo->data->time_start);
		printf_sem("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep);
		if (philo->data->time_sleep == 0)
			usleep(1);
		printf_sem("is thinking.", philo);
	}
}
