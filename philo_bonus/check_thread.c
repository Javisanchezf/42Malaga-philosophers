/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:33:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/11 16:55:20 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_eat(void	*param)
{
	t_philos	*philo;
	int			n_philos;
	int			i;
	int			j;

	philo = (t_philos *)param;
	n_philos = philo->data->n_philos;
	i = -1;
	while (++i < n_philos)
	{
		j = -1;
		while (++j < philo->data->n_eats)
			sem_wait(philo[i].n_meals);
	}
	sem_wait(philo->data->talk);
	sem_wait(philo->data->stop_sem);
	if (philo->data->stop == 1)
		printf("All the philosophers have eaten!\n");
	philo->data->stop = 0;
	sem_post(philo->data->stop_sem);
	pthread_exit(NULL);
}

void	*check_death(void	*param)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)param;
	i = -1;
	while (++i < philo->data->n_philos)
		sem_wait(philo->t_meal);
	sem_wait(philo->data->stop_sem);
	philo->data->ends = 1;
	sem_post(philo->data->stop_sem);
	pthread_exit(NULL);
}

void	close_all(t_philos *philo, pthread_t eat, pthread_t death)
{
	int	i;
	int	j;

	i = -1;
	if (philo->data->stop == 1)
	{
		sem_wait(philo->data->stop_sem);
		sem_wait(philo->data->talk);
		printf("One philo is dead.");
		philo->data->stop = 0;
		sem_post(philo->data->stop_sem);
		sem_post(philo->data->talk);
	}
	while (++i < philo->data->n_philos)
		kill(philo[i].pid, SIGKILL);
	i = -1;
	while (++i < philo->data->n_philos)
		sem_post(philo->n_meals);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		j = -1;
		while (++j < philo->data->n_eats)
			sem_post(philo[i].n_meals);
	}
	pthread_join(eat, NULL);
	pthread_join(death, NULL);
}

void	*check_thread(void	*param)
{
	t_philos	*philo;
	pthread_t	eat;
	pthread_t	death;

	philo = (t_philos *)param;
	usleep(1);
	sem_wait(philo->data->stop_sem);
	if (philo->data->ends == 1)
		if (pthread_create(&eat, NULL, check_eat, philo))
			exit (ft_error("Error creating thread."));
	ft_usleep(philo->data->time_dead);
	while (philo->data->stop == 1)
	{
		sem_post(philo->data->stop_sem);
		philo->data->ends = 0;
		if (pthread_create(&death, NULL, check_death, philo))
			exit (ft_error("Error creating thread."));
		ft_usleep(1);
		sem_wait(philo->data->stop_sem);
		if (philo->data->ends == 0)
			break ;
	}
	sem_post(philo->data->stop_sem);
	close_all(philo, eat, death);
	pthread_exit(NULL);
}
