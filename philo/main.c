/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/01 22:13:11 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
		usleep(ms / 10);
}

void	printf_mutex(char *str, t_philos *philo)
{
	useconds_t				time;

	pthread_mutex_lock(&philo->data->talk);
	time = timer() - philo->data->time_start;
	if (*(philo->data->stop))
		printf("(%u) Philo %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->talk);
}

// void	*check_starvation(void	*param)
// {
// 	unsigned int	i;
// 	t_philos		*philo;

// 	philo = (t_philos *)param;
// 	i = -1;
// 	while (*(philo->data->stop))
// 	{
// 		i = -1;
// 		ft_usleep(philo->data->time_dead);
// 		while (++i < philo->data->n_philos)
// 		{
// 			if (timer() - philo[i].last_meal >= philo->data->time_dead)
// 			{
// 				*(philo->data->stop) = 0;
// 				printf("(%ld) Philo %d is dead.\n", timer() - philo->data->time_start, philo->id);
// 				return (NULL);
// 			}
// 		}
// 	}
// 	return (NULL);
// }

void	check_args(int narg, char **argv)
{
	int	i;

	i = 0;
	if (narg != 5 && narg != 6)
		ft_error(INSTRUCTIONS, 0);
	while (--narg > 0)
	{
		i = -1;
		while (argv[narg][++i])
			if (argv[narg][i] < '0' || argv[narg][i] > '9')
				ft_error("Arguments can only be unsigned \
				positive integers.", 0);
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
	return (data);
}

void	*philo_right_handed(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (*(philo->data->stop))
	{
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
		printf_mutex("is eating.", philo);
		philo->last_meal = timer();
		ft_usleep(philo->data->time_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
		printf_mutex("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep);
		printf_mutex("is thinking.", philo);
	}
	pthread_exit(NULL);
}

void	*philo_left_handed(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (*(philo->data->stop))
	{
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
		printf_mutex("is eating.", philo);
		philo->last_meal = timer();
		ft_usleep(philo->data->time_eat);
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		printf_mutex("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep);
		printf_mutex("is thinking.", philo);
	}
	pthread_exit(NULL);
}

void	close_and_clean(t_philos *philo)
{
	unsigned int	i;

	i = -1;
	while (++i < philo->data->n_philos)
		pthread_join(philo[i].thread, NULL);
	// pthread_join(philo->data->starvation, NULL);
	i = -1;
	while (++i < philo->data->n_philos)
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
	// if (data->n_philos == 1)
	// {
	// 	printf("Philo 1 is thinking.\n");
	// 	usleep(data->time_dead);
	// 	printf("Philo 1 is dead.\n");
	// 	ft_multiple_free(2, data->ends, data->stop);
	// 	exit(EXIT_SUCCESS);
	// }//Prevenir si filosofos == 1 esperar al timedead, intentar hacerlo automatico y debe ser un hilo
	philo = malloc(data->n_philos * sizeof(t_philos));
	if (!philo)
		ft_error("Error allocating memory.", 2, data->ends, data->stop);
	while (++i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = timer();
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].fork_r, NULL))
			ft_error("Error creating thread", 1, philo);
		if (i != 0)
			philo[i].fork_l = &philo[i - 1].fork_r;
	}
	philo[0].fork_l = &philo[i - 1].fork_r;
	i = -1;
	data->time_start = timer();
	// if (pthread_create(&data->starvation, NULL, check_starvation, philo))
	// 	ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
	while (++i < data->n_philos)
	{
		if (philo[i].id % 2 == 1)
			if (pthread_create(&philo[i].thread, NULL, philo_right_handed, &philo[i]))
				ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
		if (philo[i].id % 2 == 0)
			if (pthread_create(&philo[i].thread, NULL, philo_left_handed, &philo[i]))
				ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
	}
	return(philo);
}

// void	ft_leaks(void)
// {
// 	system("leaks -q philosophers");
// }

int	main(int narg, char **argv)
{
	t_data		data;
	t_philos	*philos;

	// atexit(ft_leaks);
	data = parse_data(narg, argv);
	philos = philo_born(&data);
	close_and_clean(philos);
	return (0);
}
