/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:25:24 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/28 18:25:25 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	philo_maybe_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->parent->died);
	if (philo->parent->stop == true)
	{
		pthread_mutex_unlock(&philo->parent->died);
		return (true);
	}
	pthread_mutex_unlock(&philo->parent->died);
	return (false);
}

bool	philo_paranoid_sleep(t_philo *self, int64_t time)
{
	int32_t	total;

	total = time_ms() + time;
	while (time_ms() < total)
	{
		usleep(time);
		pthread_mutex_lock(&self->parent->died);
		if (self->parent->stop == true)
		{
			pthread_mutex_unlock(&self->parent->died);
			break ;
		}
		pthread_mutex_unlock(&self->parent->died);
	}
	return (true);
}

bool	philo_should_stop(t_philo *philo, bool *cond)
{
	pthread_mutex_lock(&philo->parent->died);
	if (philo->parent->stop == true)
	{
		*cond = true;
		pthread_mutex_unlock(&philo->parent->died);
		return (true);
	}
	pthread_mutex_unlock(&philo->parent->died);
	return (false);
}

int64_t	time_diff(int64_t time)
{
	return (time_ms() - time);
}
