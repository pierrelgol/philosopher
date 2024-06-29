/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:47:52 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/29 11:47:53 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_died(t_philo *const self)
{
	pthread_mutex_lock(&self->parent->write_lock);
	pthread_mutex_lock(&self->parent->died_lock);
	self->parent->philo_died = true;
	printf("%ld %ld died\n", timestamp() - self->parent->time_begin, self->id);
	pthread_mutex_unlock(&self->parent->died_lock);
	pthread_mutex_unlock(&self->parent->write_lock);
}

static bool	philo_check_self(t_philo *const self)
{
	pthread_mutex_lock(&self->eating_lock);
	if ((timestamp() - self->time_last_meal) > self->parent->time_to_die)
	{
		philo_died(self);
		pthread_mutex_unlock(&self->eating_lock);
		return (true);
	}
	pthread_mutex_unlock(&self->eating_lock);
	return (false);
}

static bool	philo_monitor_print_end_of_meal(t_philo_container *const self)
{
	pthread_mutex_lock(&self->died_lock);
	self->philo_died = true;
	pthread_mutex_unlock(&self->died_lock);
	pthread_mutex_lock(&self->write_lock);
	printf("%ld All the philosophers are satisfied\n", timestamp()
		- self->time_begin);
	pthread_mutex_unlock(&self->write_lock);
	return (true);
}

static void	philo_monitor_check_meal_count(t_philo_container *const self,
		const uint64_t index, bool *const stop_cond)
{
	pthread_mutex_lock(&self->philos[index].eating_lock);
	if (self->philos[index].meal_count < self->meals_total)
		*stop_cond = 1;
	pthread_mutex_unlock(&self->philos[index].eating_lock);
}

void	*philo_monitor(void *arg)
{
	t_philo_container	*self;
	bool				stop_cond;
	int64_t				i;

	self = (t_philo_container *)arg;
	while (true)
	{
		stop_cond = 0;
		i = -1;
		while (++i < self->philo_total)
		{
			if (philo_check_self(&self->philos[i]))
				break ;
			philo_monitor_check_meal_count(self, i, &stop_cond);
			if (self->philo_died)
				break ;
		}
		if (self->philo_died || (stop_cond == 0
				&& philo_monitor_print_end_of_meal(self)))
			break ;
		usleep(100);
	}
	return (NULL);
}
