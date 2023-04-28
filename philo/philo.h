/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:50:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/04/28 14:31:55 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <pthread.h>

# define INSTRUCTIONS ("Invalid Number of Arguments, these are the variables:\n \
◦[1] Number of philosophers: The number of philosophers and also the number of forks. \n \
◦[2] Time to die (milliseconds): If a philosopher didn’t start eating time_to_die \
milliseconds since the beginning of their last meal or the beginning of the simulation, they die. \n \
◦[3] Time to eat (milliseconds): The time it takes for a philosopher to eat. \
During that time, they will need to hold two forks. \n \
◦[4] Time to sleep (milliseconds): The time a philosopher will spend sleeping. \n \
◦[5] Number of times each philosopher must eat (OPTIONAL): If all \
philosophers have eaten at least this number of \
times, the simulation stops. If not specified, the simulation stops when a \
philosopher dies.")

typedef struct	rules
{
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