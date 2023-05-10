/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/10 12:55:36 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *s)
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
	return (1);
}

int	main(int narg, char **argv)
{
	t_data			data;
	t_philos		philo[242];
	int	i;

	if (parse(narg, argv, &data, philo) != 0)
		return (1);
	i = -1;
	data.time_start = timer();
	while (++i < data.n_philos)
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
			return (ft_error("Error creating mutex."));
	if (pthread_create(&data.starvation, NULL, check_hunger, philo))
		return (ft_error("Error creating mutex."));
	close_and_clean(philo);
	return (0);
}
