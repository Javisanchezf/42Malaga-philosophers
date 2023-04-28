/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/04/28 21:45:56 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		ft_error("Error", 0);
	data.stop = malloc (1 * sizeof(short int));
	if (!data.ends)
		ft_error("Error", 1, data.ends);
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

void *philo_do(void *arg)
{
    t_philos *philo = (t_philos *)arg;
    t_data *data = philo->data;
    
    printf("Philosopher %d data:\n", philo->id);
    printf("n_philos: %u\n", data->n_philos);
    printf("time_dead: %u\n", data->time_dead);
    printf("time_eat: %u\n", data->time_eat);
    printf("time_sleep: %u\n", data->time_sleep);
    printf("n_eats: %u\n", data->n_eats);
    printf("ends: %p\n", (void *)data->ends);
    printf("stop: %p\n", (void *)data->stop);
    printf("ends: %hd\n", *(data->ends));
    printf("stop: %hd\n", *(data->stop));
    
    pthread_exit(NULL);
}



t_philos	*philo_born(t_data *data)
{
	unsigned int	i;
	t_philos	*philo;

	i = -1;
	//Prevenir si filosofos == 1 esperar al timedead
	philo = malloc(data->n_philos * sizeof(t_philos));
	if (!philo)
		ft_error("Error", 2, data->ends, data->stop);
	while(++i < data->n_philos)
	{
		philo[i].id = i;
		philo[i].data = data;
		// philo[i].data->stop = data->stop;
		// philo[i].data->ends = data->ends;
		//printf("Data philo Nº%u: data.n_philos: %u, data.time_dead: %u,data.time_eat:%u ,data.time_sleep: %u\n",i, philo[i].data.n_philos, philo[i].data.time_dead, philo[i].data.time_eat, philo[i].data.time_sleep);
		printf("Data philo Nº%u: data.n_philos: %p, data.time_dead: %u,data.time_eat:%u ,data.time_sleep: %u\n",i, &philo[i].data->n_philos, philo[i].data->time_dead, philo[i].data->time_eat, philo[i].data->time_sleep);
		if (pthread_create(&philo[i].thread, NULL, philo_do, &philo[i]))
			ft_error("Error creating thread", 1, philo);
		if (i != 0)
			philo[i].fork_l = &philo[i - 1].fork_r;
	}
	philo[0].fork_l = &philo[i].fork_r;
	for (i = 0; i < philo->data->n_philos; i++) {
    pthread_join(philo[i].thread, NULL);
}
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
	(void)philos;
	*(data.stop) = 1;
	ft_multiple_free(3, philos, data.stop, data.ends);
	return(0);
}
