/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:14:04 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:14:04 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

t_trie	*trie_create(void)
{
	t_trie	*self;

	self = (t_trie *)memory_alloc(sizeof(t_trie));
	if (!self)
		return (NULL);
	self->root = trie_node_create();
	if (!self->root)
	{
		memory_dealloc(self);
		return (NULL);
	}
	return (self);
}

void	trie_insert(t_trie *const self, const char *const key)
{
	t_trie_node	*node;
	const char	*ptr;
	uint64_t	index;

	ptr = key;
	node = self->root;
	while (*ptr)
	{
		index = *ptr - 'a';
		if (!node->children[index])
			node->children[index] = trie_node_create();
		node = node->children[index];
		++ptr;
	}
	node->is_end_of_word = true;
}

bool	trie_search(t_trie *const self, const char *const key)
{
	t_trie_node	*node;
	const char	*ptr;
	uint64_t	index;

	node = self->root;
	ptr = key;
	while (*ptr)
	{
		index = *key - 'a';
		if (!node->children[index])
			return (false);
		node = node->children[index];
		++ptr;
	}
	return (node != NULL && node->is_end_of_word);
}

bool	trie_remove(t_trie *const self, const char *const key)
{
	return (trie_node_remove_child(self->root, key, 0));
}

t_list	*trie_suggest(t_trie *const self, const char *prefix)
{
	t_trie_node	*prefix_node;
	t_list		*suggest;

	suggest = list_create();
	prefix_node = trie_node_find_prefix_node(self->root, prefix);
	if (prefix_node)
		trie_collect_suggestions(prefix_node, string_clone(prefix), suggest);
	return (suggest);
}
