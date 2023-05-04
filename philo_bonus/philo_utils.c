/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:00:52 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/04 14:36:03 by javiersa         ###   ########.fr       */
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
		usleep(10);
}

void	printf_mutex(char *str, t_philos *philo)
{
	useconds_t				time;

	pthread_mutex_lock(&philo->data->talk);
	time = timer() - philo->data->time_start;
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (*(philo->data->stop) == 1)
		printf("(%u) Philo %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->talk);
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
		pthread_mutex_destroy(&philo[i].mutex_eat);
	sem_close(philo->data->forks);
	sem_unlink("/forks");
	pthread_mutex_destroy(&philo->data->talk);
	pthread_mutex_destroy(&philo->data->stop_mutex);
	ft_multiple_free(2, philo, philo->data->stop);
}
