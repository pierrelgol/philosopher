/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:01:05 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/27 21:01:05 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "../library/include/slib.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef CPU_FREQ_HZ
#  define CPU_FREQ_HZ 3200000000ULL
# endif

typedef struct s_philo_config		t_philo_config;
typedef struct s_philo				t_philo;
typedef struct s_philo_supervisor	t_philo_supervisor;
typedef struct s_philo_container	t_philo_container;

typedef enum e_action_type
{
	SLEEPING,
	EATING,
	TAKING_FORKS,
	THINKING,
	DEAD,
}									t_action_type;

struct								s_philo_config
{
	int64_t							number_of_philosophers;
	int64_t							time_to_die;
	int64_t							time_to_eat;
	int64_t							time_to_sleep;
	int64_t							time_to_think;
	int64_t							number_of_meals;
	bool							is_valid;
};

struct								s_philo_container
{
	pthread_t						supervisor;
	pthread_t						*tid;
	pthread_mutex_t					*forks;
	pthread_mutex_t					lock;
	pthread_mutex_t					stdout;
	t_philo							*philosopers;
	int64_t							philo_total;
	int64_t							meals_total;
	int64_t							philo_count;
	int64_t							meals_count;
	int64_t							time_begin;
	int64_t							time_to_die;
	int64_t							time_to_eat;
	int64_t							time_to_sleep;
	int64_t							time_to_think;
	bool							is_synced;
	bool							stop;
};

struct								s_philo
{
	t_philo_container				*parent;
	pthread_mutex_t					*left_fork;
	pthread_mutex_t					*right_fork;
	pthread_t						*tid;
	int64_t							id;
	int64_t							time_to_die;
	int64_t							time_to_sleep;
	int64_t							time_to_eat;
	int64_t							time_to_think;
	int64_t							time_last_meal;
	int64_t							meal_count;
	bool							is_eating;
	bool							stop;
};

#endif
