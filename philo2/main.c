/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/10 12:28:34 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *s)
{
	int	i;

	i = 0;
	write (2, "❌ \033[31;1m", 12);
	while (s[i])
	{
		write (2, &s[i], sizeof(char));
		i++;
	}
	write (2, "\n\033[0m", 6);
	exit(EXIT_FAILURE);
}

int	main(int narg, char **argv)
{
	t_data			data;
	t_philos		philo[200];
	unsigned int	i;

	parse(narg, argv, &data, philo);
	i = -1;
	data.time_start = timer();
	while (++i < data.n_philos)
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
			ft_error("Error creating mutex.");
	if (pthread_create(&data.starvation, NULL, check_hunger, philo))
		ft_error("Error creating mutex.");
	close_and_clean(philo);
	return (0);
}
