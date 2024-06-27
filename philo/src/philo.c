/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:12:58 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 14:12:58 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	philo_container_init_mutexes(t_philo_container *const self,
		const uint64_t total)
{
	uint64_t	i;

	if (pthread_mutex_init(&self->lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&self->stdout, NULL) != 0)
		return (false);
	i = 0;
	while (i < total)
	{
		if (pthread_mutex_init(&self->forks[i], NULL) != 0)
			return (false);
		++i;
	}
	return (true);
}

bool	philo_container_init_philo(t_philo_container *const self,
		const uint64_t total)
{
	t_philo		*philo;
	uint64_t	i;

	i = 0;
	philo = self->philosopers;
	while (i < total)
	{
		philo[i].parent = self;
		philo[i].left_fork = &self->forks[i];
		philo[i].right_fork = &self->forks[(i + 1) % total];
		philo[i].tid = &self->tid[i];
		philo[i].id = i + 1;
		philo[i].time_to_die = self->time_to_die;
		philo[i].time_to_sleep = self->time_to_sleep;
		philo[i].time_to_eat = self->time_to_eat;
		philo[i].time_to_think = self->time_to_think;
		philo[i].time_last_meal = 0;
		philo[i].is_eating = false;
		++i;
	}
	return (true);
}

bool	philo_container_alloc(t_philo_container *const self,
		const uint64_t total)
{
	self->philosopers = memory_alloc(total * sizeof(t_philo));
	self->forks = memory_alloc(total * sizeof(pthread_mutex_t));
	self->tid = memory_alloc(total * sizeof(pthread_t));
	if (!self->philosopers || !self->forks || !self->tid)
		return (false);
	return (true);
}

t_philo_container	*philo_container_create(const t_philo_config *const config)
{
	t_philo_container	self;

	self = (t_philo_container *)memory_alloc(sizeof(*self));
	if (!self)
		return (NULL);
	self->philo_total = config->number_of_philosophers;
	self->time_to_die = config->time_to_die;
	self->time_to_eat = config->time_to_eat;
	self->time_to_sleep = config->time_to_sleep;
	self->time_to_think = config->time_to_think;
	self->meals_total = config->number_of_meals;
	self->meals_count = 0;
	self->philo_count = 0;
	if (!philo_container_alloc(self, self->philo_total))
		return (philo_container_destroy(self));
	if (!philo_container_init_mutexes(self, self->philo_total))
		return (philo_container_destroy(self));
	if (!philo_container_init_philo(self, self->philo_total))
		return (philo_container_destroy(self));
	return (self);
}

t_philo_container	*philo_container_destroy(t_philo_container *const self)
{
	int64_t	i;

	if (self)
	{
		i = 0;
		if (self->forks)
		{
			while (i < self->philo_total)
				pthread_mutex_destroy(&self->forks[i++]);
			memory_dealloc(self->forks);
		}
		if (self->philosopers)
			memory_dealloc(self->philosopers);
		if (self->tid)
			memory_dealloc(self->tid);
		pthread_mutex_destroy(&self->lock);
		pthread_mutex_destroy(&self->stdout);
		memory_dealloc(self);
	}
	return (NULL);
}
