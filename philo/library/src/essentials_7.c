/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:35:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:35:34 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

uint64_t	string_wcount(const char *const source,
		const char *const delimiters)
{
	uint64_t	count;
	uint64_t	slen;
	uint64_t	i;

	if (!source || !delimiters)
		return (0);
	i = 0;
	slen = string_length(source);
	count = 0;
	while (i < slen)
	{
		i += string_span(source + i, delimiters);
		if (i < slen)
			count += 1;
		i += string_cspan(source + i, delimiters);
	}
	return (count);
}

uint64_t	string_cspan(const char *const source, const char *const delimiters)
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
	while (*(source + i) && set[(uint64_t) * (source + i)] != 1)
	{
		result += 1;
		i += 1;
	}
	return (result);
}

int64_t	string_index_of(const char *const source, const int32_t ch)
{
	uint64_t	slen;
	char		*result;

	slen = string_length(source);
	result = memory_search(source, ch, slen);
	if (!result)
		return (-1);
	return (result - source);
}

char	*string_join(const char *const s1, const char *const s2)
{
	char		*result;
	uint64_t	s1len;
	uint64_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = string_length(s1);
	s2len = string_length(s2);
	result = memory_alloc(s1len + s2len + 1);
	if (!result)
		return (NULL);
	memory_copy(result, s1, s1len);
	memory_copy(result + s1len, s2, s2len);
	*(result + s1len + s2len) = 0x00;
	return (result);
}

uint64_t	string_length(const char *const source)
{
	uint64_t	i;

	if (!source)
		return (0);
	i = 0;
	while (*(source + i))
		i += 1;
	return (i);
}
