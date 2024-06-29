/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:34:27 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 15:34:30 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	safe_sleep(t_philo *const self, const int64_t ammount)
{
	int64_t	total_time;

	total_time = timestamp() + ammount;
	while (timestamp() < total_time)
	{
		usleep(100);
		pthread_mutex_lock(&self->parent->died_lock);
		if (self->parent->philo_died == true)
		{
			pthread_mutex_unlock(&self->parent->died_lock);
			break ;
		}
		pthread_mutex_unlock(&self->parent->died_lock);
	}
}

void	print_config(const t_philo_config *const self)
{
	printf("--------------------------------\n");
	printf("PHILO CONFIG :\n");
	printf("number_of_philosophers : %ld\n", self->number_of_philosopher);
	printf("time_to_die            : %ld ms\n", self->time_to_die);
	printf("time_to_eat            : %ld ms\n", self->time_to_eat);
	printf("time_to_sleep          : %ld ms\n", self->time_to_sleep);
	printf("time_to_think          : %ld ms\n", self->time_to_think);
	printf("number_of_meals        : %ld\n", self->number_of_meals);
	printf("--------------------------------\n");
}

bool	philo_need_to_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->parent->died_lock);
	if (philo->parent->philo_died == true)
	{
		pthread_mutex_unlock(&philo->parent->died_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->parent->died_lock);
	return (false);
}
