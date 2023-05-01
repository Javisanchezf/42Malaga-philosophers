/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/04/29 23:23:18 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	// pthread_mutex_t		startmutex;

void	check_args(int narg, char **argv)
{
	int	i;

	i = 0;
	if (narg != 5 && narg != 6)
		ft_error(INSTRUCTIONS, 0);
	while (--narg > 0)
	{
		i = -1;
		while(argv[narg][++i])
			if (argv[narg][i] < '0' || argv[narg][i] > '9')
				ft_error("Arguments can only be unsigned positive integers.", 0);
	}
}

t_data	parse_data(int narg, char **argv)
{
	t_data		data;

	check_args(narg, argv);
	data.ends = malloc (1 * sizeof(short int));
	if (!data.ends)
		ft_error("Error allocating memory.", 0);
	data.stop = malloc (1 * sizeof(short int));
	if (!data.stop)
		ft_error("Error allocating memory.", 1, data.ends);
	*(data.ends) = 0;
	*(data.stop) = 1;
	data.n_philos = ft_atoui(argv[1]);
	data.time_dead = ft_atoui(argv[2]);
	data.time_eat = ft_atoui(argv[3]);
	data.time_sleep = ft_atoui(argv[4]);
	if (narg == 6)
	{
		*(data.ends) = 1;
		data.n_eats = ft_atoui(argv[5]);
	}
	return(data); 
}

void *philo_right_handed(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	// while (!*(philo->data->stop)) //Para esperar a que se creen todos los filos
	// 	usleep(1);
	// pthread_mutex_lock(&startmutex);
	// pthread_mutex_unlock(&startmutex);
	gettimeofday(&philo->last_meal, NULL);
    printf("%d Tiempo transcurrido: %ld microsegundos\n", philo->id,philo->last_meal.tv_usec - philo->data->time_start.tv_usec);
	int i = 0;
	while (*(philo->data->stop) && ++i < 2)
	{
		pthread_mutex_lock(&philo->fork_r);
		pthread_mutex_lock(philo->fork_l);
		if (*(philo->data->stop))
			printf("Philo %d is eating.\n", philo->id);
		usleep(philo->data->time_eat);
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		if (*(philo->data->stop))
		{
			printf("Philo %d is sleaping.\n", philo->id);
			usleep(philo->data->time_sleep);
		}
		printf("Philo %d is thinking.\n", philo->id);
	}
	pthread_exit(NULL);
}

void *philo_left_handed(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	// while (!*(philo->data->stop))
	// 	usleep(1);
	// pthread_mutex_lock(&startmutex);
	// pthread_mutex_unlock(&startmutex);
	gettimeofday(&philo->last_meal, NULL);
	int i = 0;
	while (*(philo->data->stop) && ++i < 10)
	{
		printf("Philo %d is sleaping.\n", philo->id);
		usleep(philo->data->time_sleep);
		if (*(philo->data->stop))
		{
			printf("Philo %d is thinking.\n", philo->id);
			pthread_mutex_lock(philo->fork_l);
			pthread_mutex_lock(&philo->fork_r);
			if (*(philo->data->stop))
				printf("Philo %d is eating.\n", philo->id);
			usleep(philo->data->time_eat);
			pthread_mutex_unlock(&philo->fork_r);
			pthread_mutex_unlock(philo->fork_l);
		}
	}
	pthread_exit(NULL);
}

void	close_and_clean(t_philos *philo)
{
	unsigned int	i;

	i = -1;
	while (++i < philo->data->n_philos)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while(++i < philo->data->n_philos)
		pthread_mutex_destroy(&philo[i].fork_r);
	ft_multiple_free(3, philo, philo->data->stop, philo->data->ends);
}

t_philos	*philo_born(t_data *data)
{
	unsigned int	i;
	t_philos	*philo;

	i = -1;
	if (data->n_philos == 0)
		ft_error("There is no philosopher.", 2, data->ends, data->stop);
	if (data->n_philos == 1)
	{
		printf("Philo 1 is thinking.\n");
		usleep(data->time_dead);
		printf("Philo 1 is dead.\n");
		ft_multiple_free(2, data->ends, data->stop);
		exit(EXIT_SUCCESS);
	}//Prevenir si filosofos == 1 esperar al timedead, intentar hacerlo automatico y debe ser un hilo
	philo = malloc(data->n_philos * sizeof(t_philos));
	if (!philo)
		ft_error("Error allocating memory.", 2, data->ends, data->stop);
	while (++i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].fork_r, NULL))
			ft_error("Error creating thread", 1, philo);
		if (i != 0)
			philo[i].fork_l = &philo[i - 1].fork_r;
	}
	philo[0].fork_l = &philo[i - 1].fork_r;
	i = -1;
	gettimeofday(&data->time_start, NULL);
	// pthread_mutex_lock(&startmutex);
	while (++i < data->n_philos)
	{
		if (philo[i].id % 2 == 1)
			if (pthread_create(&philo[i].thread, NULL, philo_right_handed, &philo[i]))
				ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
		if (philo[i].id % 2 == 0)
			if (pthread_create(&philo[i].thread, NULL, philo_left_handed, &philo[i]))
				ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
	}
	// gettimeofday(&data->time_start, NULL);
	// *(philo->data->stop) = 1;
	// printf("ALL PHILOS BORN\n");
	// pthread_mutex_unlock(&startmutex);
	usleep(2);
	return(philo);
}

void	ft_leaks(void)
{
	system("leaks -q a.out");
}

int	main(int narg, char **argv)
{
	t_data	data;
	t_philos	*philos;

	atexit(ft_leaks);
	data = parse_data(narg, argv);
	philos = philo_born(&data);
	long microseconds =philos[0].last_meal.tv_usec;
    printf("Tiempo transcurrido: %ld microsegundos\n", microseconds - data.time_start.tv_usec);
	close_and_clean(philos);
	return(0);
}
