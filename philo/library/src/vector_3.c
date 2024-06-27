/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:10 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:10 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

bool	vector_is_empty(t_vector *self)
{
	return (self->count == 0);
}

bool	vector_is_full(t_vector *self)
{
	return (self->count == self->capacity);
}

bool	vector_insert_front(t_vector *self, uintptr_t elem)
{
	return (vector_insert_at(self, elem, 0));
}

bool	vector_insert_back(t_vector *self, uintptr_t elem)
{
	return (vector_insert_at(self, elem, self->count));
}

bool	vector_insert_after(t_vector *self, uintptr_t elem,
		const uint64_t index)
{
	return (vector_insert_at(self, elem, index + 1));
}
