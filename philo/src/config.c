/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:51:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 13:51:15 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int64_t	config_parse_number(const char *const number)
{
	int64_t	result;
	int64_t	sign;
	int64_t	i;

	if (!number)
		return (0);
	sign = 1;
	i = 0;
	while (number[i] && (number[i] == ' ' || (number[i] >= '9'
				&& number[i] <= 13)))
		++i;
	if (number[i] && (number[i] == '-' || number[i] == '+'))
	{
		if (number[i++] == '-')
			sign = -1;
	}
	result = 0;
	while (number[i] && (number[i] >= '0' && number[i] <= '9'))
		result = (number[i++] - '0') + (result * 10);
	return (result * sign);
}

static void	config_parse_4(t_philo_config *const cfg, char **argv)
{
	cfg->number_of_philosopher = config_parse_number(argv[1]);
	cfg->number_of_meals = config_parse_number(argv[5]);
	cfg->time_to_die = config_parse_number(argv[2]);
	cfg->time_to_eat = config_parse_number(argv[3]);
	cfg->time_to_sleep = config_parse_number(argv[4]);
	cfg->number_of_meals = INT32_MAX;
}

static void	config_parse_5(t_philo_config *const cfg, char **argv)
{
	cfg->number_of_philosopher = config_parse_number(argv[1]);
	cfg->number_of_meals = config_parse_number(argv[5]);
	cfg->time_to_die = config_parse_number(argv[2]);
	cfg->time_to_eat = config_parse_number(argv[3]);
	cfg->time_to_sleep = config_parse_number(argv[4]);
	cfg->number_of_meals = config_parse_number(argv[5]);
}

static bool	config_sanitize(t_philo_config *const cfg)
{
	cfg->time_to_think = cfg->time_to_die - (cfg->time_to_eat
			+ cfg->time_to_sleep);
	if (cfg->number_of_philosopher < 1 || cfg->number_of_philosopher > 200)
		error_and_die("error : invalid number of philo\n");
	if (cfg->number_of_meals != -1 && (cfg->number_of_meals < 1
			|| cfg->number_of_meals > INT32_MAX))
		error_and_die("error : invalid number of meals\n");
	if (cfg->time_to_die <= 0 || cfg->time_to_die > INT32_MAX)
		error_and_die("error : invalid time to die\n");
	if (cfg->time_to_sleep <= 0 || cfg->time_to_sleep > INT32_MAX)
		error_and_die("error : invalid time to sleep\n");
	if (cfg->time_to_eat <= 0 || cfg->time_to_eat > INT32_MAX)
		error_and_die("error : invalid time to eat\n");
	if (cfg->time_to_think <= 0)
		error_and_die("error : invalid time to think\n");
	return (true);
}

bool	config_parse(t_philo_config *const cfg, int32_t argc, char **argv)
{
	if (argc == 5)
		config_parse_4(cfg, argv);
	else if (argc == 6)
		config_parse_5(cfg, argv);
	else
		error_and_die("error : invalid number of arguments");
	config_sanitize(cfg);
	return (true);
}
