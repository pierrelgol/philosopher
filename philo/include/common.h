/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:35:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/29 12:35:34 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif

typedef struct s_philo				t_philo;
typedef struct s_philo_config		t_philo_config;
typedef struct s_philo_container	t_philo_container;

struct								s_philo_config
{
	int64_t							number_of_philosopher;
	int64_t							number_of_meals;
	int64_t							time_to_die;
	int64_t							time_to_eat;
	int64_t							time_to_sleep;
	int64_t							time_to_think;
};

struct								s_philo
{
	t_philo_container				*parent;
	pthread_mutex_t					*right_fork;
	pthread_mutex_t					eating_lock;
	pthread_mutex_t					*left_fork;
	pthread_t						*thread;
	int64_t							id;
	int64_t							time_last_meal;
	int64_t							meal_count;
};

struct								s_philo_container
{
	int64_t							philo_total;
	int64_t							philo_count;
	int64_t							time_to_die;
	int64_t							time_to_eat;
	int64_t							time_to_sleep;
	int64_t							time_to_think;
	int64_t							meals_total;
	int64_t							time_begin;
	int64_t							philo_died;
	pthread_mutex_t					time_lock;
	pthread_mutex_t					died_lock;
	pthread_mutex_t					write_lock;
	pthread_mutex_t					forks[MAX_PHILO];
	t_philo							philos[MAX_PHILO];
	pthread_t						threads[MAX_PHILO + 1];
};

#endif
