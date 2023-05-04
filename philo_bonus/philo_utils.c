/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:00:52 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/04 21:10:18 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoui(const char *str)
{
	unsigned long	number;
	int				i;

	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		ft_error("Only positive values ​​are accepted.", 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	if (number > 4294967295)
		ft_error("Values ​​must be in the range of unsigned int.", 0);
	return (number);
}

useconds_t	timer(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

void	ft_usleep(useconds_t ms)
{
	useconds_t	time;

	time = timer();
	while (timer() - time < ms)
		usleep(ms * 1000);
}

void	printf_sem(char *str, t_philos *philo)
{
	useconds_t				time;

	sem_wait(philo->data->talk);
	time = timer() - philo->data->time_start;
	sem_wait(philo->data->stop_sem);
	if (*(philo->data->stop) == 1)
		printf("(%u) Philo %d %s\n", time, philo->id, str);
	sem_post(philo->data->stop_sem);
	sem_post(philo->data->talk);
}

void	close_and_clean(t_philos *philo)
{
	unsigned int	i;

	i = -1;
	while (++i < philo->data->n_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(philo->data->starvation, NULL);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		sem_unlink("/eat_data");
		sem_close(philo->eat_data);
	}
	sem_unlink("/forks");
	sem_close(philo->data->forks);
	sem_unlink("/talk");
	sem_close(philo->data->talk);
	sem_unlink("/stop_sem");
	sem_close(philo->data->stop_sem);
	ft_multiple_free(2, philo, philo->data->stop);
}
