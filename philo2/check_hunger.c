/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hunger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:33:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/10 12:57:51 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(int i, t_philos *philo, int *flag)
{
	int		time;

	while (++i < philo->data->n_philos)
	{
		pthread_mutex_lock(&philo[i].mutex_eat);
		time = timer() - philo[i].last_meal;
		if (time > philo->data->time_dead)
		{
			pthread_mutex_lock(&philo->data->stop_mutex);
			philo->data->stop = 0;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			pthread_mutex_unlock(&philo[i].mutex_eat);
			pthread_mutex_lock(&philo->data->talk);
			printf("(%ld) Philo %d is dead.\n", timer() - \
			philo->data->time_start, philo->id);
			pthread_mutex_unlock(&philo->data->talk);
			return (0);
		}
		if (philo->data->ends == 1 && philo[i].n_meals < philo->data->n_eats)
			*(flag) = 1;
		pthread_mutex_unlock(&philo[i].mutex_eat);
	}
	return (1);
}

int	check_all_eat(t_philos *philo, int flag)
{
	if (philo->data->ends == 1 && flag == 0)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = 0;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_lock(&philo->data->talk);
		printf("All the philosophers have eaten!\n");
		pthread_mutex_unlock(&philo->data->talk);
		return (0);
	}
	return (1);
}

void	*check_hunger(void	*param)
{
	int	i;
	t_philos		*philo;
	int				flag;

	philo = (t_philos *)param;
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		i = -1;
		flag = 0;
		usleep(1);
		if (check_death(i, philo, &flag) == 0)
			return (NULL);
		if (check_all_eat(philo, flag) == 0)
			return (NULL);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (NULL);
}
