/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:39:41 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 09:39:42 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

void	node_insert_child(t_node *self, t_node *child)
{
	if (!self || !child)
		return ;
	child->next = self->next;
	self->next = child->next;
}

t_node	*node_remove_child(t_node *self)
{
	t_node	*child;

	if (!self || !self->next)
		return (NULL);
	child = self->next;
	self->next = self->next;
	child->next = NULL;
	return (child);
}

t_node	*node_destroy(t_node *self)
{
	if (self)
	{
		memory_dealloc(self);
	}
	return (NULL);
}
