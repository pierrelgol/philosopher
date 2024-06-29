/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:23:56 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/29 10:23:56 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int64_t	string_length(const char *const str)
{
	int64_t	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length])
		++length;
	return (length);
}

void	error(const char *const msg)
{
	write(2, msg, string_length(msg));
}

void	error_and_die(const char *const msg)
{
	error(msg);
	exit(EXIT_FAILURE);
}

void	error_cleanup_and_die(t_philo_container *const self,
		const char *const msg)
{
	philo_container_destroy(self);
	error_and_die(msg);
}
