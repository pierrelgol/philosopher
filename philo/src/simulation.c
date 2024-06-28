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

static bool	simulation_dispatch_one(t_philo_container *const self)
{
	self->time_begin = time_ms();
	printf("%ld 1 has taken a fork\n", time_ms() - self->time_begin);
	usleep(self->time_to_die * 1000);
	printf("%ld 1 died\n", time_ms() - self->time_begin);
	philo_container_destroy(self);
	exit(EXIT_SUCCESS);
	return (true);
}

static bool	simulation_dispatch_many(t_philo_container *const self)
{
	int64_t	i;

	if (pthread_create(&self->supervisor, NULL, supervisor_sync, self))
		return (false);
	i = 0;
	while (i < self->philo_total)
	{
		if (pthread_create(&self->tid[i], NULL, simulation_sync_wait,
				&self->philosopers[i]))
			return (false);
		++i;
	}
	pthread_mutex_lock(&self->lock);
	self->philo_count = self->philo_total;
	pthread_mutex_unlock(&self->lock);
	pthread_join(self->supervisor, NULL);
	i = 0;
	while (i < self->philo_total)
	{
		pthread_join(self->tid[i], NULL);
		++i;
	}
	return (true);
}

bool	simulation_init(t_philo_container *const self)
{
	if (self->philo_total == 1)
		return (simulation_dispatch_one(self));
	else
		return (simulation_dispatch_many(self));
	return (true);
}

void	*simulation_sync_wait(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	while (true)
	{
		pthread_mutex_lock(&self->parent->lock);
		if (self->parent->is_synced)
		{
			pthread_mutex_unlock(&self->parent->lock);
			pthread_mutex_lock(&self->parent->time);
			self->time_to_die = self->parent->time_begin
				+ self->parent->time_to_die;
			self->time_last_meal = time_ms();
			pthread_mutex_unlock(&self->parent->time);
			break ;
		}
		pthread_mutex_unlock(&self->parent->lock);
		usleep(100);
	}
	simulation_start(arg);
	return (NULL);
}

void	*simulation_start(void *arg)
{
	t_philo	*self;
	bool	cond;

	self = (t_philo *)arg;
	cond = 0;
	while (true)
	{
		philo_eat(arg);
		if (philo_should_stop(self, &cond))
			break ;
		philo_sleep(arg);
		if (philo_should_stop(self, &cond))
			break ;
		philo_think(arg);
		if (philo_should_stop(self, &cond))
			break ;
	}
	return (NULL);
}
