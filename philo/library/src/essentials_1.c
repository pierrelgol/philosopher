/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:34:58 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:34:59 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

inline bool	is_alnum(const int32_t ch)
{
	return (((ch | 32) >= 'a' && (ch | 32) <= 'z') || (ch >= '0' && ch <= '9'));
}

inline bool	is_alpha(const int32_t ch)
{
	return ((ch | 32) >= 'a' && (ch | 32) <= 'z');
}

inline bool	is_ascii(const int32_t ch)
{
	return (ch >= 0 && ch <= 127);
}

inline bool	is_ctrl(const int32_t ch)
{
	return (ch == 127 || (ch >= 0 && ch <= 31));
}

inline bool	is_digit(const int32_t ch)
{
	return (ch >= '0' && ch <= '9');
}
