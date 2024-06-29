/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:30:44 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/29 10:30:45 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_container_init(t_philo_container *const self,
		const t_philo_config *const cfg, const uint64_t number_of_philosopher)
{
	uint64_t	i;

	if (!self || !cfg || !number_of_philosopher)
		return (false);
	i = 0;
	while (i < number_of_philosopher)
	{
		self->philos[i].id = i + 1;
		self->philos[i].left_fork = &self->forks[i];
		self->philos[i].right_fork = &self->forks[(i + 1) % MAX_PHILO];
		self->philos[i].parent = self;
		self->philos[i].thread = &self->threads[i];
		self->philos[i].meal_count = 0;
		if (pthread_mutex_init(&self->philos[i].eating_lock, NULL))
			error_and_die("error : failed to initialize eating_lock\n");
		++i;
	}
	return (true);
}

bool	philo_container_create(t_philo_container *const self,
		const t_philo_config *const cfg)
{
	int64_t	i;

	if (!self || !cfg)
		return (false);
	self->philo_total = cfg->number_of_philosopher;
	self->meals_total = cfg->number_of_meals;
	self->time_to_die = cfg->time_to_die;
	self->time_to_eat = cfg->time_to_eat;
	self->time_to_sleep = cfg->time_to_sleep;
	self->time_to_think = cfg->time_to_think;
	i = 0;
	while (i < self->philo_total)
	{
		if (pthread_mutex_init(&self->forks[i++], NULL))
			error_and_die("error : failed to initialize forks\n");
	}
	if (pthread_mutex_init(&self->time_lock, NULL))
		error_and_die("error : failed to initialize forks\n");
	if (pthread_mutex_init(&self->died_lock, NULL))
		error_and_die("error : failed to initialize forks\n");
	if (pthread_mutex_init(&self->write_lock, NULL))
		error_and_die("error : failed to initialize forks\n");
	return (philo_container_init(self, cfg, cfg->number_of_philosopher));
}

bool	philo_container_destroy(t_philo_container *const self)
{
	int64_t	i;

	if (!self)
		return (false);
	i = 0;
	while (i < self->philo_total)
	{
		pthread_mutex_destroy(&self->forks[i]);
		pthread_mutex_destroy(&self->philos[i].eating_lock);
		++i;
	}
	pthread_mutex_destroy(&self->died_lock);
	pthread_mutex_destroy(&self->write_lock);
	pthread_mutex_destroy(&self->time_lock);
	return (true);
}
