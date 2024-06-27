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
	t_philo				*self;
	t_philo_container	*parent;

	self = (t_philo *)arg;
	parent = self->parent;
	if (self->id % 2 == 1)
	{
		pthread_mutex_lock(self->right_fork);
		report(&parent->stdout, parent->time_begin, self->id, TAKING_FORKS);
		pthread_mutex_lock(self->left_fork);
		report(&parent->stdout, parent->time_begin, self->id, TAKING_FORKS);
	}
	else
	{
		pthread_mutex_lock(self->left_fork);
		report(&parent->stdout, parent->time_begin, self->id, TAKING_FORKS);
		pthread_mutex_lock(self->right_fork);
		report(&parent->stdout, parent->time_begin, self->id, TAKING_FORKS);
	}
	return (NULL);
}

void	*philo_put_fork(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	if (self->id % 2 == 1)
	{
		pthread_mutex_unlock(self->left_fork);
		pthread_mutex_unlock(self->right_fork);
	}
	else
	{
		pthread_mutex_unlock(self->right_fork);
		pthread_mutex_unlock(self->left_fork);
	}
	return (NULL);
}

void	*philo_eat(void *arg)
{
	t_philo				*self;
	t_philo_container	*parent;

	self = (t_philo *)arg;
	parent = self->parent;
	philo_get_fork(self);
	pthread_mutex_lock(&parent->lock);
	self->is_eating = true;
	report(&parent->stdout, parent->time_begin, self->id, EATING);
	self->time_last_meal = gettime_since_ms(parent->time_begin);
	self->time_to_die = parent->time_to_die + self->time_last_meal;
	pthread_mutex_unlock(&parent->lock);
	micro_sleep(self->time_to_eat);
	philo_put_fork(self);
	pthread_mutex_lock(&parent->lock);
	self->is_eating = false;
	pthread_mutex_unlock(&parent->lock);
	return (NULL);
}

void	*philo_sleep(void *arg)
{
	t_philo				*self;
	t_philo_container	*parent;

	self = (t_philo *)arg;
	parent = self->parent;
	pthread_mutex_lock(&parent->lock);
	report(&parent->stdout, parent->time_begin, self->id, SLEEPING);
	pthread_mutex_unlock(&parent->lock);
	micro_sleep(self->time_to_sleep);
	return (NULL);
}

void	*philo_think(void *arg)
{
	t_philo				*self;
	t_philo_container	*parent;

	self = (t_philo *)arg;
	parent = self->parent;
	pthread_mutex_lock(&parent->lock);
	report(&parent->stdout, parent->time_begin, self->id, THINKING);
	pthread_mutex_unlock(&parent->lock);
	micro_sleep(self->time_to_think / 2);
	return (NULL);
}
