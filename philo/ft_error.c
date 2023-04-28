/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:41:26 by javiersa          #+#    #+#             */
/*   Updated: 2023/04/28 12:45:26 by javiersa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_and_null(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (0);
}

// void	ft_multiple_free(int num_args, ...)
// {
// 	va_list	args;
// 	void	*ptr;
// 	int		i;

// 	i = -1;
// 	va_start(args, num_args);
// 	while (++i < num_args)
// 	{
// 		ptr = va_arg(args, void *);
// 		ft_free_and_null((void **)&ptr);
// 	}
// 	va_end(args);
// }

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], sizeof(char));
		i++;
	}
}

void	ft_error(char *prompt, int num_args, ...)
{
	va_list	args;
	void	*ptr;
	int		i;

	i = -1;
	va_start(args, num_args);
	while (++i < num_args)
	{
		ptr = va_arg(args, void *);
		ft_free_and_null((void **)&ptr);
	}
	va_end(args);
	ft_putstr_fd("❌ \033[31;1m", 2);
	ft_putstr_fd(prompt, 2);
	ft_putstr_fd("\n\033[0m", 2);
	exit(EXIT_FAILURE);
}
