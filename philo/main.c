/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:58:04 by javiersa          #+#    #+#             */
/*   Updated: 2023/04/28 14:36:26 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	extract_data(int narg, char **argv, short int *ends, short int *dead)
{
	t_rules rules;

	*ends = 0;
	*dead = 0;
	rules.time_dead = ft_atoi(argv[2]);
	rules.time_eat = ft_atoi(argv[3]);
	rules.time_sleep = ft_atoi(argv[4]);
	if (narg == 6)
	{
		*ends = 1;
		rules.n_eats = ft_atoi(argv[5]);
	}
	rules.stop = dead; 
	rules.ends = ends;
	return(rules); 
}

void	philo_born(int n_philos, t_rules rules)
{
	printf("Nº philos: %d\n Ends: %d",n_philos, *rules.ends);
}

int	main(int narg, char **argv)
{
	short int	ends;
	short int	dead;

	if (narg < 5 || narg > 6)
		ft_error(INSTRUCTIONS, 0);
	philo_born(ft_atoi(argv[1]), extract_data(narg, argv, &ends, &dead));
	
	(void)argv;
}
