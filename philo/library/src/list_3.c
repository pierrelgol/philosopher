/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:39:33 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 09:39:33 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

bool	list_is_empty(t_list *self)
{
	return (self->size == 0 || (!self->head && !self->tail));
}

uintptr_t	list_pop_front(t_list *self)
{
	uintptr_t	data;
	t_node		*node;

	node = list_remove_front(self);
	if (!node)
		return (0);
	data = node->data;
	node_destroy(node);
	return (data);
}

uintptr_t	list_pop_back(t_list *self)
{
	uintptr_t	data;
	t_node		*node;

	node = list_remove_back(self);
	if (!node)
		return (0);
	data = node->data;
	node_destroy(node);
	return (data);
}

uintptr_t	list_pop_at(t_list *self, uint64_t index)
{
	uintptr_t	data;
	t_node		*node;

	node = list_remove_at(self, index);
	if (!node)
		return (0);
	data = node->data;
	node_destroy(node);
	return (data);
}

void	list_push_front(t_list *self, uintptr_t data)
{
	t_node	*node;

	node = node_create(data);
	list_insert_front(self, node);
}
