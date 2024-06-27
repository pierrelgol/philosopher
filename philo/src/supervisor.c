/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:23:52 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 16:23:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	supervisor_check_dead_philos(t_philo_container *const self,
		const uint64_t total)
{
	uint64_t	i;

	i = 0;
	while (i < total)
	{
		if ((gettime_since_ms(self->time_begin)
				- self->philosopers[i].time_last_meal) >= self->time_to_die
			&& !self->philosopers[i].is_eating)
		{
			report(&self->stdout, self->time_begin, self->philosopers[i].id,
				DEAD);
			self->stop = true;
			return (true);
		}
		++i;
	}
	return (false);
}

bool	supervisor_check_full_philos(t_philo_container *const self,
		const uint64_t total)
{
	uint64_t	i;

	i = 0;
	while (i < total)
	{
		if (self->philosopers[i].meal_count >= self->meals_total)
		{
			self->philosopers[i].stop = true;
			pthread_mutex_lock(&self->lock);
			self->philo_count -= 1;
			pthread_mutex_unlock(&self->lock);
			return (true);
		}
		++i;
	}
	return (false);
}

void	*supervisor_monitor(void *arg)
{
	t_philo_container	*self;

	self = (t_philo_container *)arg;
	while (true)
	{
		pthread_mutex_lock(&self->lock);
		if (supervisor_check_dead_philos(self, self->philo_total))
		{
			pthread_mutex_unlock(&self->lock);
			break ;
		}
		if (self->meals_total != -1 && supervisor_check_full_philos(self,
				self->philo_total))
		{
			pthread_mutex_unlock(&self->lock);
			break ;
		}
		pthread_mutex_unlock(&self->lock);
	}
	return (NULL);
}

void	*supervisor_sync(void *arg)
{
	t_philo_container	*self;

	self = (t_philo_container *)arg;
	while (true)
	{
		pthread_mutex_lock(&self->lock);
		if (self->philo_count == self->philo_total)
		{
			self->is_synced = true;
			self->time_begin = timestamp();
			pthread_mutex_unlock(&self->lock);
			break ;
		}
		pthread_mutex_unlock(&self->lock);
	}
	return (supervisor_monitor(self));
}
