/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:10:02 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 11:10:02 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include "essentials.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_entry
{
	char		*key;
	uintptr_t	value;
}				t_entry;

typedef struct s_hashmap
{
	uint64_t	size;
	uint64_t	capacity;
	t_entry		*body;

}				t_hashmap;

t_hashmap		*hashmap_create(uint64_t capacity);
void			hashmap_destroy(t_hashmap *self);
void			hashmap_put(t_hashmap *self, char *key, uintptr_t value);
uintptr_t		hashmap_get(t_hashmap *self, char *key);
uint64_t		hashmap_hash(char *str);
t_entry			*hashmap_body_create(uint64_t capacity);
void			hashmap_body_remove(t_hashmap *self, char *key);
void			hashmap_body_resize(t_hashmap *self, uint64_t capacity);
uint64_t		hashmap_body_find_empty(t_hashmap *self, char *key);

bool			is_prime(uint64_t num);
uint64_t		find_next_prime(uint64_t num);
#endif
