/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:35:15 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:35:16 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "slib.h"

int64_t	memory_compare(const void *const s1, const void *const s2,
		const uint64_t n)
{
	uint8_t		*s1ptr;
	uint8_t		*s2ptr;
	uint64_t	i;

	if (n == 0)
		return (0);
	s1ptr = (uint8_t *)s1;
	s2ptr = (uint8_t *)s2;
	i = 0;
	while (i < n && *(s1ptr + i) == *(s2ptr + i))
		i += 1;
	return (*(s1ptr + i) - *(s2ptr + i));
}

void	*memory_copy(void *const dest, const void *const source,
		const uint64_t bytes)
{
	uint8_t		*sptr;
	uint8_t		*dptr;
	uint64_t	i;

	if (!dest && !source)
		return (NULL);
	dptr = (uint8_t *)dest;
	sptr = (uint8_t *)source;
	i = 0;
	while (i < bytes)
	{
		*(dptr + i) = *(sptr + i);
		i += 1;
	}
	return (dest);
}

void	memory_dealloc(void *const ptr)
{
	free(ptr);
}

void	*memory_dupe(const void *const source, const uint64_t ssize)
{
	return (memory_copy(memory_alloc(ssize), source, ssize));
}

void	*memory_dupz(const void *const source)
{
	uint64_t	slen;

	slen = string_length((const char *const)source);
	if (slen == 0)
		return (memory_alloc(1));
	return (memory_dupe(source, slen));
}
