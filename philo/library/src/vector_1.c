/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:02 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:02 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

t_vector	*vector_create(void)
{
	t_vector	*self;

	self = (t_vector *)memory_alloc(sizeof(t_vector));
	if (!self)
		return (NULL);
	self->capacity = VECTOR_DEFAULT_CAPACITY;
	self->count = 0;
	self->is_sorted = false;
	self->data = memory_alloc(VECTOR_DEFAULT_CAPACITY * sizeof(uintptr_t));
	if (!self->data)
		return (vector_destroy(self));
	return (self);
}

t_vector	*vector_create_with_capacity(const uint64_t capacity)
{
	t_vector	*self;

	self = (t_vector *)memory_alloc(sizeof(t_vector));
	if (!self)
		return (NULL);
	self->capacity = capacity;
	self->count = 0;
	self->data = memory_alloc(capacity * sizeof(uintptr_t));
	if (!self->data)
		return (vector_destroy(self));
	return (self);
}

void	vector_clear(t_vector *self)
{
	memory_fill(self->data, 0x00, self->count * sizeof(uintptr_t));
	self->count = 0;
	self->index = 0;
	self->saved = 0;
}

t_vector	*vector_destroy(t_vector *self)
{
	if (self)
	{
		if (self->data)
			memory_dealloc(self->data);
		memory_dealloc(self);
	}
	return (NULL);
}

uintptr_t	vector_get_at(t_vector *vector, const uint64_t index)
{
	if (vector_is_empty(vector) || index > vector->count)
		return (0);
	return (vector->data[index]);
}
