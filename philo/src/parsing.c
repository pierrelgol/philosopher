/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:51:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 13:51:15 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int64_t	parse_number(const char *const number)
{
	int64_t	result;
	int64_t	sign;
	int64_t	i;

	if (!number)
		return (0);
	sign = 1;
	i = 0;
	while (is_space(number[i]))
		++i;
	if (number[i] && (number[i] == '-' || number[i] == '+'))
	{
		if (number[i++] == '-')
			sign = -1;
	}
	result = 0;
	while (is_digit(number[i]))
	{
		result = (number[i] - '0') + (result * 10);
		++i;
	}
	return (result * sign);
}

bool	parse_philo_config_4(t_philo_config *const out_result, char **argv)
{
	out_result->number_of_philosophers = parse_number(argv[1]);
	out_result->number_of_meals = parse_number(argv[5]);
	out_result->time_to_die = parse_number(argv[2]);
	out_result->time_to_eat = parse_number(argv[3]);
	out_result->time_to_sleep = parse_number(argv[4]);
	out_result->number_of_meals = -1;
	return (true);
}

bool	parse_philo_config_5(t_philo_config *const out_result, char **argv)
{
	out_result->number_of_philosophers = parse_number(argv[1]);
	out_result->number_of_meals = parse_number(argv[5]);
	out_result->time_to_die = parse_number(argv[2]);
	out_result->time_to_eat = parse_number(argv[3]);
	out_result->time_to_sleep = parse_number(argv[4]);
	out_result->number_of_meals = parse_number(argv[5]);
	if (out_result->number_of_meals <= -1)
		return (false);
	return (true);
}

bool	sanitize_philo_config(t_philo_config *const out_result)
{
	int64_t	time_to_think;

	time_to_think = out_result->time_to_die - (out_result->time_to_eat
			+ out_result->time_to_sleep);
	if (time_to_think <= 0)
		return (false);
	out_result->time_to_think = time_to_think;
	if (out_result->number_of_philosophers < 1
		|| out_result->number_of_philosophers > 200)
		return (false);
	if (out_result->number_of_meals != -1 && (out_result->number_of_meals < 1
			|| out_result->number_of_meals > INT32_MAX))
		return (false);
	if (out_result->time_to_die < 0 || out_result->time_to_die > INT32_MAX)
		return (false);
	if (out_result->time_to_sleep < 0 || out_result->time_to_sleep > INT32_MAX)
		return (false);
	if (out_result->time_to_eat < 0 || out_result->time_to_eat > INT32_MAX)
		return (false);
	return (true);
}

bool	parse_philo_config(t_philo_config *const out_result, int32_t argc,
		char **argv)
{
	if (argc == 5)
		parse_philo_config_4(out_result, argv);
	else if (argc == 6)
		parse_philo_config_5(out_result, argv);
	else
		return (false);
	out_result->is_valid = sanitize_philo_config(out_result);
	return (out_result->is_valid);
}
