/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:32:18 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/10 22:32:19 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIE_H
# define TRIE_H

# define ALPHABET_SIZE 26

# include "essentials.h"
# include "list.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_trie_node
{
	struct s_trie_node	*children[ALPHABET_SIZE];
	bool				is_end_of_word;

}						t_trie_node;

typedef struct Trie
{
	t_trie_node			*root;

}						t_trie;

t_trie_node				*trie_node_create(void);
t_trie_node				*trie_node_find_prefix_node(t_trie_node *const self,
							const char *prefix);
void					trie_node_destroy(t_trie_node *self);
bool					trie_node_remove_child(t_trie_node *self,
							const char *const key, const uint64_t depth);
bool					trie_node_is_empty(t_trie_node *self);

t_trie					*trie_create(void);
void					trie_insert(t_trie *const self, const char *const key);
bool					trie_search(t_trie *const self, const char *const key);
bool					trie_remove(t_trie *const self, const char *const key);
t_list					*trie_suggest(t_trie *const self, const char *prefix);
void					trie_collect_suggestions(t_trie_node *const node,
							const char *prefix, t_list *suggestions);
t_trie					*trie_destroy(t_trie *const self);

// EXPERIMENTAL

#endif
