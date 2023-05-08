/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:50:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/05/08 22:02:46 by javiersa         ###   ########.fr       */
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
# include <stdarg.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define INSTRUCTIONS ("Invalid number of arguments, variables:\n \
◦[1] Number of philosophers \n \
◦[2] Time to die (milliseconds) \n \
◦[3] Time to eat (milliseconds)\n \
◦[4] Time to sleep (milliseconds)\n \
◦[5] Number of times each philosopher must eat (OPTIONAL)")

typedef struct data
{
	short int		n_philos;
	useconds_t		time_dead;
	useconds_t		time_eat;
	useconds_t		time_sleep;
	int				n_eats;
	short int		ends;
	long			time_start;
	sem_t			*forks;
	sem_t			*talk;
	sem_t			*died;
	pthread_t		starvation;
}				t_data;

typedef struct philo
{
	unsigned int		id;
	pid_t				pid;
	useconds_t			last_meal;
	pthread_t			thread;
	t_data				data;
	int					n_eats;
	sem_t				*eat;
}				t_philos;

void	parse(int narg, char **argv, t_data *data, t_philos philo[200]);
void	philo_born(t_philos *philo, t_data *data, int i);
/**
 * Displays an error message on the standard error output and exits the program
 * with an error code. Frees any pointer passed as a variable argument.
 *
 * @param prompt The error message to be displayed before exiting.
 * @param num_args The number of variable arguments to be passed to the function.
 * @param ... A variable number of pointers to be freed before exiting.
 * @return void
 */
void			ft_error(char *prompt, int num_args, ...);

/**
* @brief Frees multiple dynamically allocated memory blocks and sets the
* pointers to NULL.
* This function takes in a variable number of arguments representing memory
* blocks that need to be freed,
* and sets the corresponding pointers to NULL. It uses the
* ft_free_and_null function to properly free each block.
* @param num_args The number of arguments to be processed.
* @param ... A variable number of void pointers representing the memory
* blocks to be freed.
* @return void.
*/
void			ft_multiple_free(int num_args, ...);

/**
 * @brief Sleeps for a specified number of milliseconds
 * 
 * @param ms The number of milliseconds to sleep for
 * @param stop A pointer to a flag that controls whether to stop sleeping or not
 */
void			ft_usleep(useconds_t ms);

/**
 * @brief Joins all philosopher threads and cleans up memory
 * 
 * @param philo A pointer to the philosopher data
 */
void			close_and_clean(t_philos *philo);

/**
 * @brief Gets the current time in milliseconds
 * 
 * @return useconds_t The current time in milliseconds
 */
useconds_t		timer(void);

/**
 * @brief It is a thread that checks if any philosopher has starved 
 * or if all philosophers have eaten the minimum number of times.
 * 
 * @param param A pointer to the philosopher data.
 */
void			*check_hunger(void	*param);

#endif