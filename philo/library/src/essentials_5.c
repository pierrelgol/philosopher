/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:35:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:35:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

void	*memory_fill(void *const dest, const int32_t byte, const uint64_t dsize)
{
	uint8_t		*dptr;
	uint8_t		b;
	uint64_t	i;

	dptr = (uint8_t *)dest;
	b = (uint8_t)byte;
	i = dsize;
	while (i != 0)
	{
		*(dptr + i - 1) = b;
		i -= 1;
	}
	return (dest);
}

void	*memory_move(void *const dest, const void *const source,
		const uint64_t bytes)
{
	uint64_t	i;

	if (!dest && !source)
		return (NULL);
	i = bytes;
	if (dest > source)
	{
		while (i != 0)
		{
			*((uint8_t *)dest + i - 1) = *((uint8_t *)source + i - 1);
			i -= 1;
		}
		return (dest);
	}
	while (i != 0)
	{
		*((uint8_t *)dest + (bytes - i)) = *((uint8_t *)source + (bytes - i));
		i -= 1;
	}
	return (dest);
}

void	*memory_search(const void *const source, const int32_t byte,
		const uint64_t ssize)
{
	uint8_t		*ptr;
	uint8_t		b;
	uint64_t	i;

	i = 0;
	b = (uint8_t)byte;
	ptr = (uint8_t *)source;
	while (i < ssize && *(ptr + i) != b)
		i += 1;
	if (i == ssize)
		return (NULL);
	return ((void *)ptr + i);
}

void	*memory_zero(void *const dest, const uint64_t dsize)
{
	uint8_t		*dptr;
	uint8_t		b;
	uint64_t	i;

	dptr = (uint8_t *)dest;
	i = dsize;
	b = 0x00;
	while (i != 0)
	{
		*(dptr + i - 1) = b;
		i -= 1;
	}
	return (dest);
}

char	*string_clone(const char *const source)
{
	uint64_t	slen;

	slen = string_length(source);
	return (memory_copy(memory_alloc(slen + 1), source, slen));
}
