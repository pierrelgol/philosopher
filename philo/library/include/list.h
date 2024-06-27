/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:11:11 by pollivie          #+#    #+#             */
/*   Updated: 2024/06/10 23:11:34 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIST_H
# define LIST_H

# include "essentials.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct node_t
{
	struct node_t	*next;
	uintptr_t		data;

}					t_node;

t_node				*node_create(uintptr_t data);
t_node				*node_get_nchild(t_node *self, uint64_t n);
void				node_insert_child(t_node *self, t_node *child);
t_node				*node_remove_child(t_node *self);
uint64_t			node_count_child(t_node *self);
t_node				*node_next(t_node *self);
t_node				*node_destroy(t_node *self);

typedef struct list_t
{
	t_node			*head;
	t_node			*tail;
	uint64_t		size;

}					t_list;

t_list				*list_create(void);
void				list_insert_front(t_list *self, t_node *new_head);
void				list_insert_at(t_list *self, t_node *node, uint64_t index);
void				list_insert_back(t_list *self, t_node *new_tail);
bool				list_is_empty(t_list *self);
uint64_t			list_size(t_list *self);
t_node				*list_remove_front(t_list *self);
t_node				*list_remove_back(t_list *self);
t_node				*list_remove_at(t_list *self, uint64_t index);
void				list_push_front(t_list *self, uintptr_t data);
void				list_push_back(t_list *self, uintptr_t data);
void				list_push_at(t_list *self, uintptr_t data, uint64_t index);
uintptr_t			list_pop_front(t_list *self);
uintptr_t			list_pop_back(t_list *self);
uintptr_t			list_pop_at(t_list *self, uint64_t index);
void				list_sort(t_node **list, int (*f)(uintptr_t d1,
							uintptr_t d2));
t_list				*list_destroy(t_list *self);

#endif
