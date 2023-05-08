/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/08 21:56:46 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int narg, char **argv)
{
	t_data		data;
	t_philos	philo[200];

	printf("%s", (char *)&(HEADER));
	parse(narg, argv, &data, philo);
	// philo_born(philo, &data, -1);
	// if (pthread_create(&data.starvation, NULL, check_hunger, philo))
	// 	ft_error("Error creating mutex.", 0);
	// close_and_clean(philo);
	return (0);
}
