/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:35:06 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:35:08 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

inline bool	is_graph(const int32_t ch)
{
	return (!is_ctrl(ch) && !is_space(ch));
}

inline bool	is_hex(const int32_t ch)
{
	return ((ch >= '0' && ch <= '9') || ((ch | 32) >= 'a' && (ch | 32) <= 'f'));
}

inline bool	is_lower(const int32_t ch)
{
	return (ch >= 'a' && ch <= 'z');
}

inline bool	is_newline(const int32_t ch)
{
	return (ch == '\n');
}

inline bool	is_print(const int32_t ch)
{
	return (ch >= ' ' && ch <= '~');
}
