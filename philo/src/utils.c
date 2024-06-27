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

#include "philosopher.h"

// int64_t gettime(void)
// {
//     struct timespec ts;
//     clock_gettime(CLOCK_MONOTONIC, &ts);
//     return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
// }

// int64_t gettime_since_ms(const int64_t beg)
// {
//     return (gettime() - beg);
// }

// void micro_sleep(int64_t time)
// {
//     int64_t start = gettime();
//     while ((gettime() - start) < time)
//     {
//         usleep(time / 10);
//     }
// }

int64_t	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int64_t	gettime_since_ms(const int64_t beg)
{
	return (timestamp() - beg);
}

void	micro_sleep(int64_t time)
{
	int64_t	start;

	start = timestamp();
	while (gettime_since_ms(start) < time)
	{
		usleep(50);
	}
}

void	report(pthread_mutex_t *stdout, const int64_t beg_time,
		const int64_t id, t_action_type activity)
{
	pthread_mutex_lock(stdout);
	if (activity == EATING)
		printf("%ld %ld is eating\n", gettime_since_ms(beg_time), id);
	else if (activity == TAKING_FORKS)
		printf("%ld %ld has taken a fork\n", gettime_since_ms(beg_time), id);
	else if (activity == SLEEPING)
		printf("%ld %ld is sleeping\n", gettime_since_ms(beg_time), id);
	else if (activity == THINKING)
		printf("%ld %ld is thinking\n", gettime_since_ms(beg_time), id);
	else
		printf("%ld %ld died\n", gettime_since_ms(beg_time), id);
	pthread_mutex_unlock(stdout);
}

void	print_config(const t_philo_config *const self)
{
	printf("--------------------------------\n");
	printf("PHILO CONFIG :\n");
	printf("number_of_philosophers : %ld\n", self->number_of_philosophers);
	printf("time_to_die            : %ld ms\n", self->time_to_die);
	printf("time_to_eat            : %ld ms\n", self->time_to_eat);
	printf("time_to_sleep          : %ld ms\n", self->time_to_sleep);
	printf("time_to_think          : %ld ms\n", self->time_to_think);
	printf("number_of_meals        : %ld\n", self->number_of_meals);
	printf("--------------------------------\n");
}
