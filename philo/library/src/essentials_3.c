/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:35:11 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:35:12 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "slib.h"

inline bool	is_punct(const int32_t ch)
{
	return (ch != 32 && !is_alnum(ch) && !is_ctrl(ch));
}

inline bool	is_space(const int32_t ch)
{
	return (ch == ' ' || (ch >= 9 && ch <= 13));
}

inline bool	is_upper(const int32_t ch)
{
	return (ch >= 'A' && ch <= 'Z');
}

void	*memory_alloc(const uint64_t size)
{
	return (memory_zero(malloc(size), size));
}

void	*memory_ccopy(void *const dest, const int32_t byte,
		const void *const source, const uint64_t dsize)
{
	uint8_t	*sptr;
	uint8_t	*dptr;
	uint8_t	b;
	uint8_t	i;

	dptr = (uint8_t *)dest;
	sptr = (uint8_t *)source;
	b = (uint8_t)byte;
	i = 0;
	while (i < dsize)
	{
		if (*(sptr + i) == b)
			return ((void *)(source + i + 1));
		*(dptr + i) = *(sptr + i);
		++i;
	}
	return (NULL);
}
