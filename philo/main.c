/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/02 19:20:49 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Checks if a philosopher has starved to death or if all
 * philosophers have eaten their required number of meals.
 * 
 * @param param pointer to the philosopher
 *
 * @return NULL
 */
void	*check_hunger(void *param)
{
	unsigned int	i;
	t_philos		*philo;
	useconds_t		time;
	int				flag;

	philo = (t_philos *)param;
	i = -1;
	while (*(philo->data->stop))
	{
		i = -1;
		flag = 0;
		ft_usleep(1);
		while (++i < philo->data->n_philos)
		{
			pthread_mutex_lock(&philo[i].mutex_eat);
			time = timer() - philo[i].last_meal;
			pthread_mutex_lock(&philo->data->stop_mutex);
			if (time > philo->data->time_dead)
			{
				*(philo->data->stop) = 0;
				pthread_mutex_unlock(&philo->data->stop_mutex);
				pthread_mutex_unlock(&philo[i].mutex_eat);
				pthread_mutex_lock(&philo->data->talk);
				printf("(%ld) Philo %d is dead.\n", timer() - philo->data->time_start, philo->id);
				pthread_mutex_unlock(&philo->data->talk);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->data->stop_mutex);
			if (*(philo->data->ends) == 1 && philo[i].n_meals < philo->data->n_eats)
				flag = 1;
			pthread_mutex_unlock(&philo[i].mutex_eat);
		}
		if (*(philo->data->ends) == 1 && flag == 0)
		{
			*(philo->data->stop) = 0;
			pthread_mutex_lock(&philo->data->talk);
			printf("All the philosophers have eaten!\n");
			pthread_mutex_unlock(&philo->data->talk);
			return (NULL);
		}
	}
	return (NULL);
}

/**
 * Basic checks if the command-line arguments are valid
 * @param narg: number of arguments
 * @param argv: array of arguments
 *
 */
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

/**
 * Parses command-line arguments and initializes a `t_data` struct.
 *
 * @brief   Parses command-line arguments and initializes a `t_data` struct.
 * @param   narg    The number of command-line arguments.
 * @param   argv    The command-line arguments.
 * @return  A `t_data` struct with the parsed values.
 */
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

/**
 * The right-handed philosopher
 * @param arg: a pointer to the philosopher
 *
 * @return NULL
 */
void	*philo_right_handed(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (*(philo->data->stop) == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
		pthread_mutex_lock(&philo->mutex_eat);
		printf_mutex("is eating.", philo);
		philo->last_meal = timer();
		philo->n_meals++;
		pthread_mutex_unlock(&philo->mutex_eat);
		ft_usleep(philo->data->time_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
		printf_mutex("is sleeping.", philo);
		ft_usleep(philo->data->time_sleep);
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_exit(NULL);
}

/**
 * The left-handed philosopher
 * @param arg: a pointer to the philosopher
 *
 * @return NULL
 */
void	*philo_left_handed(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (*(philo->data->stop) == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
		pthread_mutex_lock(&philo->mutex_eat);
		printf_mutex("is eating.", philo);
		philo->last_meal = timer();
		philo->n_meals++;
		pthread_mutex_unlock(&philo->mutex_eat);
		ft_usleep(philo->data->time_eat);
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		printf_mutex("is sleeping.", philo);
		ft_usleep(philo->data->time_sleep);
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_exit(NULL);
}

/**
*
* Creates an array of philosophers and initializes their variables and trheads.
*
*@param data: a pointer to the main data structure
*
* @return A pointer to the array of philosophers
*/
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
		philo[i].n_meals = 0;
		philo[i].last_meal = timer();
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].fork_r, NULL))
			ft_error("Error creating mutex.", 3, philo, data->stop, data->ends);
		if (pthread_mutex_init(&philo[i].mutex_eat, NULL))
			ft_error("Error creating mutex.", 3, philo, data->stop, data->ends);
		if (i != 0)
			philo[i].fork_l = &philo[i - 1].fork_r;
	}
	if (pthread_mutex_init(&philo->data->talk, NULL))
		ft_error("Error creating mutex.", 3, philo, data->stop, data->ends);
	if (pthread_mutex_init(&philo->data->stop_mutex, NULL))
		ft_error("Error creating mutex.", 3, philo, data->stop, data->ends);
	philo[0].fork_l = &philo[i - 1].fork_r;
	i = -1;
	data->time_start = timer();
	while (++i < data->n_philos)
	{
		if (philo[i].id % 2 == 1)
			if (pthread_create(&philo[i].thread, NULL, philo_right_handed, &philo[i]))
				ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
		if (philo[i].id % 2 == 0)
			if (pthread_create(&philo[i].thread, NULL, philo_left_handed, &philo[i]))
				ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
	}
	if (pthread_create(&data->starvation, NULL, check_hunger, philo))
		ft_error("Error creating thread.", 3, philo, data->stop, data->ends);
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
	printf("%s", (char *)&(HEADER));
	data = parse_data(narg, argv);
	philos = philo_born(&data);
	close_and_clean(philos);
	return (0);
}
