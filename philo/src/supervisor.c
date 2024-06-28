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

bool	philo_is_full(t_philo *self)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&self->eat_lock);
	if (self->meal_count >= self->parent->meals_total)
		result = true;
	pthread_mutex_unlock(&self->eat_lock);
	return (result);
}

bool	philo_is_dead(t_philo *self)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&self->eat_lock);
	if ((self->time_last_meal - time_ms()) > self->parent->time_to_die)
	{
		report(&self->parent->write, self->parent->time_begin, self->id, DEAD);
		pthread_mutex_lock(&self->parent->died);
		self->parent->stop = true;
		pthread_mutex_unlock(&self->parent->died);
		result = true;
	}
	pthread_mutex_unlock(&self->eat_lock);
	return (result);
}

void	*supervisor_monitor(void *arg)
{
	t_philo_container	*self;
	int64_t				i;
	bool				all_full;

	self = (t_philo_container *)arg;
	while (true)
	{
		i = 0;
		all_full = true;
		while (i < self->philo_count)
		{
			if (philo_is_dead(&self->philosopers[i]))
			{
				report(&self->write, self->time_begin, self->philosopers[i].id,
					DEAD);
				return (NULL);
			}
			if (!philo_is_full(&self->philosopers[i]))
				all_full = false;
		}
		if (all_full)
		{
			report(&self->write, self->time_begin, 0, DEAD_OR_FULL);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	*supervisor_sync(void *arg)
{
	t_philo_container	*self;

	self = (t_philo_container *)arg;
	pthread_mutex_lock(&self->lock);
	while (self->philo_count < self->philo_total)
	{
		pthread_mutex_unlock(&self->lock);
		usleep(100);
		pthread_mutex_lock(&self->lock);
	}
	self->is_synced = true;
	pthread_mutex_lock(&self->time);
	self->time_begin = time_ms();
	pthread_mutex_unlock(&self->time);
	pthread_mutex_unlock(&self->lock);
	supervisor_monitor(self);
	return (NULL);
}
