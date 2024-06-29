/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:16:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/29 12:16:43 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_can_eat(t_philo *const self)
{
	pthread_mutex_lock(&self->parent->died_lock);
	if (self->parent->philo_died == true)
	{
		pthread_mutex_unlock(&self->parent->died_lock);
		return (false);
	}
	pthread_mutex_unlock(&self->parent->died_lock);
	return (true);
}

bool	philo_try_get_left_fork(t_philo *const self)
{
	if (!philo_can_eat(self))
		return (false);
	pthread_mutex_lock(self->left_fork);
	pthread_mutex_lock(&self->parent->write_lock);
	if (philo_can_eat(self))
		printf("%ld %ld has taken a fork\n", timestamp()
			- self->parent->time_begin, self->id);
	pthread_mutex_unlock(&self->parent->write_lock);
	return (true);
}

bool	philo_try_get_right_fork(t_philo *const self)
{
	if (!philo_can_eat(self))
	{
		pthread_mutex_unlock(self->left_fork);
		return (false);
	}
	pthread_mutex_lock(self->right_fork);
	pthread_mutex_lock(&self->parent->write_lock);
	if (philo_can_eat(self) && self->meal_count < self->parent->meals_total)
	{
		printf("%ld %ld has taken a fork \n", timestamp()
			- self->parent->time_begin, self->id);
		printf("%ld %ld is eating\n", timestamp() - self->parent->time_begin,
			self->id);
	}
	return (true);
}
