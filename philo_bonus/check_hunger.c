/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hunger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:33:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/04 15:15:16 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(unsigned int i, t_philos *philo, int *flag, useconds_t time)
{
	while (++i < philo->data->n_philos)
	{
		sem_wait(philo[i].eat_data);
		time = timer() - philo[i].last_meal;
		if (time > philo->data->time_dead)
		{
			sem_wait(philo->data->stop_sem);
			*(philo->data->stop) = 0;
			sem_post(philo->data->stop_sem);
			sem_post(philo[i].eat_data);
			sem_wait(philo->data->talk);
			printf("(%ld) Philo %d is dead.\n", timer() - \
			philo->data->time_start, philo->id);
			sem_post(philo->data->talk);
			i = -1;
			while (++i < philo->data->n_philos)
				sem_post(philo->data->forks);
			return (0);
		}
		if (philo->data->ends == 1 && philo[i].n_meals < philo->data->n_eats)
			*(flag) = 1;
		sem_post(philo[i].eat_data);
	}
	return (1);
}

int	check_all_eat(t_philos *philo, int flag)
{
	if (philo->data->ends == 1 && flag == 0)
	{
		sem_wait(philo->data->stop_sem);
		*(philo->data->stop) = 0;
		sem_post(philo->data->stop_sem);
		sem_wait(philo->data->talk);
		printf("All the philosophers have eaten!\n");
		sem_post(philo->data->talk);
		return (0);
	}
	return (1);
}

void	*check_hunger(void	*param)
{
	unsigned int	i;
	t_philos		*philo;
	int				flag;
	useconds_t		time;

	philo = (t_philos *)param;
	i = -1;
	sem_wait(philo->data->stop_sem);
	while (*(philo->data->stop))
	{
		sem_post(philo->data->stop_sem);
		i = -1;
		flag = 0;
		time = 0;
		ft_usleep(1);
		if (check_death(i, philo, &flag, time) == 0)
			return (NULL);
		if (check_all_eat(philo, flag) == 0)
			return (NULL);
		sem_wait(philo->data->stop_sem);
	}
	sem_post(philo->data->stop_sem);
	return (NULL);
}
