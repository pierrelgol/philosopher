/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:40:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/29 11:40:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_run(void *arg)
{
	t_philo	*self;

	self = arg;
	while (true)
	{
		philo_eats(self);
		if (philo_need_to_stop(self))
			break ;
		philo_sleeps(self);
		if (philo_need_to_stop(self))
			break ;
		philo_thinks(self);
		if (philo_need_to_stop(self))
			break ;
	}
	return (NULL);
}

void	philo_eats(t_philo *const self)
{
	if (philo_try_get_left_fork(self) == false)
		return ;
	if (philo_try_get_right_fork(self) == false)
		return ;
	pthread_mutex_unlock(&self->parent->write_lock);
	pthread_mutex_lock(&self->eating_lock);
	self->meal_count++;
	pthread_mutex_unlock(&self->eating_lock);
	pthread_mutex_lock(&self->eating_lock);
	self->time_last_meal = timestamp();
	pthread_mutex_unlock(&self->eating_lock);
	safe_sleep(self, self->parent->time_to_eat);
	pthread_mutex_unlock(self->left_fork);
	pthread_mutex_unlock(self->right_fork);
}

void	philo_sleeps(t_philo *const self)
{
	pthread_mutex_lock(&self->parent->write_lock);
	if (philo_can_eat(self))
		printf("%ld %ld is sleeping\n", timestamp() - self->parent->time_begin,
			self->id);
	pthread_mutex_unlock(&self->parent->write_lock);
	safe_sleep(self, self->parent->time_to_sleep);
}

void	philo_thinks(t_philo *const self)
{
	pthread_mutex_lock(&self->parent->write_lock);
	if (philo_can_eat(self))
		printf("%ld %ld is thinking\n", timestamp() - self->parent->time_begin,
			self->id);
	pthread_mutex_unlock(&self->parent->write_lock);
	safe_sleep(self, self->parent->time_to_think);
}
