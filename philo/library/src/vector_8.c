/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:31:10 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:31:10 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

uintptr_t	it_peek_next(t_vector *self)
{
	if (self->index + 1 >= self->count)
		return (0);
	return (*(self->data + self->index + 1));
}

uintptr_t	it_peek_curr(t_vector *self)
{
	if (self->index >= self->count)
		return (0);
	return (*(self->data + self->index));
}

uintptr_t	it_peek_prev(t_vector *self)
{
	if (self->index < 1 || self->count == 0)
		return (0);
	return (*(self->data + self->index - 1));
}
