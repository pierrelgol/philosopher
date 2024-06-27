/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:06 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

void	vector_set_at(t_vector *vector, uintptr_t elem, const uint64_t index)
{
	if (vector_is_empty(vector) || index > vector->count)
		return ;
	vector->data[index] = elem;
}

bool	vector_push(t_vector *self, uintptr_t elem)
{
	return (vector_insert_at(self, elem, self->count));
}

uintptr_t	vector_pop(t_vector *self)
{
	if (vector_is_empty(self))
		return (0);
	return (vector_remove_at(self, self->count - 1));
}

bool	vector_enqueue(t_vector *self, uintptr_t elem)
{
	return (vector_insert_at(self, elem, self->count));
}

uintptr_t	vector_dequeue(t_vector *self)
{
	if (vector_is_empty(self))
		return (0);
	return (vector_remove_at(self, 0));
}
