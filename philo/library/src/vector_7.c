/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:24:32 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:32 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

void	it_restore(t_vector *self)
{
	self->index = self->saved;
}

void	it_advance(t_vector *self)
{
	if (it_end(self))
		return ;
	self->index += 1;
}

bool	it_contains(t_vector *self, uintptr_t elem, bool(eql)(uintptr_t a,
			uintptr_t b))
{
	const uint64_t	saved = self->index;
	uintptr_t		maybe_elem;

	if (it_end(self))
		return (false);
	while (!it_end(self))
	{
		maybe_elem = it_peek_curr(self);
		if (eql(maybe_elem, elem))
		{
			self->index = saved;
			return (true);
		}
		it_advance(self);
	}
	self->index = saved;
	return (false);
}

uintptr_t	it_match(t_vector *self, uintptr_t elem, bool(eql)(uintptr_t a,
			uintptr_t b))
{
	uintptr_t	maybe_elem;

	if (it_end(self))
		return (0);
	maybe_elem = it_peek_next(self);
	if (!maybe_elem)
		return (0);
	if (eql(maybe_elem, elem))
		return (elem);
	return (0);
}

uint64_t	it_skip(t_vector *self, uintptr_t elem, bool(eql)(uintptr_t a,
			uintptr_t b))
{
	uint64_t	count;

	count = 0;
	while (it_match(self, elem, eql) != 0)
	{
		it_advance(self);
		count += 1;
	}
	return (count);
}
