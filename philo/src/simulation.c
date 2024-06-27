/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:10:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 16:10:34 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	simulation_init(t_philo_container *const self)
{
	int64_t	i;

	if (pthread_create(&self->supervisor, NULL, supervisor_sync, self) != 0)
		return (false);
	pthread_detach(self->supervisor);
	i = 0;
	while (i < self->philo_total)
	{
		if (pthread_create(&self->tid[i], NULL, simulation_sync_wait,
				(void *)&self->philosopers[i]) != 0)
			return (false);
		++i;
	}
	pthread_mutex_lock(&self->lock);
	self->philo_count = self->philo_total;
	pthread_mutex_unlock(&self->lock);
	i = 0;
	while (i < self->philo_total)
	{
		if (pthread_join(self->tid[i], NULL) != 0)
			return (false);
		++i;
	}
	philo_container_destroy(self);
	return (true);
}

void	*simulation_sync_wait(void *arg)
{
	t_philo				*self;
	t_philo_container	*parent;

	self = (t_philo *)arg;
	parent = self->parent;
	while (true)
	{
		pthread_mutex_lock(&parent->lock);
		if (parent->is_synced)
		{
			self->time_to_die = parent->time_to_die + timestamp();
			pthread_mutex_unlock(&parent->lock);
			return (simulation_sync_start(arg));
		}
		pthread_mutex_unlock(&parent->lock);
	}
	return (NULL);
}

void	*simulation_sync_start(void *arg)
{
	t_philo				*self;
	t_philo_container	*parent;

	self = (t_philo *)arg;
	parent = self->parent;
	while (true)
	{
		pthread_mutex_lock(&parent->lock);
		if (parent->stop)
		{
			pthread_mutex_unlock(&parent->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&parent->lock);
		philo_eat(self);
		philo_sleep(self);
		philo_think(self);
	}
	return (NULL);
}
