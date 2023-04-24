/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:50:19 by javiersa          #+#    #+#             */
/*   Updated: 2023/04/24 17:56:16 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>

typedef struct	rules
{
	int	n_philos;
	int	n_eat;
	int	time_dead;
	int	time_eat;
	int	time_sleep;
}				t_rules;

#endif