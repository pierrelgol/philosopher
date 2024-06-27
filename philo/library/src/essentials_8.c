/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:35:42 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:35:42 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

char	*string_nclone(const char *const source, const uint64_t n)
{
	return (memory_copy(memory_alloc(n + 1), source, n));
}

char	*string_search(const char *const haystack, const char *const needle,
		const uint64_t len)
{
	uint64_t	i;
	uint64_t	j;

	if (!haystack && len == 0)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (*(haystack + i))
	{
		j = 0;
		while (*(haystack + i) && *(haystack + i) == *(needle + j) && i < len)
		{
			j += 1;
			i += 1;
		}
		if (!*(needle + j))
			return ((char *)&haystack[(int64_t)i - j]);
		i = (i - j) + 1;
	}
	return (NULL);
}

uint64_t	string_span(const char *const source, const char *const delimiters)
{
	uint64_t	result;
	uint64_t	i;
	char		*set;

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
	while (*(source + i) && set[(uint64_t) * (source + i)] == 1)
	{
		result += 1;
		i += 1;
	}
	return (result);
}
