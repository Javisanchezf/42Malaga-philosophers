/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:00:52 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/08 21:54:23 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

useconds_t	timer(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

// void	ft_usleep(useconds_t ms)
// {
// 	useconds_t	time;

// 	time = timer();
// 	while (timer() - time < ms)
// 		usleep(10);
// }

// void	printf_sem(char *str, t_philos *philo)
// {
// 	useconds_t				time;

// 	sem_wait(philo->data->talk);
// 	time = timer() - philo->data->time_start;
// 	sem_wait(philo->data->stop_sem);
// 	printf("(%u) Philo %d %s\n", time, philo->id, str);
// 	sem_post(philo->data->stop_sem);
// 	sem_post(philo->data->talk);
// }

// void	close_and_clean(t_philos *philo)
// {
// 	unsigned int	i;

// 	i = -1;
// 	pthread_join(philo->data->starvation, NULL);
// 	while (++i < philo->data->n_philos)
// 		kill (philo->data->pid[i], SIGKILL);
// 	i = -1;
// 	while (++i < philo->data->n_philos)
// 	{
// 		sem_unlink("/eat_sem");
// 		sem_close(philo[i].eat_sem);
// 		sem_unlink("/n_meals");
// 		sem_close(philo[i].n_meals);
// 	}
// 	sem_unlink("/forks");
// 	sem_close(philo->data->forks);
// 	sem_unlink("/talk");
// 	sem_close(philo->data->talk);
// 	sem_unlink("/stop_sem");
// 	sem_close(philo->data->stop_sem);
// 	ft_multiple_free(1, philo);
// }
