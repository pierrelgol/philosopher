/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:14:00 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:14:01 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

t_trie_node	*trie_node_create(void)
{
	t_trie_node	*self;

	self = (t_trie_node *)memory_alloc(sizeof(t_trie_node));
	if (!self)
		return (NULL);
	self->is_end_of_word = false;
	memory_fill(self->children, 0x00, ALPHABET_SIZE * sizeof(void *));
	return (self);
}

t_trie_node	*trie_node_find_prefix_node(t_trie_node *const self,
		const char *prefix)
{
	t_trie_node	*temp;
	uint64_t	index;

	temp = self;
	while (*prefix && temp)
	{
		index = *prefix - 'a';
		temp = temp->children[index];
		++prefix;
	}
	return (temp);
}

bool	trie_node_remove_child(t_trie_node *self, const char *const key,
		const uint64_t depth)
{
	uint64_t	index;

	if (!self)
		return (false);
	if (*key == '\0')
	{
		if (self->is_end_of_word)
		{
			self->is_end_of_word = false;
			if (trie_node_is_empty(self))
				return (memory_dealloc(self), (true));
			return (false);
		}
	}
	else
	{
		index = *key - 'a';
		if (trie_node_remove_child(self->children[index], key + 1, depth + 1))
		{
			self->children[index] = NULL;
			return (!self->is_end_of_word && trie_node_is_empty(self));
		}
	}
	return (false);
}

bool	trie_node_is_empty(t_trie_node *self)
{
	uint64_t	i;

	i = 0;
	while (i < ALPHABET_SIZE)
	{
		if (self->children[i])
			return (false);
		++i;
	}
	return (true);
}

void	trie_node_destroy(t_trie_node *self)
{
	uint64_t	i;

	if (self)
	{
		i = 0;
		while (i < ALPHABET_SIZE)
		{
			if (self->children[i])
				trie_node_destroy(self->children[i]);
			++i;
		}
		memory_dealloc(self);
	}
}
