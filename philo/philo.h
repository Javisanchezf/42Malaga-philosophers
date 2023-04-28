/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:50:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/04/28 15:12:38 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <pthread.h>

# define INSTRUCTIONS ("Invalid number of arguments, variables:\n \
◦[1] Number of philosophers \n \
◦[2] Time to die (milliseconds) \n \
◦[3] Time to eat (milliseconds)\n \
◦[4] Time to sleep (milliseconds)\n \
◦[5] Number of times each philosopher must eat (OPTIONAL)")

typedef struct	rules
{
	int		philo;
	int		time_dead;
	int		time_eat;
	int		time_sleep;
	int		n_eats;
	short int		*ends;
	short int		*stop;
}				t_rules;

void	ft_error(char *prompt, int num_args, ...);
int		ft_atoi(const char *str);

#endif