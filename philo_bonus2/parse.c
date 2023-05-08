/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:32:09 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/08 22:06:40 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi_mod(const char *str)
{
	long	number;
	int		i;

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
	if (number > 2147483647)
		ft_error("Values ​​must be in the range of int.", 0);
	return (number);
}

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

void	parse_data(int narg, char **argv, t_data *data)
{
	data->ends = 0;
	data->n_philos = ft_atoi_mod(argv[1]);
	data->time_dead = ft_atoi_mod(argv[2]);
	data->time_eat = ft_atoi_mod(argv[3]);
	data->time_sleep = ft_atoi_mod(argv[4]);
	if (narg == 6)
	{
		data->ends = 1;
		data->n_eats = ft_atoi_mod(argv[5]);
	}
	if (data->n_philos > 200)
		ft_error("The maximum number of philosophers is 200.", 0);
	if (data->n_philos == 0)
		ft_error("There is no philosopher.", 0);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philos);
	data->talk = sem_open("/talk", O_CREAT, 0644, 1);
	data->died = sem_open("/talk", O_CREAT, 0644, 0);
	if (data->forks == SEM_FAILED || data->talk == SEM_FAILED)
		ft_error("Error creating semaphore.", 0);
	data->time_start = timer();
}

void	parse_philos(t_philos philo[200], t_data *data, int i)
{
	while (++i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].n_eats = 0;
		if (data->ends == 1)
			philo[i].n_eats = data->n_eats;
		philo[i].last_meal = timer();
		philo[i].data = *(data);
		philo[i].eat = sem_open("/n_meals", O_CREAT, 0644, 0);
		if (philo->eat == SEM_FAILED)
			ft_error("Error creating semaphore.", 0);
	}
}

void	parse(int narg, char **argv, t_data *data, t_philos philo[200])
{
	check_args(narg, argv);
	parse_data(narg, argv, data);
	parse_philos(philo, data, -1);
}
