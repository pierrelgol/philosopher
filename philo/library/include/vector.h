/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:21:45 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:21:46 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# ifndef VECTOR_DEFAULT_CAPACITY
#  define VECTOR_DEFAULT_CAPACITY 32
# endif

# include "essentials.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_vector
{
	uint64_t	is_sorted;
	uint64_t	capacity;
	uint64_t	count;
	uint64_t	index;
	uint64_t	saved;
	uintptr_t	*data;

}				t_vector;

t_vector		*vector_create_with_capacity(const uint64_t capacity);
t_vector		*vector_create(void);
bool			vector_resize(t_vector *self, const uint64_t new_capacity);
void			vector_clear(t_vector *self);
t_vector		*vector_destroy(t_vector *self);
bool			vector_insert_front(t_vector *self, uintptr_t elem);
bool			vector_insert_back(t_vector *self, uintptr_t elem);
bool			vector_insert_after(t_vector *self, uintptr_t elem,
					const uint64_t index);
bool			vector_insert_at(t_vector *self, uintptr_t elem,
					const uint64_t index);
uintptr_t		vector_remove_front(t_vector *self);
uintptr_t		vector_remove_back(t_vector *self);
uintptr_t		vector_remove_after(t_vector *self, const uint64_t index);
uintptr_t		vector_remove_at(t_vector *self, const uint64_t index);
bool			vector_push(t_vector *vector, uintptr_t elem);
uintptr_t		vector_pop(t_vector *vector);
bool			vector_enqueue(t_vector *vector, uintptr_t elem);
uintptr_t		vector_dequeue(t_vector *vector);
uintptr_t		vector_get_at(t_vector *vector, const uint64_t index);
void			vector_set_at(t_vector *vector, uintptr_t elem,
					const uint64_t index);
bool			vector_is_full(t_vector *self);
bool			vector_is_empty(t_vector *self);
void			vector_sort(t_vector *self, int64_t(cmp)(uintptr_t a,
						uintptr_t b));
int64_t			vector_search(t_vector *self, uintptr_t elem,
					int64_t(cmp)(uintptr_t a, uintptr_t b));
bool			vector_insert_sorted(t_vector *self, uintptr_t elem,
					int64_t(cmp)(uintptr_t a, uintptr_t b));

void			it_restore(t_vector *self);
void			it_advance(t_vector *self);
bool			it_contains(t_vector *self, uintptr_t elem,
					bool(eql)(uintptr_t a, uintptr_t b));
uintptr_t		it_match(t_vector *self, uintptr_t elem, bool(eql)(uintptr_t a,
						uintptr_t b));
uint64_t		it_skip(t_vector *self, uintptr_t elem, bool(eql)(uintptr_t a,
						uintptr_t b));
uintptr_t		it_peek_next(t_vector *self);
uintptr_t		it_peek_curr(t_vector *self);
uintptr_t		it_peek_prev(t_vector *self);
void			it_save(t_vector *self);
bool			it_end(t_vector *self);

#endif
