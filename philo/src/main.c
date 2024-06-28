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

#include "philosopher.h"

int32_t	main(int32_t argc, char **argv)
{
	t_philo_container	*self;
	t_philo_config		cfg;

	if (parse_philo_config(&cfg, argc, argv))
	{
		print_config(&cfg);
		self = philo_container_create(&cfg);
		if (!self)
		{
			printf("initialization failure\n");
			exit(1);
		}
		if (!simulation_init(self))
		{
			printf("runtime failure\n");
			exit(1);
		}
		self = philo_container_destroy(self);
	}
	else
		printf("inputs are invalid\n");
	return (EXIT_SUCCESS);
}
