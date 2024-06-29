/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:52:16 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 13:52:16 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_run_one(t_philo_container *const self)
{
	self->time_begin = timestamp();
	printf("%ld 1 has taken a fork\n", timestamp() - self->time_begin);
	usleep(self->time_to_die * 1000);
	printf("%ld 1 died\n", timestamp() - self->time_begin);
}

void	philo_run_many(t_philo_container *const self,
		const uint64_t number_of_threads)
{
	uint64_t	i;

	i = 0;
	self->time_begin = timestamp();
	while (i < number_of_threads)
	{
		self->philos[i].time_last_meal = timestamp();
		if (pthread_create(&self->threads[i], NULL, philo_run,
				&self->philos[i]))
			error_cleanup_and_die(self, "error : pthread_create failed\n");
		++i;
		usleep(100);
	}
	if (pthread_create(&self->threads[i], NULL, philo_monitor, (void *)self))
		error_cleanup_and_die(self, "error : pthread_create failed\n");
	i = 0;
	while (i <= number_of_threads)
		pthread_join(self->threads[i++], NULL);
}

int32_t	main(int32_t argc, char **argv)
{
	t_philo_container	self;
	t_philo_config		cfg;

	config_parse(&cfg, argc, argv);
	philo_container_create(&self, &cfg);
	print_config(&cfg);
	if (cfg.number_of_philosopher == 1)
		philo_run_one(&self);
	else
		philo_run_many(&self, cfg.number_of_philosopher);
	philo_container_destroy(&self);
	return (EXIT_SUCCESS);
}
