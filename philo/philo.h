/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:50:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/01 19:20:26 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

# define INSTRUCTIONS ("Invalid number of arguments, variables:\n \
◦[1] Number of philosophers \n \
◦[2] Time to die (milliseconds) \n \
◦[3] Time to eat (milliseconds)\n \
◦[4] Time to sleep (milliseconds)\n \
◦[5] Number of times each philosopher must eat (OPTIONAL)")

typedef struct	data
{
	unsigned int	n_philos;
	unsigned int	time_dead;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	n_eats;
	short int		*ends;
	short int		*stop; //Cuando finalice *stop = 0;
	long			time_start;
	pthread_mutex_t	talk;
	pthread_t		starvation;
}				t_data;

typedef struct	philo
{
	unsigned int		id;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	t_data				*data;
}				t_philos;


void	ft_error(char *prompt, int num_args, ...);
unsigned int		ft_atoui(const char *str);
void	ft_multiple_free(int num_args, ...);

#endif