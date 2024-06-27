/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:14:12 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/13 10:14:12 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slib.h"

static char	*trie_build_prefix(const char *prefix, char new_char)
{
	const uint64_t	prefix_len = string_length(prefix);
	const uint64_t	new_len = prefix_len + 2;
	char			*new_prefix;
	uint64_t		i;

	new_prefix = (char *)memory_alloc(new_len);
	if (new_prefix)
	{
		i = 0;
		while (i < prefix_len)
		{
			new_prefix[i] = prefix[i];
			++i;
		}
		new_prefix[prefix_len] = new_char;
		new_prefix[prefix_len + 1] = '\0';
	}
	return (new_prefix);
}

void	trie_collect_suggestions(t_trie_node *const node, const char *prefix,
		t_list *suggestions)
{
	char		*prefix_buffer;
	char		new_char;
	uint64_t	i;

	if (!node)
		return ;
	if (node->is_end_of_word)
		list_push_back(suggestions, (uintptr_t)strdup(prefix));
	i = 0;
	while (i < ALPHABET_SIZE)
	{
		if (node->children[i])
		{
			new_char = 'a' + i;
			prefix_buffer = trie_build_prefix(prefix, new_char);
			if (prefix_buffer)
			{
				trie_collect_suggestions(node->children[i], prefix_buffer,
					suggestions);
				memory_dealloc(prefix_buffer);
			}
		}
		++i;
	}
}

t_trie	*trie_destroy(t_trie *const self)
{
	if (self)
	{
		trie_node_destroy(self->root);
		memory_dealloc(self);
	}
	return (NULL);
}
