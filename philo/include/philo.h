/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:02:47 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/29 10:02:48 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "common.h"

// config
bool	config_parse(t_philo_config *const out_result, int32_t argc,
			char **argv);
void	print_config(const t_philo_config *const self);

// philosopher
bool	philo_container_create(t_philo_container *const self,
			const t_philo_config *const cfg);
bool	philo_container_destroy(t_philo_container *const self);

// monitor
void	*philo_monitor(void *arg);

// routine
void	*philo_run(void *arg);
void	philo_eats(t_philo *const philo);
void	philo_sleeps(t_philo *const philo);
void	philo_thinks(t_philo *const self);

// routine helpers
bool	philo_can_eat(t_philo *const philo);
bool	philo_try_get_left_fork(t_philo *const philo);
bool	philo_try_get_right_fork(t_philo *const philo);

// utils
void	safe_sleep(t_philo *const self, const int64_t ammount);
int64_t	timestamp(void);
bool	philo_need_to_stop(t_philo *philo);

// errors
void	error(const char *const msg);
void	error_and_die(const char *const msg);
void	error_cleanup_and_die(t_philo_container *const self,
			const char *const msg);

#endif
