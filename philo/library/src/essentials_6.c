/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:35:26 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:35:27 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

int64_t	string_compare(const char *const source1, const char *const source2)
{
	uint8_t		*ps1;
	uint8_t		*ps2;
	uint64_t	i;

	ps1 = (uint8_t *)source1;
	ps2 = (uint8_t *)source2;
	if (!source1 || !source2)
		return (0);
	i = 0;
	while (*(ps1 + i) && *(ps1 + i) == *(ps2 + i))
		i += 1;
	return (*(ps1 + i) - *(ps2 + i));
}

int64_t	string_ncompare(const char *const source1, const char *const source2,
		const uint64_t n)
{
	uint8_t		*ps1;
	uint8_t		*ps2;
	uint64_t	i;

	ps1 = (uint8_t *)source1;
	ps2 = (uint8_t *)source2;
	if (!source1 || !source2)
		return (0);
	i = 0;
	while (*(ps1 + i) && *(ps1 + i) == *(ps2 + i) && i < n)
		i += 1;
	return (*(ps1 + i) - *(ps2 + i));
}

uint64_t	string_concat(char *const dst, const char *const src,
		const uint64_t size)
{
	uint64_t	i;
	uint64_t	j;
	uint64_t	k;

	if ((!dst || !src) && !size)
		return (0);
	k = 0;
	i = string_length(dst);
	j = string_length(src);
	if (!size)
		return (j);
	k = j + i;
	if (i > size)
		return (j + size);
	j = 0;
	while (*(src + j) && i + j < size - 1)
	{
		*(dst + (i + j)) = *(src + j);
		j++;
	}
	*(dst + i + j) = '\0';
	if (k >= i + size && i > k - i)
		return (i + size);
	return (k);
}

uint64_t	string_copy(char *const dest, const char *const source,
		const uint64_t dsize)
{
	uint64_t	slen;
	uint64_t	i;

	slen = string_length(source);
	if (dsize == 0)
		return (slen);
	i = 0;
	while (*(source + i) && (i + 1) < dsize)
	{
		*(dest + i) = *(source + i);
		i += 1;
	}
	*(dest + i) = '\0';
	return (slen);
}

uint64_t	string_count(const char *const source, const char *const delimiters)
{
	char		*set;
	uint64_t	result;
	uint64_t	i;

	set = (char [256]){0};
	if (!source || !delimiters)
		return (0);
	i = 0;
	while (*(delimiters + i))
	{
		set[(uint64_t) * (delimiters + i)] = 1;
		i += 1;
	}
	i = 0;
	result = 0;
	while (*(source + i))
	{
		if (set[(uint64_t) * (source + i)] == 1)
			result += 1;
		i += 1;
	}
	return (result);
}
