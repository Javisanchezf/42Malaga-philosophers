/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/03 19:58:39 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data.stop = malloc (1 * sizeof(short int));
	if (!data.stop)
		ft_error("Error allocating memory.", 0);
	data.ends = 0;
	*(data.stop) = 1;
	data.n_philos = ft_atoui(argv[1]);
	data.time_dead = ft_atoui(argv[2]);
	data.time_eat = ft_atoui(argv[3]);
	data.time_sleep = ft_atoui(argv[4]);
	if (narg == 6)
	{
		data.ends = 1;
		data.n_eats = ft_atoui(argv[5]);
	}
	return (data);
}

int	main(int narg, char **argv)
{
	t_data		data;
	t_philos	*philo;

	printf("%s", (char *)&(HEADER));
	data = parse_data(narg, argv);
	if (data.n_philos == 0)
		ft_error("There is no philosopher.", 1, data.stop);
	philo = malloc(data.n_philos * sizeof(t_philos));
	if (!philo)
		ft_error("Error allocating memory.", 1, data.stop);
	philo_born(philo, &data, -1);
	if (pthread_create(&data.starvation, NULL, check_hunger, philo))
		ft_error("Error creating mutex.", 2, philo, data.stop);
	close_and_clean(philo);
	return (0);
}
