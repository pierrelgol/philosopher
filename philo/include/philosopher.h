/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:31:00 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/23 20:31:00 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "common.h"

bool parse_philo_config(t_philo_config *const out_result, int32_t argc, char **argv);
void               print_config(const t_philo_config *const self);
t_philo_container *philo_container_create(const t_philo_config *const config);
t_philo_container *philo_container_destroy(t_philo_container *const self);
bool               simulation_init(t_philo_container *const self);
void              *simulation_sync_wait(void *arg);
void              *simulation_start(void *arg);
void              *supervisor_sync(void *arg);
void              *supervisor_monitor(void *arg);
bool supervisor_check_dead_philos(t_philo_container *const self, const uint64_t total);
bool supervisor_check_full_philos(t_philo_container *const self, const uint64_t total);

void *philo_get_fork(void *arg);
void *philo_put_fork(void *arg);
void *philo_eat(void *arg);
void *philo_sleep(void *arg);
void *philo_think(void *arg);

int64_t time_ms(void);
int64_t time_diff(int64_t time);
void report(pthread_mutex_t *stdout, const int64_t beg_time, const int64_t id, t_action_type activity);
bool philo_paranoid_sleep(t_philo *self, int64_t time);
bool philo_is_dead(t_philo *self);
bool philo_is_full(t_philo *self);
bool philo_should_stop(t_philo *philo, bool *cond);
bool philo_maybe_stop(t_philo *philo);

#endif
