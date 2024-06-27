/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:14 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

bool	vector_insert_at(t_vector *self, uintptr_t elem, const uint64_t index)
{
	uint64_t	bytes_to_move;

	if (index > self->count)
		return (false);
	if (vector_is_full(self))
	{
		if (!vector_resize(self, self->capacity * 2))
			return (false);
	}
	bytes_to_move = (self->count - index) * sizeof(uintptr_t);
	memory_move((self->data + index + 1), (self->data + index), bytes_to_move);
	self->data[index] = elem;
	self->count += 1;
	return (true);
}

bool	vector_insert_sorted(t_vector *self, uintptr_t elem,
		int64_t(cmp)(uintptr_t a, uintptr_t b))
{
	uint64_t	pos;
	uint64_t	i;

	if (self == NULL || self->data == NULL)
		return (false);
	pos = 0;
	if (self->is_sorted == 0)
		vector_sort(self, cmp);
	if (self->count == self->capacity)
	{
		if (!vector_resize(self, self->capacity * 2))
			return (false);
	}
	while (pos < self->count && cmp(self->data[pos], elem) < 0)
		pos++;
	i = self->count;
	while (i > pos)
	{
		self->data[i] = self->data[i - 1];
		i -= 1;
	}
	self->data[pos] = elem;
	self->count++;
	return (true);
}

uintptr_t	vector_remove_front(t_vector *self)
{
	if (vector_is_empty(self))
		return (0);
	return (vector_remove_at(self, 0));
}

uintptr_t	vector_remove_back(t_vector *self)
{
	if (vector_is_empty(self))
		return (0);
	return (vector_remove_at(self, self->count - 1));
}

uintptr_t	vector_remove_after(t_vector *self, const uint64_t index)
{
	if (vector_is_empty(self))
		return (0);
	return (vector_remove_at(self, index + 1));
}
