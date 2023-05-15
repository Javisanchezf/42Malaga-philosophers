/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:50:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/10 13:34:51 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define HEADER ("\n\
\033[36;1m██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\n\
██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\n\
██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\n\
██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\n\
██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\n\
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n\
 \n\
\033[37;1m                                           By                                          \n\
\033[1m                                    --- javiersa ---                                   \n\
\n\033[0m")

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define INSTRUCTIONS ("Invalid number of arguments, variables:\n \
◦[1] Number of philosophers \n \
◦[2] Time to die (milliseconds) \n \
◦[3] Time to eat (milliseconds)\n \
◦[4] Time to sleep (milliseconds)\n \
◦[5] Number of times each philosopher must eat (OPTIONAL)")

typedef struct data
{
	int				n_philos;
	int				time_dead;
	int				time_eat;
	int				time_sleep;
	int				n_eats;
	short int		ends;
	short int		stop;
	long			time_start;
	pthread_mutex_t	talk;
	pthread_mutex_t	stop_mutex;
	pthread_t		starvation;
}				t_data;

typedef struct philo
{
	int					id;
	int					n_meals;
	int					last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		mutex_eat;
	t_data				*data;
}				t_philos;

int		parse(int narg, char **argv, t_data *data, t_philos *philo);
void	*philo_thread(void *arg);
void	*check_thread(void	*param);
void	printf_mutex(char *str, t_philos *philo);
int		timer(void);
void	ft_usleep(int ms, t_philos *philo);
int		ft_error(char *s);
void	*exception(void *arg);

#endif