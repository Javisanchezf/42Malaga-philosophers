/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:13:26 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/11 21:42:39 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_check_death(void *arg)
{
	t_philos	*philo;
	long		aux;

	philo = (t_philos *)arg;
	while (1)
	{
		sem_wait(philo->philo_sem);
		aux = philo->last_meal;
		sem_post(philo->philo_sem);
		if (aux + philo->data->time_dead < timer())
		{
			sem_wait(philo->data->talk);
			printf("(%ld) Philo %d is dead.\n", timer() - \
			philo->data->time_start, philo->id);
			sem_post(philo->data->stop_sem);
			break ;
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	eat(t_philos *philo)
{
	sem_wait(philo->data->forks);
	printf_sem("has taken the forks and is eating.", philo);
	sem_post(philo->n_meals);
	sem_wait(philo->philo_sem);
	philo->last_meal = timer();
	sem_post(philo->philo_sem);
	ft_usleep(philo->data->time_eat);
	sem_post(philo->data->forks);
}

void	philo_fork(t_philos *philo)
{
	pthread_t	death;

	sem_wait(philo->philo_sem);
	philo->last_meal = timer();
	pthread_create(&death, NULL, ft_check_death, philo);
	pthread_detach(death);
	sem_post(philo->philo_sem);
	while (1)
	{
		eat(philo);
		printf_sem("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep);
		if (philo->data->time_sleep == 0)
			usleep(1);
		printf_sem("is thinking.", philo);
	}
}
