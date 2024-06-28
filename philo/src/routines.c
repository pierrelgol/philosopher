/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:01:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 17:01:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_get_fork(void *arg)
{
	t_philo	*self;

	self = (void *)arg;
	if (philo_maybe_stop(self))
		return (NULL);
	if (self->id % 2 == 1)
	{
		pthread_mutex_lock(self->left_fork);
		report(&self->parent->write, self->parent->time_begin, self->id,
			TAKING_FORKS);
		pthread_mutex_lock(self->right_fork);
		report(&self->parent->write, self->parent->time_begin, self->id,
			TAKING_FORKS);
	}
	else
	{
		pthread_mutex_lock(self->right_fork);
		report(&self->parent->write, self->parent->time_begin, self->id,
			TAKING_FORKS);
		pthread_mutex_lock(self->left_fork);
		report(&self->parent->write, self->parent->time_begin, self->id,
			TAKING_FORKS);
	}
	return (NULL);
}

void	*philo_put_fork(void *arg)
{
	t_philo	*self;

	self = (void *)arg;
	if (philo_maybe_stop(self))
		return (NULL);
	if (self->id % 2 == 1)
	{
		pthread_mutex_unlock(self->right_fork);
		pthread_mutex_unlock(self->left_fork);
	}
	else
	{
		pthread_mutex_unlock(self->left_fork);
		pthread_mutex_unlock(self->right_fork);
	}
	return (NULL);
}

void	*philo_eat(void *arg)
{
	t_philo	*self;

	self = (void *)arg;
	pthread_mutex_lock(&self->eat_lock);
	philo_get_fork(self);
	self->meal_count += 1;
	self->time_last_meal = time_ms();
	self->time_to_die = self->parent->time_begin + time_ms();
	report(&self->parent->write, self->parent->time_begin, self->id, EATING);
	philo_paranoid_sleep(self, self->time_to_eat * 1000);
	philo_put_fork(self);
	pthread_mutex_unlock(&self->eat_lock);
	return (NULL);
}

void	*philo_sleep(void *arg)
{
	t_philo	*self;

	self = (void *)arg;
	pthread_mutex_lock(&self->parent->lock);
	if (!philo_maybe_stop(self))
	{
		report(&self->parent->write, self->parent->time_begin, self->id,
			SLEEPING);
		philo_paranoid_sleep(self, self->time_to_sleep * 1000);
	}
	pthread_mutex_unlock(&self->parent->lock);
	return (NULL);
}

void	*philo_think(void *arg)
{
	t_philo	*self;

	self = (void *)arg;
	pthread_mutex_lock(&self->parent->lock);
	if (!philo_maybe_stop(self))
	{
		report(&self->parent->write, self->parent->time_begin, self->id,
			THINKING);
		philo_paranoid_sleep(self, self->time_to_think * 1000);
	}
	pthread_mutex_unlock(&self->parent->lock);
	return (NULL);
}
