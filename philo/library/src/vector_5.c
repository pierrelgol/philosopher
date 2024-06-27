/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:23 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

uintptr_t	vector_remove_at(t_vector *self, const uint64_t index)
{
	uint64_t	bytes_to_move;
	uintptr_t	elem;

	if (vector_is_empty(self) || index >= self->count)
		return (0);
	elem = self->data[index];
	bytes_to_move = (self->count - index - 1) * sizeof(uintptr_t);
	if (bytes_to_move)
		memory_move(self->data + index, self->data + index + 1, bytes_to_move);
	self->count -= 1;
	return (elem);
}

bool	vector_resize(t_vector *self, const uint64_t new_capacity)
{
	uintptr_t	*old_data;
	uint64_t	old_capacity;

	old_capacity = self->count;
	old_data = self->data;
	self->data = (uintptr_t *)memory_alloc(new_capacity * sizeof(uintptr_t));
	if (!self->data)
	{
		self->data = old_data;
		return (false);
	}
	memory_copy(self->data, old_data, old_capacity * sizeof(uintptr_t));
	self->capacity = new_capacity;
	memory_dealloc(old_data);
	return (true);
}

static int64_t	binary_search(t_vector *self, uintptr_t elem,
		int64_t(cmp)(uintptr_t a, uintptr_t b))
{
	int64_t	left;
	int64_t	mid;
	int64_t	right;
	int64_t	comparison;

	left = 0;
	mid = 0;
	right = self->count - 1;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		comparison = cmp(self->data[mid], elem);
		if (comparison == 0)
			return (mid);
		else if (comparison < 0)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}

static int64_t	linear_search(t_vector *self, uintptr_t elem,
		int64_t(cmp)(uintptr_t a, uintptr_t b))
{
	uint64_t	i;

	i = 0;
	while (i < self->count)
	{
		if (cmp(self->data[i], elem) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}

int64_t	vector_search(t_vector *self, uintptr_t elem, int64_t(cmp)(uintptr_t a,
			uintptr_t b))
{
	if (self == NULL || self->data == NULL)
		return (-1);
	if (self->is_sorted)
		return (binary_search(self, elem, cmp));
	else
		return (linear_search(self, elem, cmp));
	return (-1);
}
